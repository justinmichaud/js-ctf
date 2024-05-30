# Copyright (C) 2020-2024 Apple Inc. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1.  Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
# 2.  Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

import inspect
import operator
import os
import shutil
import tempfile

from buildbot.process.results import Results, SUCCESS, FAILURE, WARNINGS, SKIPPED, EXCEPTION, RETRY
from buildbot.test.fake.fakebuild import FakeBuild
from buildbot.test.fake.remotecommand import Expect, ExpectRemoteRef, ExpectShell
from buildbot.test.util.misc import TestReactorMixin
from buildbot.test.util.steps import BuildStepMixin
from buildbot.util import identifiers as buildbot_identifiers
from mock import call
from twisted.internet import defer, error, reactor
from twisted.python import failure, log
from twisted.trial import unittest

from .steps import *

CURRENT_HOSTNAME = socket.gethostname().strip()
# Workaround for https://github.com/buildbot/buildbot/issues/4669
FakeBuild.addStepsAfterLastStep = lambda FakeBuild, step_factories: None
FakeBuild._builderid = 1

class ExpectMasterShellCommand(object):
    def __init__(self, command, workdir=None, env=None, usePTY=0):
        self.args = command
        self.usePTY = usePTY
        self.rc = None
        self.path = None
        self.logs = []

        if env is not None:
            self.env = env
        else:
            self.env = os.environ
        if workdir:
            self.path = os.path.join(os.getcwd(), workdir)

    @classmethod
    def log(self, name, value):
        return ('log', name, value)

    def __add__(self, other):
        if isinstance(other, int):
            self.rc = other
        elif isinstance(other, tuple) and other[0] == 'log':
            self.logs.append((other[1], other[2]))
        return self

    def __repr__(self):
        return f'ExpectMasterShellCommand({repr(self.args)})'


class BuildStepMixinAdditions(BuildStepMixin, TestReactorMixin):
    def setUpBuildStep(self):
        self.patch(reactor, 'spawnProcess', lambda *args, **kwargs: self._checkSpawnProcess(*args, **kwargs))
        self._expected_local_commands = []
        self.setUpTestReactor()

        self._temp_directory = tempfile.mkdtemp()
        os.chdir(self._temp_directory)
        self._expected_uploaded_files = []

        super(BuildStepMixinAdditions, self).setUpBuildStep()

    def tearDownBuildStep(self):
        shutil.rmtree(self._temp_directory)
        super(BuildStepMixinAdditions, self).tearDownBuildStep()

    def fakeBuildFinished(self, text, results):
        self.build.text = text
        self.build.results = results

    def setupStep(self, step, *args, **kwargs):
        self.previous_steps = kwargs.get('previous_steps') or []
        if self.previous_steps:
            del kwargs['previous_steps']

        super(BuildStepMixinAdditions, self).setupStep(step, *args, **kwargs)
        self.build.terminate = False
        self.build.stopped = False
        self.build.executedSteps = self.executedSteps
        self.build.buildFinished = self.fakeBuildFinished
        self._expected_added_urls = []
        self._expected_sources = None

    @property
    def executedSteps(self):
        return [step for step in self.previous_steps if not step.stopped]

    def setProperty(self, name, value, source='Unknown'):
        self.properties.setProperty(name, value, source)

    def getProperty(self, name):
        return self.properties.getProperty(name)

    def expectAddedURLs(self, added_urls):
        self._expected_added_urls = added_urls

    def expectUploadedFile(self, path):
        self._expected_uploaded_files.append(path)

    def expectLocalCommands(self, *expected_commands):
        self._expected_local_commands.extend(expected_commands)

    def expectRemoteCommands(self, *expected_commands):
        self.expectCommands(*expected_commands)

    def expectSources(self, expected_sources):
        self._expected_sources = expected_sources

    def _checkSpawnProcess(self, processProtocol, executable, args, env, path, usePTY, **kwargs):
        got = (executable, args, env, path, usePTY)
        if not self._expected_local_commands:
            self.fail(f'got local command {got} when no further commands were expected')
        local_command = self._expected_local_commands.pop(0)
        try:
            self.assertEqual(got, (local_command.args[0], local_command.args, local_command.env, local_command.path, local_command.usePTY))
        except AssertionError:
            log.err()
            raise
        for name, value in local_command.logs:
            if name == 'stdout':
                processProtocol.outReceived(value)
            elif name == 'stderr':
                processProtocol.errReceived(value)
        if local_command.rc != 0:
            value = error.ProcessTerminated(exitCode=local_command.rc)
        else:
            value = error.ProcessDone(None)
        processProtocol.processEnded(failure.Failure(value))

    def _added_files(self):
        results = []
        for dirpath, dirnames, filenames in os.walk(self._temp_directory):
            relative_root_path = os.path.relpath(dirpath, start=self._temp_directory)
            if relative_root_path == '.':
                relative_root_path = ''
            for name in filenames:
                results.append(os.path.join(relative_root_path, name))
        return results

    def runStep(self):
        def check(result):
            self.assertEqual(self._expected_local_commands, [], 'assert all expected local commands were run')
            self.expectAddedURLs(self._expected_added_urls)
            self.assertEqual(self._added_files(), self._expected_uploaded_files)
            if self._expected_sources is not None:
                # Convert to dictionaries because assertEqual() only knows how to diff Python built-in types.
                actual_sources = sorted([source.asDict() for source in self.build.sources], key=operator.itemgetter('codebase'))
                expected_sources = sorted([source.asDict() for source in self._expected_sources], key=operator.itemgetter('codebase'))
                self.assertEqual(actual_sources, expected_sources)
        deferred_result = super(BuildStepMixinAdditions, self).runStep()
        deferred_result.addCallback(check)
        return deferred_result


class TestStepNameShouldBeValidIdentifier(BuildStepMixinAdditions, unittest.TestCase):
    def test_step_names_are_valid(self):
        from . import steps
        build_step_classes = inspect.getmembers(steps, inspect.isclass)
        for build_step in build_step_classes:
            if 'name' in vars(build_step[1]):
                name = build_step[1].name
                self.assertFalse(' ' in name, f'step name "{name}" contain space.')
                self.assertTrue(buildbot_identifiers.ident_re.match(name), f'step name "{name}" is not a valid buildbot identifier.')


class TestRunBindingsTests(BuildStepMixinAdditions, unittest.TestCase):
    def setUp(self):
        self.longMessage = True
        return self.setUpBuildStep()

    def tearDown(self):
        return self.tearDownBuildStep()

    def test_success(self):
        self.setupStep(RunBindingsTests())
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=1200,
                logEnviron=True,
                command=['python3', 'Tools/Scripts/run-bindings-tests'],
            ) + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='bindings-tests')
        return self.runStep()

    def test_failure(self):
        self.setupStep(RunBindingsTests())
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=1200,
                logEnviron=True,
                command=['python3', 'Tools/Scripts/run-bindings-tests'],
            ) + 2
            + ExpectShell.log('stdio', stdout='FAIL: (JS) JSTestInterface.cpp'),
        )
        self.expectOutcome(result=FAILURE, state_string='bindings-tests (failure)')
        return self.runStep()


class TestKillOldProcesses(BuildStepMixinAdditions, unittest.TestCase):
    def setUp(self):
        self.longMessage = True
        return self.setUpBuildStep()

    def tearDown(self):
        return self.tearDownBuildStep()

    def test_success(self):
        self.setupStep(KillOldProcesses())
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=1200,
                logEnviron=True,
                command=['python3', 'Tools/CISupport/kill-old-processes', 'buildbot'],
            ) + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='killed old processes')
        return self.runStep()

    def test_failure(self):
        self.setupStep(KillOldProcesses())
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=1200,
                logEnviron=True,
                command=['python3', 'Tools/CISupport/kill-old-processes', 'buildbot'],
            ) + 2
            + ExpectShell.log('stdio', stdout='Unexpected error.'),
        )
        self.expectOutcome(result=FAILURE, state_string='killed old processes (failure)')
        return self.runStep()


class TestCleanBuildIfScheduled(BuildStepMixinAdditions, unittest.TestCase):
    def setUp(self):
        self.longMessage = True
        return self.setUpBuildStep()

    def tearDown(self):
        return self.tearDownBuildStep()

    def test_success(self):
        self.setupStep(CleanBuildIfScheduled())
        self.setProperty('fullPlatform', 'ios-14')
        self.setProperty('configuration', 'release')
        self.setProperty('is_clean', 'True')
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=1200,
                logEnviron=True,
                command=['python3', 'Tools/CISupport/clean-build', '--platform=ios-14', '--release'],
            ) + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='deleted WebKitBuild directory')
        return self.runStep()

    def test_failure(self):
        self.setupStep(CleanBuildIfScheduled())
        self.setProperty('fullPlatform', 'ios-simulator-14')
        self.setProperty('configuration', 'debug')
        self.setProperty('is_clean', 'True')
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=1200,
                logEnviron=True,
                command=['python3', 'Tools/CISupport/clean-build', '--platform=ios-simulator-14', '--debug'],
            ) + 2
            + ExpectShell.log('stdio', stdout='Unexpected error.'),
        )
        self.expectOutcome(result=FAILURE, state_string='deleted WebKitBuild directory (failure)')
        return self.runStep()

    def test_skip(self):
        self.setupStep(CleanBuildIfScheduled())
        self.setProperty('fullPlatform', 'ios-simulator-14')
        self.setProperty('configuration', 'debug')
        self.expectOutcome(result=SKIPPED, state_string='deleted WebKitBuild directory (skipped)')
        return self.runStep()


class TestInstallGtkDependencies(BuildStepMixinAdditions, unittest.TestCase):
    def setUp(self):
        self.longMessage = True
        return self.setUpBuildStep()

    def tearDown(self):
        return self.tearDownBuildStep()

    def test_success(self):
        self.setupStep(InstallGtkDependencies())
        self.setProperty('configuration', 'release')
        self.assertEqual(InstallGtkDependencies.haltOnFailure, True)
        self.expectRemoteCommands(
            ExpectShell(workdir='wkdir',
                        timeout=1200,
                        logEnviron=True,
                        command=['perl', 'Tools/Scripts/update-webkitgtk-libs', '--release'],
                        )
            + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='updated gtk dependencies')
        return self.runStep()

    def test_failure(self):
        self.setupStep(InstallGtkDependencies())
        self.setProperty('configuration', 'debug')
        self.assertEqual(InstallGtkDependencies.haltOnFailure, True)
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=1200,
                logEnviron=True,
                command=['perl', 'Tools/Scripts/update-webkitgtk-libs', '--debug'],
            ) + 2
            + ExpectShell.log('stdio', stdout='Unexpected error.'),
        )
        self.expectOutcome(result=FAILURE, state_string='updated gtk dependencies (failure)')
        return self.runStep()


class TestInstallWpeDependencies(BuildStepMixinAdditions, unittest.TestCase):
    def setUp(self):
        self.longMessage = True
        return self.setUpBuildStep()

    def tearDown(self):
        return self.tearDownBuildStep()

    def test_success(self):
        self.setupStep(InstallWpeDependencies())
        self.setProperty('configuration', 'release')
        self.assertEqual(InstallWpeDependencies.haltOnFailure, True)
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=1200,
                logEnviron=True,
                command=['perl', 'Tools/Scripts/update-webkitwpe-libs', '--release'],
            ) + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='updated wpe dependencies')
        return self.runStep()

    def test_failure(self):
        self.setupStep(InstallWpeDependencies())
        self.setProperty('configuration', 'release')
        self.assertEqual(InstallWpeDependencies.haltOnFailure, True)
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=1200,
                logEnviron=True,
                command=['perl', 'Tools/Scripts/update-webkitwpe-libs', '--release'],
            ) + 2
            + ExpectShell.log('stdio', stdout='Unexpected error.'),
        )
        self.expectOutcome(result=FAILURE, state_string='updated wpe dependencies (failure)')
        return self.runStep()


class TestCompileWebKit(BuildStepMixinAdditions, unittest.TestCase):
    def setUp(self):
        self.longMessage = True
        return self.setUpBuildStep()

    def tearDown(self):
        return self.tearDownBuildStep()

    def test_success(self):
        self.setupStep(CompileWebKit())
        self.setProperty('fullPlatform', 'ios-simulator-11')
        self.setProperty('configuration', 'release')
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=3600,
                logEnviron=True,
                command=['perl', 'Tools/Scripts/build-webkit', '--no-fatal-warnings', '--release'],
            ) + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='compiled')
        return self.runStep()

    def test_success_architecture(self):
        self.setupStep(CompileWebKit())
        self.setProperty('platform', 'mac')
        self.setProperty('fullPlatform', 'mac-ventura')
        self.setProperty('configuration', 'release')
        self.setProperty('architecture', 'x86_64 arm64')
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=3600,
                logEnviron=True,
                command=['/bin/sh', '-c', 'perl Tools/Scripts/build-webkit --no-fatal-warnings --release --architecture "x86_64 arm64" WK_VALIDATE_DEPENDENCIES=YES 2>&1 | perl Tools/Scripts/filter-build-webkit -logfile build-log.txt'],
            ) + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='compiled')
        return self.runStep()

    def test_bigsur_timeout(self):
        self.setupStep(CompileWebKit())
        self.setProperty('fullPlatform', 'mac-ventura')
        self.setProperty('configuration', 'release')
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=3600,
                logEnviron=True,
                command=['perl', 'Tools/Scripts/build-webkit', '--no-fatal-warnings', '--release'],
            ) + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='compiled')
        return self.runStep()

    def test_success_gtk(self):
        self.setupStep(CompileWebKit())
        self.setProperty('platform', 'gtk')
        self.setProperty('fullPlatform', 'gtk')
        self.setProperty('configuration', 'release')
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=3600,
                logEnviron=True,
                command=['perl', 'Tools/Scripts/build-webkit', '--no-fatal-warnings', '--release', '--prefix=/app/webkit/WebKitBuild/Release/install', '--gtk'],
            ) + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='compiled')
        return self.runStep()

    def test_success_wpe(self):
        self.setupStep(CompileWebKit())
        self.setProperty('platform', 'wpe')
        self.setProperty('fullPlatform', 'wpe')
        self.setProperty('configuration', 'release')
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=3600,
                logEnviron=True,
                command=['perl', 'Tools/Scripts/build-webkit', '--no-fatal-warnings', '--release', '--wpe'],
            ) + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='compiled')
        return self.runStep()

    def test_failure(self):
        self.setupStep(CompileWebKit())
        self.setProperty('fullPlatform', 'mac-sierra')
        self.setProperty('configuration', 'debug')
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=3600,
                logEnviron=True,
                command=['perl', 'Tools/Scripts/build-webkit', '--no-fatal-warnings', '--debug'],
            ) + 2
            + ExpectShell.log('stdio', stdout='1 error generated.'),
        )
        self.expectOutcome(result=FAILURE, state_string='Failed compile-webkit')
        return self.runStep()


class TestCompileJSCOnly(BuildStepMixinAdditions, unittest.TestCase):
    def setUp(self):
        self.longMessage = True
        return self.setUpBuildStep()

    def tearDown(self):
        return self.tearDownBuildStep()

    def test_success(self):
        self.setupStep(CompileJSCOnly())
        self.setProperty('fullPlatform', 'jsc-only')
        self.setProperty('configuration', 'release')
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=3600,
                logEnviron=True,
                command=['perl', 'Tools/Scripts/build-jsc', '--release'],
            ) + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='compiled')
        return self.runStep()

    def test_failure(self):
        self.setupStep(CompileJSCOnly())
        self.setProperty('fullPlatform', 'jsc-only')
        self.setProperty('configuration', 'debug')
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=3600,
                logEnviron=True,
                command=['perl', 'Tools/Scripts/build-jsc', '--debug'],
            ) + 2
            + ExpectShell.log('stdio', stdout='1 error generated.'),
        )
        self.expectOutcome(result=FAILURE, state_string='Failed compile-jsc')
        return self.runStep()


class TestShowIdentifier(BuildStepMixinAdditions, unittest.TestCase):
    def setUp(self):
        self.longMessage = True
        return self.setUpBuildStep()

    def tearDown(self):
        return self.tearDownBuildStep()

    @defer.inlineCallbacks
    def test_success(self):
        self.setupStep(ShowIdentifier())
        self.setProperty('got_revision', 'd3f2b739b65eda1eeb651991a3554dfaeebdfe0b')
        self.expectRemoteCommands(
            ExpectShell(workdir='wkdir',
                        timeout=600,
                        logEnviron=False,
                        command=['python3', 'Tools/Scripts/git-webkit', 'find', 'd3f2b739b65eda1eeb651991a3554dfaeebdfe0b']) +
            ExpectShell.log('stdio', stdout='Identifier: 233939@main\n') +
            0,
        )
        self.expectOutcome(result=SUCCESS, state_string='Identifier: 233939@main')
        rc = yield self.runStep()
        self.assertEqual(self.getProperty('identifier'), '233939@main')
        defer.returnValue(rc)

    def test_failure(self):
        self.setupStep(ShowIdentifier())
        self.setProperty('got_revision', 'd3f2b739b65eda1eeb651991a3554dfaeebdfe0b')
        self.expectRemoteCommands(
            ExpectShell(workdir='wkdir',
                        timeout=600,
                        logEnviron=False,
                        command=['python3', 'Tools/Scripts/git-webkit', 'find', 'd3f2b739b65eda1eeb651991a3554dfaeebdfe0b']) +
            ExpectShell.log('stdio', stdout='Unexpected failure') +
            2,
        )
        self.expectOutcome(result=FAILURE, state_string='Failed to find identifier')
        return self.runStep()


class TestRunWebKitPerlTests(BuildStepMixinAdditions, unittest.TestCase):
    def setUp(self):
        self.longMessage = True
        return self.setUpBuildStep()

    def tearDown(self):
        return self.tearDownBuildStep()

    def test_success(self):
        self.setupStep(RunPerlTests())
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=1200,
                logEnviron=True,
                command=['perl', 'Tools/Scripts/test-webkitperl'],
            ) + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='webkitperl-test')
        return self.runStep()

    def test_failure(self):
        self.setupStep(RunPerlTests())
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=1200,
                logEnviron=True,
                command=['perl', 'Tools/Scripts/test-webkitperl'],
            ) + 2
            + ExpectShell.log('stdio', stdout='''Failed tests:  1-3, 5-7, 9, 11-13
Files=40, Tests=630,  4 wallclock secs ( 0.16 usr  0.09 sys +  2.78 cusr  0.64 csys =  3.67 CPU)
Result: FAIL
Failed 1/40 test programs. 10/630 subtests failed.'''),
        )
        self.expectOutcome(result=FAILURE, state_string='10 perl tests failed')
        return self.runStep()


class TestRunWebKitPyTests(BuildStepMixinAdditions, unittest.TestCase):
    def setUp(self):
        self.longMessage = True
        os.environ['RESULTS_SERVER_API_KEY'] = 'test-api-key'
        return self.setUpBuildStep()

    def tearDown(self):
        del os.environ['RESULTS_SERVER_API_KEY']
        return self.tearDownBuildStep()

    def configureStep(self):
        self.setupStep(RunWebKitPyTests())
        self.setProperty('buildername', 'WebKitPy-Tests-EWS')
        self.setProperty('buildnumber', '101')
        self.setProperty('workername', 'ews100')

    def test_success(self):
        self.configureStep()
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=1200,
                logEnviron=False,
                command=['python3', 'Tools/Scripts/test-webkitpy', '--verbose',
                         '--buildbot-master', CURRENT_HOSTNAME,
                         '--builder-name', 'WebKitPy-Tests-EWS',
                         '--build-number', '101', '--buildbot-worker', 'ews100',
                         '--report', RESULTS_WEBKIT_URL],
                env={'RESULTS_SERVER_API_KEY': 'test-api-key'}
            ) + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='webkitpy-test')
        return self.runStep()

    def test_unexpected_failure(self):
        self.configureStep()
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=1200,
                logEnviron=False,
                command=['python3', 'Tools/Scripts/test-webkitpy', '--verbose',
                         '--buildbot-master', CURRENT_HOSTNAME,
                         '--builder-name', 'WebKitPy-Tests-EWS',
                         '--build-number', '101', '--buildbot-worker', 'ews100',
                         '--report', RESULTS_WEBKIT_URL],
                env={'RESULTS_SERVER_API_KEY': 'test-api-key'}
            ) + 2,
        )
        self.expectOutcome(result=FAILURE, state_string='webkitpy-test (failure)')
        return self.runStep()

    def test_failure(self):
        self.configureStep()
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=1200,
                logEnviron=False,
                command=['python3', 'Tools/Scripts/test-webkitpy', '--verbose',
                         '--buildbot-master', CURRENT_HOSTNAME,
                         '--builder-name', 'WebKitPy-Tests-EWS',
                         '--build-number', '101', '--buildbot-worker', 'ews100',
                         '--report', RESULTS_WEBKIT_URL],
                env={'RESULTS_SERVER_API_KEY': 'test-api-key'}
            ) + 2
            + ExpectShell.log('stdio', stdout='FAILED (failures=2, errors=0)'),
        )
        self.expectOutcome(result=FAILURE, state_string='2 python tests failed')
        return self.runStep()

    def test_errors(self):
        self.configureStep()
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=1200,
                logEnviron=False,
                command=['python3', 'Tools/Scripts/test-webkitpy', '--verbose',
                         '--buildbot-master', CURRENT_HOSTNAME,
                         '--builder-name', 'WebKitPy-Tests-EWS',
                         '--build-number', '101', '--buildbot-worker', 'ews100',
                         '--report', RESULTS_WEBKIT_URL],
                env={'RESULTS_SERVER_API_KEY': 'test-api-key'}
            ) + 2
            + ExpectShell.log('stdio', stdout='FAILED (failures=0, errors=2)'),
        )
        self.expectOutcome(result=FAILURE, state_string='2 python tests failed')
        return self.runStep()

    def test_lot_of_failures(self):
        self.configureStep()
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=1200,
                logEnviron=False,
                command=['python3', 'Tools/Scripts/test-webkitpy', '--verbose',
                         '--buildbot-master', CURRENT_HOSTNAME,
                         '--builder-name', 'WebKitPy-Tests-EWS',
                         '--build-number', '101', '--buildbot-worker', 'ews100',
                         '--report', RESULTS_WEBKIT_URL],
                env={'RESULTS_SERVER_API_KEY': 'test-api-key'}
            ) + 2
            + ExpectShell.log('stdio', stdout='FAILED (failures=30, errors=2)'),
        )
        self.expectOutcome(result=FAILURE, state_string='32 python tests failed')
        return self.runStep()


class TestRunLLDBWebKitTests(BuildStepMixinAdditions, unittest.TestCase):
    def setUp(self):
        self.longMessage = True
        return self.setUpBuildStep()

    def tearDown(self):
        return self.tearDownBuildStep()

    def test_success(self):
        self.setupStep(RunLLDBWebKitTests())
        self.setProperty('configuration', 'release')
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=1200,
                logEnviron=True,
                command=['python3', 'Tools/Scripts/test-lldb-webkit', '--verbose', '--no-build', '--release'],
            ) + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='lldb-webkit-test')
        return self.runStep()

    def test_unexpected_failure(self):
        self.setupStep(RunLLDBWebKitTests())
        self.setProperty('configuration', 'release')
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=1200,
                logEnviron=True,
                command=['python3', 'Tools/Scripts/test-lldb-webkit', '--verbose', '--no-build', '--release'],
            ) + 2,
        )
        self.expectOutcome(result=FAILURE, state_string='lldb-webkit-test (failure)')
        return self.runStep()

    def test_failure(self):
        self.setupStep(RunLLDBWebKitTests())
        self.setProperty('configuration', 'release')
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=1200,
                logEnviron=True,
                command=['python3', 'Tools/Scripts/test-lldb-webkit', '--verbose', '--no-build', '--release'],
            ) + 2
            + ExpectShell.log('stdio', stdout='FAILED (failures=2, errors=0)'),
        )
        self.expectOutcome(result=FAILURE, state_string='2 lldb tests failed')
        return self.runStep()

    def test_errors(self):
        self.setupStep(RunLLDBWebKitTests())
        self.setProperty('configuration', 'release')
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=1200,
                logEnviron=True,
                command=['python3', 'Tools/Scripts/test-lldb-webkit', '--verbose', '--no-build', '--release'],
            ) + 2
            + ExpectShell.log('stdio', stdout='FAILED (failures=0, errors=2)'),
        )
        self.expectOutcome(result=FAILURE, state_string='2 lldb tests failed')
        return self.runStep()

    def test_lot_of_failures(self):
        self.setupStep(RunLLDBWebKitTests())
        self.setProperty('configuration', 'release')
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=1200,
                logEnviron=True,
                command=['python3', 'Tools/Scripts/test-lldb-webkit', '--verbose', '--no-build', '--release'],
            ) + 2
            + ExpectShell.log('stdio', stdout='FAILED (failures=30, errors=2)'),
        )
        self.expectOutcome(result=FAILURE, state_string='32 lldb tests failed')
        return self.runStep()


class TestRunWebKitTests(BuildStepMixinAdditions, unittest.TestCase):
    def setUp(self):
        self.longMessage = True
        os.environ['RESULTS_SERVER_API_KEY'] = 'test-api-key'
        return self.setUpBuildStep()

    def tearDown(self):
        del os.environ['RESULTS_SERVER_API_KEY']
        return self.tearDownBuildStep()

    def configureStep(self):
        self.setupStep(RunWebKitTests())
        self.setProperty('buildername', 'iOS-14-Simulator-WK2-Tests-EWS')
        self.setProperty('buildnumber', '101')
        self.setProperty('workername', 'ews100')

    def test_success(self):
        self.configureStep()
        self.setProperty('fullPlatform', 'ios-simulator')
        self.setProperty('configuration', 'release')
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=1200,
                logEnviron=False,
                command=['python3', 'Tools/Scripts/run-webkit-tests', '--no-build', '--no-show-results',
                         '--no-new-test-results', '--clobber-old-results',
                         '--builder-name', 'iOS-14-Simulator-WK2-Tests-EWS',
                         '--build-number', '101', '--buildbot-worker', 'ews100',
                         '--buildbot-master', CURRENT_HOSTNAME,
                         '--report', RESULTS_WEBKIT_URL,
                         '--exit-after-n-crashes-or-timeouts', '50',
                         '--exit-after-n-failures', '500',
                         '--release', '--results-directory', 'layout-test-results', '--debug-rwt-logging'],
                env={'RESULTS_SERVER_API_KEY': 'test-api-key'}
            ) + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='layout-tests')
        return self.runStep()

    def test_warnings(self):
        self.configureStep()
        self.setProperty('fullPlatform', 'ios-simulator')
        self.setProperty('configuration', 'release')
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=1200,
                logEnviron=False,
                command=['python3', 'Tools/Scripts/run-webkit-tests', '--no-build', '--no-show-results',
                         '--no-new-test-results', '--clobber-old-results',
                         '--builder-name', 'iOS-14-Simulator-WK2-Tests-EWS',
                         '--build-number', '101', '--buildbot-worker', 'ews100',
                         '--buildbot-master', CURRENT_HOSTNAME,
                         '--report', RESULTS_WEBKIT_URL,
                         '--exit-after-n-crashes-or-timeouts', '50',
                         '--exit-after-n-failures', '500',
                         '--release', '--results-directory', 'layout-test-results', '--debug-rwt-logging'],
                env={'RESULTS_SERVER_API_KEY': 'test-api-key'}
            ) + 0
            + ExpectShell.log('stdio', stdout='''Unexpected flakiness: timeouts (2)
                              imported/blink/storage/indexeddb/blob-valid-before-commit.html [ Timeout Pass ]
                              storage/indexeddb/modern/deleteindex-2.html [ Timeout Pass ]'''),
        )
        self.expectOutcome(result=WARNINGS, state_string='2 flakes')
        return self.runStep()

    def test_failure(self):
        self.configureStep()
        self.setProperty('fullPlatform', 'ios-simulator')
        self.setProperty('configuration', 'release')
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=1200,
                logEnviron=False,
                command=['python3', 'Tools/Scripts/run-webkit-tests', '--no-build', '--no-show-results',
                         '--no-new-test-results', '--clobber-old-results',
                         '--builder-name', 'iOS-14-Simulator-WK2-Tests-EWS',
                         '--build-number', '101', '--buildbot-worker', 'ews100',
                         '--buildbot-master', CURRENT_HOSTNAME,
                         '--report', RESULTS_WEBKIT_URL,
                         '--exit-after-n-crashes-or-timeouts', '50',
                         '--exit-after-n-failures', '500',
                         '--release', '--results-directory', 'layout-test-results', '--debug-rwt-logging'],
                env={'RESULTS_SERVER_API_KEY': 'test-api-key'}
            ) + 2
            + ExpectShell.log('stdio', stdout='9 failures found.'),
        )
        self.expectOutcome(result=FAILURE, state_string='layout-tests (failure)')
        return self.runStep()

    def test_unexpected_error(self):
        self.configureStep()
        self.setProperty('fullPlatform', 'mac-highsierra')
        self.setProperty('configuration', 'debug')
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=1200,
                logEnviron=False,
                command=['python3', 'Tools/Scripts/run-webkit-tests', '--no-build', '--no-show-results',
                         '--no-new-test-results', '--clobber-old-results',
                         '--builder-name', 'iOS-14-Simulator-WK2-Tests-EWS',
                         '--build-number', '101', '--buildbot-worker', 'ews100',
                         '--buildbot-master', CURRENT_HOSTNAME,
                         '--report', RESULTS_WEBKIT_URL,
                         '--exit-after-n-crashes-or-timeouts', '50',
                         '--exit-after-n-failures', '500',
                         '--debug', '--results-directory', 'layout-test-results', '--debug-rwt-logging'],
                env={'RESULTS_SERVER_API_KEY': 'test-api-key'}
            ) + 2
            + ExpectShell.log('stdio', stdout='Unexpected error.'),
        )
        self.expectOutcome(result=FAILURE, state_string='layout-tests (failure)')
        return self.runStep()

    def test_exception(self):
        self.configureStep()
        self.setProperty('fullPlatform', 'mac-highsierra')
        self.setProperty('configuration', 'debug')
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=1200,
                logEnviron=False,
                command=['python3', 'Tools/Scripts/run-webkit-tests', '--no-build', '--no-show-results',
                         '--no-new-test-results', '--clobber-old-results',
                         '--builder-name', 'iOS-14-Simulator-WK2-Tests-EWS',
                         '--build-number', '101', '--buildbot-worker', 'ews100',
                         '--buildbot-master', CURRENT_HOSTNAME,
                         '--report', RESULTS_WEBKIT_URL,
                         '--exit-after-n-crashes-or-timeouts', '50',
                         '--exit-after-n-failures', '500',
                         '--debug', '--results-directory', 'layout-test-results', '--debug-rwt-logging'],
                env={'RESULTS_SERVER_API_KEY': 'test-api-key'}
            ) + 254
            + ExpectShell.log('stdio', stdout='Unexpected error.'),
        )
        self.expectOutcome(result=EXCEPTION, state_string='layout-tests (exception)')
        return self.runStep()

    def test_gtk_parameters(self):
        self.configureStep()
        self.setProperty('fullPlatform', 'gtk')
        self.setProperty('platform', 'gtk')
        self.setProperty('configuration', 'release')
        self.setProperty('buildername', 'GTK-Linux-64-bit-Release-Tests')
        self.setProperty('buildnumber', '103')
        self.setProperty('workername', 'gtk103')
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=1200,
                logEnviron=False,
                command=['python3', 'Tools/Scripts/run-webkit-tests', '--no-build', '--no-show-results',
                         '--no-new-test-results', '--clobber-old-results',
                         '--builder-name', 'GTK-Linux-64-bit-Release-Tests',
                         '--build-number', '103', '--buildbot-worker', 'gtk103',
                         '--buildbot-master', CURRENT_HOSTNAME,
                         '--report', RESULTS_WEBKIT_URL,
                         '--exit-after-n-crashes-or-timeouts', '50',
                         '--exit-after-n-failures', '500',
                         '--release', '--gtk', '--results-directory', 'layout-test-results',
                         '--debug-rwt-logging', '--enable-core-dumps-nolimit'],
                env={'RESULTS_SERVER_API_KEY': 'test-api-key'}
            ) + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='layout-tests')
        return self.runStep()

    def test_wpe_parameters(self):
        self.configureStep()
        self.setProperty('fullPlatform', 'wpe')
        self.setProperty('platform', 'wpe')
        self.setProperty('configuration', 'release')
        self.setProperty('buildername', 'WPE-Linux-64-bit-Release-Tests')
        self.setProperty('buildnumber', '103')
        self.setProperty('workername', 'wpe103')
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=1200,
                logEnviron=False,
                command=['python3', 'Tools/Scripts/run-webkit-tests', '--no-build', '--no-show-results',
                         '--no-new-test-results', '--clobber-old-results',
                         '--builder-name', 'WPE-Linux-64-bit-Release-Tests',
                         '--build-number', '103', '--buildbot-worker', 'wpe103',
                         '--buildbot-master', CURRENT_HOSTNAME,
                         '--report', RESULTS_WEBKIT_URL,
                         '--exit-after-n-crashes-or-timeouts', '50',
                         '--exit-after-n-failures', '500',
                         '--release', '--wpe', '--results-directory', 'layout-test-results',
                         '--debug-rwt-logging', '--enable-core-dumps-nolimit'],
                env={'RESULTS_SERVER_API_KEY': 'test-api-key'}
            ) + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='layout-tests')
        return self.runStep()


class TestRunWebKit1Tests(BuildStepMixinAdditions, unittest.TestCase):
    def setUp(self):
        self.longMessage = True
        self.jsonFileName = 'layout-test-results/full_results.json'
        os.environ['RESULTS_SERVER_API_KEY'] = 'test-api-key'
        return self.setUpBuildStep()

    def tearDown(self):
        del os.environ['RESULTS_SERVER_API_KEY']
        return self.tearDownBuildStep()

    def configureStep(self):
        self.setupStep(RunWebKit1Tests())
        self.setProperty('buildername', 'Apple-iOS-14-Simulator-Debug-Build')
        self.setProperty('buildnumber', '101')
        self.setProperty('workername', 'bot100')

    def test_success(self):
        self.configureStep()
        self.setProperty('fullPlatform', 'ios-simulator')
        self.setProperty('configuration', 'debug')
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                logEnviron=False,
                command=['python3', 'Tools/Scripts/run-webkit-tests', '--no-build', '--no-show-results',
                         '--no-new-test-results', '--clobber-old-results',
                         '--builder-name', 'Apple-iOS-14-Simulator-Debug-Build',
                         '--build-number', '101', '--buildbot-worker', 'bot100',
                         '--buildbot-master', CURRENT_HOSTNAME,
                         '--report', RESULTS_WEBKIT_URL,
                         '--exit-after-n-crashes-or-timeouts', '50',
                         '--exit-after-n-failures', '500',
                         '--debug', '--dump-render-tree', '--results-directory', 'layout-test-results', '--debug-rwt-logging'],
                env={'RESULTS_SERVER_API_KEY': 'test-api-key'}
            ) + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='layout-tests')
        return self.runStep()

    def test_failure(self):
        self.configureStep()
        self.setProperty('fullPlatform', 'ios-14')
        self.setProperty('configuration', 'release')
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                logEnviron=False,
                command=['python3', 'Tools/Scripts/run-webkit-tests', '--no-build', '--no-show-results',
                         '--no-new-test-results', '--clobber-old-results',
                         '--builder-name', 'Apple-iOS-14-Simulator-Debug-Build',
                         '--build-number', '101', '--buildbot-worker', 'bot100',
                         '--buildbot-master', CURRENT_HOSTNAME,
                         '--report', RESULTS_WEBKIT_URL,
                         '--exit-after-n-crashes-or-timeouts', '50',
                         '--exit-after-n-failures', '500',
                         '--release', '--dump-render-tree', '--results-directory', 'layout-test-results', '--debug-rwt-logging'],
                env={'RESULTS_SERVER_API_KEY': 'test-api-key'}
            ) + ExpectShell.log('stdio', stdout='9 failures found.')
            + 2,
        )
        self.expectOutcome(result=FAILURE, state_string='layout-tests (failure)')
        return self.runStep()


class TestRunJavaScriptCoreTests(BuildStepMixinAdditions, unittest.TestCase):
    def setUp(self):
        self.longMessage = True
        os.environ['RESULTS_SERVER_API_KEY'] = 'test-api-key'
        self.jsonFileName = 'jsc_results.json'
        return self.setUpBuildStep()

    def tearDown(self):
        del os.environ['RESULTS_SERVER_API_KEY']
        return self.tearDownBuildStep()

    def configureStep(self, platform=None, fullPlatform=None, configuration=None):
        self.setupStep(RunJavaScriptCoreTests())
        self.commandExtra = RunJavaScriptCoreTests.commandExtra
        if platform:
            self.setProperty('platform', platform)
        if fullPlatform:
            self.setProperty('fullPlatform', fullPlatform)
        if configuration:
            self.setProperty('configuration', configuration)
        self.setProperty('buildername', 'JSC-Tests')
        self.setProperty('buildnumber', '101')
        self.setProperty('workername', 'bot100')

    def test_success(self):
        self.configureStep(platform='mac', fullPlatform='mac-highsierra', configuration='release')
        command = ['perl', 'Tools/Scripts/run-javascriptcore-tests', '--no-build', '--no-fail-fast', f'--json-output={self.jsonFileName}', '--release', '--builder-name', 'JSC-Tests', '--build-number', '101', '--buildbot-worker', 'bot100', '--buildbot-master', CURRENT_HOSTNAME, '--report', 'https://results.webkit.org'] + self.commandExtra
        self.expectRemoteCommands(
            ExpectShell(workdir='wkdir',
                        logEnviron=False,
                        command=['/bin/sh', '-c', ' '.join(command) + ' 2>&1 | python3 Tools/Scripts/filter-jsc-tests'],
                        logfiles={'json': self.jsonFileName},
                        env={'RESULTS_SERVER_API_KEY': 'test-api-key'},
                        timeout=72000,
                        )
            + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='jscore-test')
        return self.runStep()

    def test_failure(self):
        self.configureStep(platform='mac', fullPlatform='mac-highsierra', configuration='debug')
        command = ['perl', 'Tools/Scripts/run-javascriptcore-tests', '--no-build', '--no-fail-fast', f'--json-output={self.jsonFileName}', '--debug', '--builder-name', 'JSC-Tests', '--build-number', '101', '--buildbot-worker', 'bot100', '--buildbot-master', CURRENT_HOSTNAME, '--report', 'https://results.webkit.org'] + self.commandExtra
        self.expectRemoteCommands(
            ExpectShell(workdir='wkdir',
                        logEnviron=False,
                        command=['/bin/sh', '-c', ' '.join(command) + ' 2>&1 | python3 Tools/Scripts/filter-jsc-tests'],
                        logfiles={'json': self.jsonFileName},
                        env={'RESULTS_SERVER_API_KEY': 'test-api-key'},
                        timeout=72000,
                        )
            + ExpectShell.log('stdio', stdout='Results for JSC stress tests:\n 9 failures found.')
            + 2,
        )
        self.expectOutcome(result=FAILURE, state_string='9 JSC tests failed')
        return self.runStep()


class TestSetPermissions(BuildStepMixinAdditions, unittest.TestCase):
    def setUp(self):
        self.longMessage = True
        return self.setUpBuildStep()

    def tearDown(self):
        return self.tearDownBuildStep()

    def test_success(self):
        self.setupStep(SetPermissions())
        self.setProperty('result_directory', 'public_html/results/Apple-Ventura-Release-WK2-Tests/r277034 (2346)')
        self.expectLocalCommands(
            ExpectMasterShellCommand(command=['chmod', 'a+rx', 'public_html/results/Apple-Ventura-Release-WK2-Tests/r277034 (2346)'])
            + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='Ran')
        return self.runStep()

    def test_failure(self):
        self.setupStep(SetPermissions())
        self.setProperty('result_directory', 'testdir')
        self.expectLocalCommands(
            ExpectMasterShellCommand(command=['chmod', 'a+rx', 'testdir'])
            + 1,
        )
        self.expectOutcome(result=FAILURE, state_string='failed (1) (failure)')
        return self.runStep()


class TestCleanUpGitIndexLock(BuildStepMixinAdditions, unittest.TestCase):
    def setUp(self):
        self.longMessage = True
        return self.setUpBuildStep()

    def tearDown(self):
        return self.tearDownBuildStep()

    def test_success(self):
        self.setupStep(CleanUpGitIndexLock())
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=120,
                logEnviron=False,
                command=['rm', '-f', '.git/index.lock'],
            ) + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='Deleted .git/index.lock')
        return self.runStep()

    def test_failure(self):
        self.setupStep(CleanUpGitIndexLock())
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                timeout=120,
                logEnviron=False,
                command=['rm', '-f', '.git/index.lock'],
            ) + 2
            + ExpectShell.log('stdio', stdout='Unexpected error.'),
        )
        self.expectOutcome(result=FAILURE, state_string='Deleted .git/index.lock (failure)')
        return self.runStep()


class TestPrintConfiguration(BuildStepMixinAdditions, unittest.TestCase):
    def setUp(self):
        self.longMessage = True
        return self.setUpBuildStep()

    def tearDown(self):
        return self.tearDownBuildStep()

    def test_success_mac(self):
        self.setupStep(PrintConfiguration())
        self.setProperty('buildername', 'macOS-Ventura-Release-WK2-Tests-EWS')
        self.setProperty('platform', 'mac-ventura')

        self.expectRemoteCommands(
            ExpectShell(command=['hostname'], workdir='wkdir', timeout=60, logEnviron=False) + 0
            + ExpectShell.log('stdio', stdout='ews150.apple.com'),
            ExpectShell(command=['df', '-hl'], workdir='wkdir', timeout=60, logEnviron=False) + 0
            + ExpectShell.log('stdio', stdout='''Filesystem     Size   Used  Avail Capacity iused  ifree %iused  Mounted on
/dev/disk1s1  119Gi   95Gi   23Gi    81%  937959 9223372036853837848    0%   /
/dev/disk1s4  119Gi   20Ki   23Gi     1%       0 9223372036854775807    0%   /private/var/vm
/dev/disk0s3  119Gi   22Gi   97Gi    19%  337595          4294629684    0%   /Volumes/Data'''),
            ExpectShell(command=['date'], workdir='wkdir', timeout=60, logEnviron=False) + 0
            + ExpectShell.log('stdio', stdout='Tue Apr  9 15:30:52 PDT 2019'),
            ExpectShell(command=['sw_vers'], workdir='wkdir', timeout=60, logEnviron=False) + 0
            + ExpectShell.log('stdio', stdout='''ProductName:	macOS
ProductVersion:	12.0.1
BuildVersion:	21A558'''),
            ExpectShell(command=['system_profiler', 'SPSoftwareDataType', 'SPHardwareDataType'], workdir='wkdir', timeout=60, logEnviron=False) + 0
            + ExpectShell.log('stdio', stdout='Configuration version: Software: System Software Overview: System Version: macOS 11.4 (20F71) Kernel Version: Darwin 20.5.0 Boot Volume: Macintosh HD Boot Mode: Normal Computer Name: bot1020 User Name: WebKit Build Worker (buildbot) Secure Virtual Memory: Enabled System Integrity Protection: Enabled Time since boot: 27 seconds Hardware: Hardware Overview: Model Name: Mac mini Model Identifier: Macmini8,1 Processor Name: 6-Core Intel Core i7 Processor Speed: 3.2 GHz Number of Processors: 1 Total Number of Cores: 6 L2 Cache (per Core): 256 KB L3 Cache: 12 MB Hyper-Threading Technology: Enabled Memory: 32 GB System Firmware Version: 1554.120.19.0.0 (iBridge: 18.16.14663.0.0,0) Serial Number (system): C07DXXXXXXXX Hardware UUID: F724DE6E-706A-5A54-8D16-000000000000 Provisioning UDID: E724DE6E-006A-5A54-8D16-000000000000 Activation Lock Status: Disabled Xcode 12.5 Build version 12E262'),
            ExpectShell(command=['/bin/sh', '-c', 'echo TimezoneVers: $(cat /usr/share/zoneinfo/+VERSION)'], workdir='wkdir', timeout=60, logEnviron=False) + 0,
            ExpectShell(command=['xcodebuild', '-sdk', '-version'], workdir='wkdir', timeout=60, logEnviron=False)
            + ExpectShell.log('stdio', stdout='''MacOSX12.0.sdk - macOS 12.0 (macosx12.0)
SDKVersion: 12.0
Path: /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX12.0.sdk
PlatformVersion: 12.0
PlatformPath: /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform
ProductBuildVersion: 21A344
ProductCopyright: 1983-2021 Apple Inc.
ProductName: macOS
ProductUserVisibleVersion: 12.0
ProductVersion: 12.0
iOSSupportVersion: 15.0

Xcode 13.1
Build version 13A1030d''')
            + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='OS: Monterey (12.0.1), Xcode: 13.1')
        return self.runStep()

    def test_success_ios_simulator(self):
        self.setupStep(PrintConfiguration())
        self.setProperty('buildername', 'Apple-iOS-15-Simulator-Release-WK2-Tests')
        self.setProperty('platform', 'ios-simulator-15')

        self.expectRemoteCommands(
            ExpectShell(command=['hostname'], workdir='wkdir', timeout=60, logEnviron=False) + 0
            + ExpectShell.log('stdio', stdout='ews152.apple.com'),
            ExpectShell(command=['df', '-hl'], workdir='wkdir', timeout=60, logEnviron=False) + 0
            + ExpectShell.log('stdio', stdout='''Filesystem     Size   Used  Avail Capacity iused  ifree %iused  Mounted on
/dev/disk1s1  119Gi   95Gi   23Gi    81%  937959 9223372036853837848    0%   /
/dev/disk1s4  119Gi   20Ki   23Gi     1%       0 9223372036854775807    0%   /private/var/vm
/dev/disk0s3  119Gi   22Gi   97Gi    19%  337595          4294629684    0%   /Volumes/Data'''),
            ExpectShell(command=['date'], workdir='wkdir', timeout=60, logEnviron=False) + 0
            + ExpectShell.log('stdio', stdout='Tue Apr  9 15:30:52 PDT 2019'),
            ExpectShell(command=['sw_vers'], workdir='wkdir', timeout=60, logEnviron=False) + 0
            + ExpectShell.log('stdio', stdout='''ProductName:	macOS
ProductVersion:	11.6
BuildVersion:	20G165'''),
            ExpectShell(command=['system_profiler', 'SPSoftwareDataType', 'SPHardwareDataType'], workdir='wkdir', timeout=60, logEnviron=False) + 0
            + ExpectShell.log('stdio', stdout='Sample system information'),
            ExpectShell(command=['/bin/sh', '-c', 'echo TimezoneVers: $(cat /usr/share/zoneinfo/+VERSION)'], workdir='wkdir', timeout=60, logEnviron=False) + 0,
            ExpectShell(command=['xcodebuild', '-sdk', '-version'], workdir='wkdir', timeout=60, logEnviron=False)
            + ExpectShell.log('stdio', stdout='''iPhoneSimulator15.0.sdk - Simulator - iOS 15.0 (iphonesimulator15.0)
SDKVersion: 15.0
Path: /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator15.0.sdk
PlatformVersion: 15.0
PlatformPath: /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform
BuildID: 84856584-0587-11EC-B99C-6807972BB3D4
ProductBuildVersion: 19A339
ProductCopyright: 1983-2021 Apple Inc.
ProductName: iPhone OS
ProductVersion: 15.0

Xcode 13.0
Build version 13A233''')
            + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='OS: Big Sur (11.6), Xcode: 13.0')
        return self.runStep()

    def test_success_webkitpy(self):
        self.setupStep(PrintConfiguration())
        self.setProperty('platform', '*')

        self.expectRemoteCommands(
            ExpectShell(command=['hostname'], workdir='wkdir', timeout=60, logEnviron=False) + 0,
            ExpectShell(command=['df', '-hl'], workdir='wkdir', timeout=60, logEnviron=False) + 0,
            ExpectShell(command=['date'], workdir='wkdir', timeout=60, logEnviron=False) + 0,
            ExpectShell(command=['sw_vers'], workdir='wkdir', timeout=60, logEnviron=False) + 0
            + ExpectShell.log('stdio', stdout='''ProductName:	macOS
ProductVersion:	11.6
BuildVersion:	20G165'''),
            ExpectShell(command=['system_profiler', 'SPSoftwareDataType', 'SPHardwareDataType'], workdir='wkdir', timeout=60, logEnviron=False) + 0
            + ExpectShell.log('stdio', stdout='Sample system information'),
            ExpectShell(command=['/bin/sh', '-c', 'echo TimezoneVers: $(cat /usr/share/zoneinfo/+VERSION)'], workdir='wkdir', timeout=60, logEnviron=False) + 0,
            ExpectShell(command=['xcodebuild', '-sdk', '-version'], workdir='wkdir', timeout=60, logEnviron=False) + 0
            + ExpectShell.log('stdio', stdout='''Xcode 13.0\nBuild version 13A233'''),
        )
        self.expectOutcome(result=SUCCESS, state_string='OS: Big Sur (11.6), Xcode: 13.0')
        return self.runStep()

    def test_success_linux_wpe(self):
        self.setupStep(PrintConfiguration())
        self.setProperty('platform', 'wpe')

        self.expectRemoteCommands(
            ExpectShell(command=['hostname'], workdir='wkdir', timeout=60, logEnviron=False) + 0
            + ExpectShell.log('stdio', stdout='ews190'),
            ExpectShell(command=['df', '-hl', '--exclude-type=fuse.portal'], workdir='wkdir', timeout=60, logEnviron=False) + 0
            + ExpectShell.log('stdio', stdout='''Filesystem     Size   Used  Avail Capacity iused  ifree %iused  Mounted on
/dev/disk0s3  119Gi   22Gi   97Gi    19%  337595          4294629684    0%   /'''),
            ExpectShell(command=['date'], workdir='wkdir', timeout=60, logEnviron=False) + 0
            + ExpectShell.log('stdio', stdout='Tue Apr  9 15:30:52 PDT 2019'),
            ExpectShell(command=['uname', '-a'], workdir='wkdir', timeout=60, logEnviron=False) + 0
            + ExpectShell.log('stdio', stdout='''Linux kodama-ews 5.0.4-arch1-1-ARCH #1 SMP PREEMPT Sat Mar 23 21:00:33 UTC 2019 x86_64 GNU/Linux'''),
            ExpectShell(command=['uptime'], workdir='wkdir', timeout=60, logEnviron=False) + 0
            + ExpectShell.log('stdio', stdout=' 6:31  up 22 seconds, 12:05, 2 users, load averages: 3.17 7.23 5.45'),
        )
        self.expectOutcome(result=SUCCESS, state_string='Printed configuration')
        return self.runStep()

    def test_success_linux_gtk(self):
        self.setupStep(PrintConfiguration())
        self.setProperty('platform', 'gtk')

        self.expectRemoteCommands(
            ExpectShell(command=['hostname'], workdir='wkdir', timeout=60, logEnviron=False) + 0,
            ExpectShell(command=['df', '-hl', '--exclude-type=fuse.portal'], workdir='wkdir', timeout=60, logEnviron=False) + 0,
            ExpectShell(command=['date'], workdir='wkdir', timeout=60, logEnviron=False) + 0,
            ExpectShell(command=['uname', '-a'], workdir='wkdir', timeout=60, logEnviron=False) + 0,
            ExpectShell(command=['uptime'], workdir='wkdir', timeout=60, logEnviron=False) + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='Printed configuration')
        return self.runStep()

    def test_success_win(self):
        self.setupStep(PrintConfiguration())
        self.setProperty('platform', 'win')

        self.expectRemoteCommands(
            ExpectShell(command=['hostname'], workdir='wkdir', timeout=60, logEnviron=False) + 0,
            ExpectShell(command=['df', '-hl'], workdir='wkdir', timeout=60, logEnviron=False) + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='Printed configuration')
        return self.runStep()

    def test_failure(self):
        self.setupStep(PrintConfiguration())
        self.setProperty('platform', 'ios-12')
        self.expectRemoteCommands(
            ExpectShell(command=['hostname'], workdir='wkdir', timeout=60, logEnviron=False) + 0,
            ExpectShell(command=['df', '-hl'], workdir='wkdir', timeout=60, logEnviron=False) + 0,
            ExpectShell(command=['date'], workdir='wkdir', timeout=60, logEnviron=False) + 0,
            ExpectShell(command=['sw_vers'], workdir='wkdir', timeout=60, logEnviron=False) + 1
            + ExpectShell.log('stdio', stdout='''Upon execvpe sw_vers ['sw_vers'] in environment id 7696545650400
:Traceback (most recent call last):
  File "/usr/lib/python2.7/site-packages/twisted/internet/process.py", line 445, in _fork
    environment)
  File "/usr/lib/python2.7/site-packages/twisted/internet/process.py", line 523, in _execChild
    os.execvpe(executable, args, environment)
  File "/usr/lib/python2.7/os.py", line 355, in execvpe
    _execvpe(file, args, env)
  File "/usr/lib/python2.7/os.py", line 382, in _execvpe
    func(fullname, *argrest)
OSError: [Errno 2] No such file or directory'''),
            ExpectShell(command=['system_profiler', 'SPSoftwareDataType', 'SPHardwareDataType'], workdir='wkdir', timeout=60, logEnviron=False) + 0
            + ExpectShell.log('stdio', stdout='Sample system information'),
            ExpectShell(command=['/bin/sh', '-c', 'echo TimezoneVers: $(cat /usr/share/zoneinfo/+VERSION)'], workdir='wkdir', timeout=60, logEnviron=False) + 0,
            ExpectShell(command=['xcodebuild', '-sdk', '-version'], workdir='wkdir', timeout=60, logEnviron=False)
            + ExpectShell.log('stdio', stdout='''Upon execvpe xcodebuild ['xcodebuild', '-sdk', '-version'] in environment id 7696545612416
:Traceback (most recent call last):
  File "/usr/lib/python2.7/site-packages/twisted/internet/process.py", line 445, in _fork
    environment)
  File "/usr/lib/python2.7/site-packages/twisted/internet/process.py", line 523, in _execChild
    os.execvpe(executable, args, environment)
  File "/usr/lib/python2.7/os.py", line 355, in execvpe
    _execvpe(file, args, env)
  File "/usr/lib/python2.7/os.py", line 382, in _execvpe
    func(fullname, *argrest)
OSError: [Errno 2] No such file or directory''')
            + 1,
        )
        self.expectOutcome(result=FAILURE, state_string='Failed to print configuration')
        return self.runStep()


class TestInstallBuiltProduct(BuildStepMixinAdditions, unittest.TestCase):
    def setUp(self):
        self.longMessage = True
        return self.setUpBuildStep()

    def tearDown(self):
        return self.tearDownBuildStep()

    def test_success(self):
        self.setupStep(InstallBuiltProduct())
        self.setProperty('fullPlatform', 'ios-14')
        self.setProperty('configuration', 'release')
        self.expectRemoteCommands(
            ExpectShell(workdir='wkdir',
                        command=['python3', 'Tools/Scripts/install-built-product', '--platform=ios-14', '--release'],
                        logEnviron=True,
                        timeout=1200,
                        )
            + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='Installed Built Product')
        return self.runStep()

    def test_failure(self):
        self.setupStep(InstallBuiltProduct())
        self.setProperty('fullPlatform', 'ios-14')
        self.setProperty('configuration', 'debug')
        self.expectRemoteCommands(
            ExpectShell(workdir='wkdir',
                        command=['python3', 'Tools/Scripts/install-built-product', '--platform=ios-14', '--debug'],
                        logEnviron=True,
                        timeout=1200,
                        )
            + ExpectShell.log('stdio', stdout='Unexpected error.')
            + 2,
        )
        self.expectOutcome(result=FAILURE, state_string='Installed Built Product (failure)')
        return self.runStep()


class TestGenerateUploadBundleSteps(BuildStepMixinAdditions, unittest.TestCase):
    def setUp(self):
        def fakeaddStepsAfterCurrentStep(self, step_factories):
            self.addedStepsAfterCurrentStep = step_factories

        FakeBuild.addedStepsAfterCurrentStep = []
        FakeBuild.addStepsAfterCurrentStep = fakeaddStepsAfterCurrentStep
        self.longMessage = True
        return self.setUpBuildStep()

    def tearDown(self):
        return self.tearDownBuildStep()

    def setUpPropertiesForTest(self):
        self.setProperty('fullPlatform', 'gtk')
        self.setProperty('configuration', 'release')
        self.setProperty('buildername', 'GTK-Linux-64-bit-Release-Build')
        self.setProperty('archive_revision', '261281@main')

    def test_success_generate_minibrowser_bundle(self):
        self.setupStep(GenerateMiniBrowserBundle())
        self.setUpPropertiesForTest()
        self.expectRemoteCommands(
            ExpectShell(workdir='wkdir',
                        command=['Tools/Scripts/generate-bundle', '--builder-name', 'GTK-Linux-64-bit-Release-Build', '--bundle=MiniBrowser', '--platform=gtk', '--release', '--revision=261281@main'],
                        logEnviron=True,
                        timeout=1200,
                        )
            + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='generated minibrowser bundle')
        rc = self.runStep()
        self.assertTrue(UploadMiniBrowserBundleViaSftp() in self.build.addedStepsAfterCurrentStep)
        return rc

    def test_failure_generate_minibrowser_bundle(self):
        self.setupStep(GenerateMiniBrowserBundle())
        self.setUpPropertiesForTest()
        self.expectRemoteCommands(
            ExpectShell(workdir='wkdir',
                        command=['Tools/Scripts/generate-bundle', '--builder-name', 'GTK-Linux-64-bit-Release-Build', '--bundle=MiniBrowser', '--platform=gtk', '--release', '--revision=261281@main'],
                        logEnviron=True,
                        timeout=1200,
                        )
            + 2,
        )
        self.expectOutcome(result=FAILURE, state_string='generated minibrowser bundle (failure)')
        rc = self.runStep()
        self.assertTrue(UploadMiniBrowserBundleViaSftp() not in self.build.addedStepsAfterCurrentStep)
        return rc

    def test_success_generate_jsc_bundle(self):
        self.setupStep(GenerateJSCBundle())
        self.setUpPropertiesForTest()
        self.expectRemoteCommands(
            ExpectShell(workdir='wkdir',
                        command=['Tools/Scripts/generate-bundle', '--builder-name', 'GTK-Linux-64-bit-Release-Build', '--bundle=jsc', '--syslibs=bundle-all', '--platform=gtk', '--release', '--revision=261281@main'],
                        logEnviron=True,
                        timeout=1200,
                        )
            + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='generated jsc bundle')
        rc = self.runStep()
        self.assertTrue(UploadJSCBundleViaSftp() in self.build.addedStepsAfterCurrentStep)
        return rc

    def test_failure_generate_jsc_bundle(self):
        self.setupStep(GenerateJSCBundle())
        self.setUpPropertiesForTest()
        self.expectRemoteCommands(
            ExpectShell(workdir='wkdir',
                        command=['Tools/Scripts/generate-bundle', '--builder-name', 'GTK-Linux-64-bit-Release-Build', '--bundle=jsc', '--syslibs=bundle-all', '--platform=gtk', '--release', '--revision=261281@main'],
                        logEnviron=True,
                        timeout=1200,
                        )
            + 2,
        )
        self.expectOutcome(result=FAILURE, state_string='generated jsc bundle (failure)')
        rc = self.runStep()
        self.assertTrue(UploadJSCBundleViaSftp() not in self.build.addedStepsAfterCurrentStep)
        return rc

    def test_parameters_upload_minibrowser_bundle_sftp(self):
        self.setupStep(UploadMiniBrowserBundleViaSftp())
        self.setUpPropertiesForTest()
        self.expectRemoteCommands(
            ExpectShell(workdir='wkdir',
                        command=['python3', 'Tools/CISupport/Shared/transfer-archive-via-sftp', '--remote-config-file', '../../remote-minibrowser-bundle-upload-config.json', '--remote-file', 'MiniBrowser_gtk_261281@main.zip', 'WebKitBuild/MiniBrowser_gtk_release.zip'],
                        logEnviron=True,
                        timeout=1200,
                        )
            + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='uploaded minibrowser bundle via sftp')
        return self.runStep()

    def test_parameters_upload_jsc_bundle_sftp(self):
        self.setupStep(UploadJSCBundleViaSftp())
        self.setUpPropertiesForTest()
        self.expectRemoteCommands(
            ExpectShell(workdir='wkdir',
                        command=['python3', 'Tools/CISupport/Shared/transfer-archive-via-sftp', '--remote-config-file', '../../remote-jsc-bundle-upload-config.json', '--remote-file', '261281@main.zip', 'WebKitBuild/jsc_gtk_release.zip'],
                        logEnviron=True,
                        timeout=1200,
                        )
            + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='uploaded jsc bundle via sftp')
        return self.runStep()


class TestCheckIfNeededUpdateCrossTargetImageSteps(BuildStepMixinAdditions, unittest.TestCase):
    def setUp(self):
        def fakeaddStepsAfterCurrentStep(self, step_factories):
            self.addedStepsAfterCurrentStep = step_factories

        FakeBuild.addedStepsAfterCurrentStep = []
        FakeBuild.addStepsAfterCurrentStep = fakeaddStepsAfterCurrentStep
        self.longMessage = True
        return self.setUpBuildStep()

    def tearDown(self):
        return self.tearDownBuildStep()

    def setUpPropertiesForTest(self):
        self.setProperty('fullPlatform', 'wpe')
        self.setProperty('configuration', 'release')
        self.setProperty('buildername', 'WPE-Linux-RPi4-64bits-Mesa-Release-Perf-Build')
        self.setProperty('archive_revision', '265300@main')
        self.setProperty('additionalArguments', ['--cross-target=rpi4-64bits-mesa'])

    def test_success_check_if_deployed_cross_target_image_is_updated(self):
        self.setupStep(CheckIfNeededUpdateDeployedCrossTargetImage())
        self.setUpPropertiesForTest()
        self.expectRemoteCommands(
            ExpectShell(workdir='wkdir',
                        command=['python3', 'Tools/Scripts/cross-toolchain-helper', '--check-if-image-is-updated', 'deployed', '--cross-target=rpi4-64bits-mesa'],
                        logEnviron=True,
                        timeout=1200,
                        )
            + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='deployed cross target image is updated')
        rc = self.runStep()
        self.assertTrue(BuildAndDeployCrossTargetImage() not in self.build.addedStepsAfterCurrentStep)
        return rc

    def test_failure_check_if_deployed_cross_target_image_is_updated(self):
        self.setupStep(CheckIfNeededUpdateDeployedCrossTargetImage())
        self.setUpPropertiesForTest()
        self.expectRemoteCommands(
            ExpectShell(workdir='wkdir',
                        command=['python3', 'Tools/Scripts/cross-toolchain-helper', '--check-if-image-is-updated', 'deployed', '--cross-target=rpi4-64bits-mesa'],
                        logEnviron=True,
                        timeout=1200,
                        )
            + 1,
        )
        self.expectOutcome(result=FAILURE, state_string='deployed cross target image is updated (failure)')
        self.assertTrue(BuildAndDeployCrossTargetImage() not in self.build.addedStepsAfterCurrentStep)
        rc = self.runStep()
        self.assertTrue(BuildAndDeployCrossTargetImage() in self.build.addedStepsAfterCurrentStep)
        return rc

    def test_success_check_if_running_cross_target_image_is_updated(self):
        self.setupStep(CheckIfNeededUpdateRunningCrossTargetImage())
        self.setUpPropertiesForTest()
        self.expectRemoteCommands(
            ExpectShell(workdir='wkdir',
                        command=['python3', 'Tools/Scripts/cross-toolchain-helper', '--check-if-image-is-updated', 'running'],
                        logEnviron=True,
                        timeout=1200,
                        )
            + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='running cross target image is updated')
        rc = self.runStep()
        self.assertTrue(RebootWithUpdatedCrossTargetImage() not in self.build.addedStepsAfterCurrentStep)
        return rc

    def test_failure_check_if_running_cross_target_image_is_updated(self):
        self.setupStep(CheckIfNeededUpdateRunningCrossTargetImage())
        self.setUpPropertiesForTest()
        self.expectRemoteCommands(
            ExpectShell(workdir='wkdir',
                        command=['python3', 'Tools/Scripts/cross-toolchain-helper', '--check-if-image-is-updated', 'running'],
                        logEnviron=True,
                        timeout=1200,
                        )
            + 1,
        )
        self.expectOutcome(result=FAILURE, state_string='running cross target image is updated (failure)')
        self.assertTrue(RebootWithUpdatedCrossTargetImage() not in self.build.addedStepsAfterCurrentStep)
        rc = self.runStep()
        self.assertTrue(RebootWithUpdatedCrossTargetImage() in self.build.addedStepsAfterCurrentStep)
        return rc


class TestRunWebDriverTests(BuildStepMixinAdditions, unittest.TestCase):
    def setUp(self):
        self.longMessage = True
        self.jsonFileName = 'webdriver_tests.json'
        return self.setUpBuildStep()

    def tearDown(self):
        return self.tearDownBuildStep()

    def configureStep(self):
        self.setupStep(RunWebDriverTests())
        self.setProperty('buildername', 'GTK-Linux-64-bit-Release-WebDriver-Tests')
        self.setProperty('buildnumber', '101')
        self.setProperty('workername', 'gtk-linux-bot-14')

    def test_success(self):
        self.configureStep()
        self.setProperty('fullPlatform', 'gtk')
        self.setProperty('configuration', 'release')
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                logEnviron=True,
                logfiles={'json': self.jsonFileName},
                command=['/bin/sh', '-c', 'python3 Tools/Scripts/run-webdriver-tests --json-output=webdriver_tests.json --release > logs.txt 2>&1'],
                timeout=5400
            ) + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='webdriver-tests')
        return self.runStep()

    def test_failure(self):
        self.configureStep()
        self.setProperty('fullPlatform', 'gtk')
        self.setProperty('configuration', 'release')
        self.expectRemoteCommands(
            ExpectShell(
                workdir='wkdir',
                logEnviron=True,
                logfiles={'json': self.jsonFileName},
                command=['/bin/sh', '-c', 'python3 Tools/Scripts/run-webdriver-tests --json-output=webdriver_tests.json --release > logs.txt 2>&1'],
                timeout=5400
            ) + 1,
        )
        self.expectOutcome(result=FAILURE, state_string='webdriver-tests (failure)')
        return self.runStep()


class current_hostname(object):
    def __init__(self, hostname):
        self.hostname = hostname
        self.saved_hostname = None

    def __enter__(self):
        from . import steps
        self.saved_hostname = steps.CURRENT_HOSTNAME
        steps.CURRENT_HOSTNAME = self.hostname

    def __exit__(self, type, value, tb):
        from . import steps
        steps.CURRENT_HOSTNAME = self.saved_hostname


class TestGenerateS3URL(BuildStepMixinAdditions, unittest.TestCase):
    def setUp(self):
        self.longMessage = True
        return self.setUpBuildStep()

    def tearDown(self):
        return self.tearDownBuildStep()

    def configureStep(self, identifier='mac-highsierra-x86_64-release', extension='zip', content_type=None):
        self.setupStep(GenerateS3URL(identifier, extension=extension, content_type=content_type))
        self.setProperty('archive_revision', '1234')

    def disabled_test_success(self):
        # TODO: Figure out how to pass logs to unit-test for MasterShellCommand steps
        self.configureStep()
        self.expectLocalCommands(
            ExpectMasterShellCommand(command=['python3',
                                              '../Shared/generate-s3-url',
                                              '--revision', '1234',
                                              '--identifier', 'mac-highsierra-x86_64-release',
                                              '--extension', 'zip',
                                              ])
            + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='Generated S3 URL')
        with current_hostname(BUILD_WEBKIT_HOSTNAMES[0]):
            return self.runStep()

    def test_failure(self):
        self.configureStep('ios-simulator-16-x86_64-debug')
        self.expectLocalCommands(
            ExpectMasterShellCommand(command=['python3',
                                              '../Shared/generate-s3-url',
                                              '--revision', '1234',
                                              '--identifier', 'ios-simulator-16-x86_64-debug',
                                              '--extension', 'zip',
                                              ])
            + 2,
        )
        self.expectOutcome(result=FAILURE, state_string='Failed to generate S3 URL')

        try:
            with current_hostname(BUILD_WEBKIT_HOSTNAMES[0]), open(os.devnull, 'w') as null:
                sys.stdout = null
                return self.runStep()
        finally:
            sys.stdout = sys.__stdout__

    def test_failure_with_extension(self):
        self.configureStep('macos-arm64-release-compile-webkit', extension='txt', content_type='text/plain')
        self.expectLocalCommands(
            ExpectMasterShellCommand(command=['python3',
                                              '../Shared/generate-s3-url',
                                              '--revision', '1234',
                                              '--identifier', 'macos-arm64-release-compile-webkit',
                                              '--extension', 'txt',
                                              '--content-type', 'text/plain',
                                              ])
            + 2,
        )
        self.expectOutcome(result=FAILURE, state_string='Failed to generate S3 URL')

        try:
            with current_hostname(BUILD_WEBKIT_HOSTNAMES[0]), open(os.devnull, 'w') as null:
                sys.stdout = null
                return self.runStep()
        finally:
            sys.stdout = sys.__stdout__

    def test_skipped(self):
        self.configureStep()
        self.expectOutcome(result=SKIPPED, state_string='Generated S3 URL (skipped)')
        with current_hostname('something-other-than-steps.BUILD_WEBKIT_HOSTNAMES'):
            return self.runStep()


class TestUploadFileToS3(BuildStepMixinAdditions, unittest.TestCase):
    def setUp(self):
        self.longMessage = True
        return self.setUpBuildStep()

    def tearDown(self):
        return self.tearDownBuildStep()

    def configureStep(self, file='WebKitBuild/release.zip', content_type=None):
        self.setupStep(UploadFileToS3(file, content_type=content_type))
        self.build.s3url = 'https://test-s3-url'

    def test_success(self):
        self.configureStep()
        self.assertEqual(UploadFileToS3.haltOnFailure, True)
        self.assertEqual(UploadFileToS3.flunkOnFailure, True)
        self.expectRemoteCommands(
            ExpectShell(workdir='wkdir',
                        env=dict(UPLOAD_URL='https://test-s3-url'),
                        logEnviron=False,
                        command=['python3', 'Tools/Scripts/upload-file-to-url', '--filename', 'WebKitBuild/release.zip'],
                        timeout=1860,
                        )
            + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='Uploaded WebKitBuild/release.zip to S3')
        with current_hostname(BUILD_WEBKIT_HOSTNAMES[0]):
            return self.runStep()

    def test_success_content_type(self):
        self.configureStep(file='build-log.txt', content_type='text/plain')
        self.assertEqual(UploadFileToS3.haltOnFailure, True)
        self.assertEqual(UploadFileToS3.flunkOnFailure, True)
        self.expectRemoteCommands(
            ExpectShell(workdir='wkdir',
                        env=dict(UPLOAD_URL='https://test-s3-url'),
                        logEnviron=False,
                        command=['python3', 'Tools/Scripts/upload-file-to-url', '--filename', 'build-log.txt', '--content-type', 'text/plain'],
                        timeout=1860,
                        )
            + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='Uploaded build-log.txt to S3')
        with current_hostname(BUILD_WEBKIT_HOSTNAMES[0]):
            return self.runStep()

    def test_failure(self):
        self.configureStep()
        self.expectRemoteCommands(
            ExpectShell(workdir='wkdir',
                        env=dict(UPLOAD_URL='https://test-s3-url'),
                        logEnviron=False,
                        command=['python3', 'Tools/Scripts/upload-file-to-url', '--filename', 'WebKitBuild/release.zip'],
                        timeout=1860,
                        )
            + ExpectShell.log('stdio', stdout='''Uploading WebKitBuild/release.zip
response: <Response [403]>, 403, Forbidden
exit 1''')
            + 2,
        )
        self.expectOutcome(result=FAILURE, state_string='Failed to upload WebKitBuild/release.zip to S3. Please inform an admin.')
        with current_hostname(BUILD_WEBKIT_HOSTNAMES[0]):
            return self.runStep()

    def test_skipped(self):
        self.configureStep()
        self.expectOutcome(result=SKIPPED, state_string='Skipped upload to S3')
        with current_hostname('something-other-than-steps.BUILD_WEBKIT_HOSTNAMES'):
            return self.runStep()


class TestScanBuildSmartPointer(BuildStepMixinAdditions, unittest.TestCase):
    WORK_DIR = 'wkdir'
    EXPECTED_BUILD_COMMAND = ['/bin/sh', '-c', f'Tools/Scripts/build-and-analyze --output-dir wkdir/build/{SCAN_BUILD_OUTPUT_DIR} --only-smart-pointers --analyzer-path=wkdir/llvm-project/build/bin/clang --scan-build-path=../llvm-project/clang/tools/scan-build/bin/scan-build --sdkroot=macosx 2>&1 | python3 Tools/Scripts/filter-static-analyzer']

    def setUp(self):
        return self.setUpBuildStep()

    def tearDown(self):
        return self.tearDownBuildStep()

    def configureStep(self):
        self.setupStep(ScanBuildSmartPointer())

    def test_failure(self):
        self.configureStep()
        self.setProperty('builddir', self.WORK_DIR)

        self.expectRemoteCommands(
            ExpectShell(workdir=self.WORK_DIR,
                        command=['/bin/sh', '-c', f'/bin/rm -rf wkdir/build/{SCAN_BUILD_OUTPUT_DIR}'],
                        timeout=2 * 60 * 60) + 0,
            ExpectShell(workdir=self.WORK_DIR,
                        command=self.EXPECTED_BUILD_COMMAND,
                        timeout=2 * 60 * 60)
            + ExpectShell.log('stdio', stdout='scan-build-static-analyzer: No bugs found.\nTotal issue count: 123\n')
            + 0
        )
        self.expectOutcome(result=FAILURE, state_string='ANALYZE FAILED: scan-build-smart-pointer found 123 issues (failure)')
        return self.runStep()

    def test_success(self):
        self.configureStep()
        self.setProperty('builddir', self.WORK_DIR)

        self.expectRemoteCommands(
            ExpectShell(workdir=self.WORK_DIR,
                        command=['/bin/sh', '-c', f'/bin/rm -rf wkdir/build/{SCAN_BUILD_OUTPUT_DIR}'],
                        timeout=2 * 60 * 60)
            + 0,
            ExpectShell(workdir=self.WORK_DIR,
                        command=self.EXPECTED_BUILD_COMMAND,
                        timeout=2 * 60 * 60)
            + ExpectShell.log('stdio', stdout='ANALYZE SUCCEEDED No issues found.\n')
            + 0
        )
        self.expectOutcome(result=SUCCESS, state_string='scan-build-smart-pointer found 0 issues')
        return self.runStep()

    def test_success_with_issues(self):
        self.configureStep()
        self.setProperty('builddir', self.WORK_DIR)

        self.expectRemoteCommands(
            ExpectShell(workdir=self.WORK_DIR,
                        command=['/bin/sh', '-c', f'/bin/rm -rf wkdir/build/{SCAN_BUILD_OUTPUT_DIR}'],
                        timeout=2 * 60 * 60)
            + 0,
            ExpectShell(workdir=self.WORK_DIR,
                        command=self.EXPECTED_BUILD_COMMAND,
                        timeout=2 * 60 * 60)
            + ExpectShell.log('stdio', stdout='ANALYZE SUCCEEDED\n Total issue count: 300\n')
            + 0
        )
        self.expectOutcome(result=SUCCESS, state_string='scan-build-smart-pointer found 300 issues')
        return self.runStep()


class TestParseStaticAnalyzerResults(BuildStepMixinAdditions, unittest.TestCase):
    def setUp(self):
        return self.setUpBuildStep()

    def tearDown(self):
        return self.tearDownBuildStep()

    def configureStep(self):
        self.setupStep(ParseStaticAnalyzerResults())

    def test_success(self):
        self.configureStep()
        self.setProperty('builddir', 'wkdir')
        self.setProperty('buildnumber', 1234)

        self.expectRemoteCommands(
            ExpectShell(workdir='wkdir',
                        command=['python3', 'Tools/Scripts/generate-dirty-files', f'wkdir/build/{SCAN_BUILD_OUTPUT_DIR}', '--output-dir', 'wkdir/smart-pointer-result-archive/1234', '--build-dir', 'wkdir/build'])
            + ExpectShell.log('stdio', stdout='Total (24247) WebKit (327) WebCore (23920)\n')
            + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string=' Issues by project: Total (24247) WebKit (327) WebCore (23920)\n')
        return self.runStep()


class TestCompareStaticAnalyzerResults(BuildStepMixinAdditions, unittest.TestCase):
    def setUp(self):
        return self.setUpBuildStep()

    def tearDown(self):
        return self.tearDownBuildStep()

    def configureStep(self):
        self.setupStep(CompareStaticAnalyzerResults())

    def test_success_no_issues(self):
        self.configureStep()
        self.setProperty('builddir', 'wkdir')
        self.setProperty('buildnumber', 2)

        self.expectRemoteCommands(
            ExpectShell(workdir='wkdir',
                        command=['python3', 'Tools/Scripts/compare-static-analysis-results', 'wkdir/smart-pointer-result-archive/2', '--scan-build-path', '../llvm-project/clang/tools/scan-build/bin/scan-build', '--build-output', SCAN_BUILD_OUTPUT_DIR, '--check-expectations'],)
            + ExpectShell.log('stdio', stdout='')
            + 0,
        )
        self.expectOutcome(result=SUCCESS, state_string='Found no unexpected results')
        return self.runStep()

    def test_new_issues(self):
        self.configureStep()
        self.setProperty('builddir', 'wkdir')
        self.setProperty('buildnumber', 1234)

        self.expectRemoteCommands(
            ExpectShell(workdir='wkdir',
                        command=['python3', 'Tools/Scripts/compare-static-analysis-results', 'wkdir/smart-pointer-result-archive/1234', '--scan-build-path', '../llvm-project/clang/tools/scan-build/bin/scan-build', '--build-output', SCAN_BUILD_OUTPUT_DIR, '--check-expectations'],)
            + ExpectShell.log('stdio', stdout='Total unexpected failing files: 123\nTotal unexpected passing files: 456\nTotal unexpected issues: 789\n')
            + 0,
        )
        self.expectOutcome(result=FAILURE, state_string='Unexpected failing files: 123 Unexpected passing files: 456 Unexpected issues: 789 (failure)')
        return self.runStep()


class TestUpdateSmartPointerBaseline(BuildStepMixinAdditions, unittest.TestCase):
    def setUp(self):
        return self.setUpBuildStep()

    def tearDown(self):
        return self.tearDownBuildStep()

    def configureStep(self):
        self.setupStep(UpdateSmartPointerBaseline())

    def test_success(self):
        self.configureStep()
        self.setProperty('builddir', 'wkdir')
        self.setProperty('buildnumber', 2)

        self.expectRemoteCommands(
            ExpectShell(workdir='wkdir',
                        command=['/bin/sh', '-c', 'rm -r wkdir/smart-pointer-result-archive/baseline'],)
            + ExpectShell.log('stdio', stdout='')
            + 0,
            ExpectShell(workdir='wkdir',
                        command=['/bin/sh', '-c', 'cp -r wkdir/smart-pointer-result-archive/2 wkdir/smart-pointer-result-archive/baseline'],)
            + ExpectShell.log('stdio', stdout='')
            + 0,
        )
        self.expectOutcome(result=SUCCESS)
        return self.runStep()

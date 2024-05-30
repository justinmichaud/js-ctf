#!/usr/bin/env perl

# Copyright (C) 2017 Apple Inc. All rights reserved.
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
# THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS'' AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
# ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

# Unit tests for webkitdirs::extractNonMacOSHostConfiguration.

use strict;
use warnings;

use Config;
use Test::More;
use webkitdirs;

my @testCases = (
{
    argValue => [],
    expectedValue => [],
    description => "Empty configuration",
},
{
    argValue => ["--debug"],
    expectedValue => ["--debug"],
    description => "Debug configuration",
},
{
    argValue => ["--release"],
    expectedValue => ["--release"],
    description => "Release configuration",
},
{
    argValue => ["--debug", "--device"],
    expectedValue => ["--debug"],
    description => "Debug with device",
},
{
    argValue => ["--debug", "--ios-simulator"],
    expectedValue => ["--debug"],
    description => "Debug with simulator",
},
{
    argValue => ["--debug", "--gtk"],
    expectedValue => ["--debug"],
    description => "Debug with GTK",
},
{
    argValue => ["--debug", "--wincairo"],
    expectedValue => ["--debug"],
    description => "Debug with WinCairo",
},
{
    argValue => ["--clean"],
    expectedValue => ["--clean"],
    description => "Clean",
},
{
    argValue => ["--debug", "--device", "ARCHS=arm64"],
    expectedValue => ["--debug"],
    description => "Debug with device architecture",
},
{
    argValue => ["--debug", "SDKROOT=iphoneos", "ARCHS=arm64"],
    expectedValue => ["--debug"],
    description => "Debug with device SDK",
},
{
    argValue => ["--debug", "ARCHS=x86_64"],
    expectedValue => ["--debug", "ARCHS=x86_64"],
    description => "Debug 64-bit build",
},
);

plan(tests => 1 * @testCases);
print "\n";
foreach my $testCase (@testCases) {
    my @result = extractNonMacOSHostConfiguration($testCase->{argValue});
    my @expected = @{$testCase->{expectedValue}};
    is_deeply(
        \@result,
        \@expected,
        "prependToEnvironmentVariableList: $testCase->{description}");
}

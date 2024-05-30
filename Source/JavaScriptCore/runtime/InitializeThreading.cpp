/*
 * Copyright (C) 2008-2024 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer. 
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution. 
 * 3.  Neither the name of Apple Inc. ("Apple") nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "InitializeThreading.h"

#include "AssemblyComments.h"
#include "ExecutableAllocator.h"
#include "InPlaceInterpreter.h"
#include "JITOperationList.h"
#include "JSCConfig.h"
#include "JSCPtrTag.h"
#include "LLIntData.h"
#include "NativeCalleeRegistry.h"
#include "Options.h"
#include "RegisterTZoneTypes.h"
#include "SuperSampler.h"
#include "VMTraps.h"
#include "WasmCapabilities.h"
#include "WasmFaultSignalHandler.h"
#include "WasmThunks.h"
#include <mutex>
#include <wtf/TZoneMallocInitialization.h>
#include <wtf/Threading.h>
#include <wtf/threads/Signals.h>

#if !USE(SYSTEM_MALLOC)
#include <bmalloc/BPlatform.h>
#if BUSE(LIBPAS)
#include <bmalloc/pas_scavenger.h>
#endif
#endif

#if ENABLE(LLVM_PROFILE_GENERATION)
extern "C" char __llvm_profile_filename[] = "/private/tmp/WebKitPGO/JavaScriptCore_%m_pid%p%c.profraw";
#endif

namespace JSC {

static_assert(sizeof(bool) == 1, "LLInt and JIT assume sizeof(bool) is always 1 when touching it directly from assembly code.");

enum class JSCProfileTag { };

void initialize()
{
    static std::once_flag onceFlag;

    std::call_once(onceFlag, [] {
#if USE(TZONE_MALLOC)
        // This is needed for apps that link with the JavaScriptCore ObjC API
        if (!WTF_TZONE_IS_READY()) {
            WTF_TZONE_INIT(nullptr);
            JSC::registerTZoneTypes();
            WTF_TZONE_REGISTRATION_DONE();
        }
#endif
        WTF::initialize();
        Options::initialize();

        initializePtrTagLookup();

#if ENABLE(WRITE_BARRIER_PROFILING)
        WriteBarrierCounters::initialize();
#endif
        {
            Options::AllowUnfinalizedAccessScope scope;
            JITOperationList::initialize();
            ExecutableAllocator::initialize();
            VM::computeCanUseJIT();
            if (!g_jscConfig.vm.canUseJIT) {
                Options::useJIT() = false;
                Options::notifyOptionsChanged();
            } else {
#if CPU(ARM64E) && ENABLE(JIT)
                g_jscConfig.arm64eHashPins.initializeAtStartup();
                isARM64E_FPAC(); // Call this to initialize g_jscConfig.canUseFPAC.
#endif
            }
        }
        Options::finalize();

#if !USE(SYSTEM_MALLOC)
#if BUSE(LIBPAS)
        if (Options::libpasScavengeContinuously())
            pas_scavenger_disable_shut_down();
#endif
#endif

        JITOperationList::populatePointersInJavaScriptCore();

        AssemblyCommentRegistry::initialize();
#if ENABLE(WEBASSEMBLY)
        if (Options::useWasmIPInt() || Options::useIPIntWrappers())
            IPInt::initialize();
#endif
        LLInt::initialize();
        DisallowGC::initialize();

        initializeSuperSampler();
        Thread& thread = Thread::current();
        thread.setSavedLastStackTop(thread.stack().origin());

        NativeCalleeRegistry::initialize();
#if ENABLE(WEBASSEMBLY) && ENABLE(JIT)
        if (Wasm::isSupported()) {
            Wasm::Thunks::initialize();
        }
#endif

        if (VM::isInMiniMode())
            WTF::fastEnableMiniMode();

        if (Wasm::isSupported() || !Options::usePollingTraps()) {
            if (!Options::usePollingTraps())
                VMTraps::initializeSignals();
            if (Wasm::isSupported())
                Wasm::prepareSignalingMemory();
        }

        WTF::compilerFence();
        RELEASE_ASSERT(!g_jscConfig.initializeHasBeenCalled);
        g_jscConfig.initializeHasBeenCalled = true;
#if OS(WINDOWS) && ENABLE(WEBASSEMBLY)
        g_wtfConfigForLLInt = g_wtfConfig;
#endif
    });
}

} // namespace JSC

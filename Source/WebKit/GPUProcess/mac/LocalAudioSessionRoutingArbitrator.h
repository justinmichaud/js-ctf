/*
 * Copyright (C) 2021 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#if ENABLE(ROUTING_ARBITRATION) && HAVE(AVAUDIO_ROUTING_ARBITER)

#include "AudioSessionRoutingArbitratorProxy.h"
#include <wtf/ThreadSafeWeakPtr.h>
#include <wtf/WeakRef.h>

namespace WTF {
class Logger;
}

namespace WebKit {

class GPUConnectionToWebProcess;

class LocalAudioSessionRoutingArbitrator final
    : public WebCore::AudioSessionRoutingArbitrationClient {
    WTF_MAKE_FAST_ALLOCATED;

    friend UniqueRef<LocalAudioSessionRoutingArbitrator> WTF::makeUniqueRefWithoutFastMallocCheck<LocalAudioSessionRoutingArbitrator>(GPUConnectionToWebProcess&);
public:
    static UniqueRef<LocalAudioSessionRoutingArbitrator> create(GPUConnectionToWebProcess&);
    virtual ~LocalAudioSessionRoutingArbitrator();

    using WeakValueType = WebCore::AudioSessionRoutingArbitrationClient;

    void processDidTerminate();

private:
    LocalAudioSessionRoutingArbitrator(GPUConnectionToWebProcess&);

    // AudioSessionRoutingArbitrationClient
    void beginRoutingArbitrationWithCategory(WebCore::AudioSession::CategoryType, ArbitrationCallback&&) final;
    void leaveRoutingAbritration() final;

    Logger& logger();
    ASCIILiteral logClassName() const { return "LocalAudioSessionRoutingArbitrator"_s; }
    WTFLogChannel& logChannel() const;
    const void* logIdentifier() const final { return m_logIdentifier; }
    bool canLog() const final;

    ThreadSafeWeakPtr<GPUConnectionToWebProcess> m_connectionToWebProcess;
    const void* m_logIdentifier;
};

}

#endif

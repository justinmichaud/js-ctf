/*
 * Copyright (C) 2018-2023 Apple Inc. All rights reserved.
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

#if ENABLE(APPLE_PAY)

#include "ApplePaySetupConfiguration.h"
#include "JSDOMPromiseDeferred.h"
#include <WebCore/ActiveDOMObject.h>
#include <WebCore/JSDOMPromiseDeferredForward.h>
#include <wtf/Forward.h>
#include <wtf/Ref.h>
#include <wtf/RefCounted.h>
#include <wtf/text/WTFString.h>

namespace WebCore {

class ApplePaySetupFeature;
class Document;

class ApplePaySetup : public ActiveDOMObject, public RefCounted<ApplePaySetup> {
public:
    static Ref<ApplePaySetup> create(ScriptExecutionContext&, ApplePaySetupConfiguration&&);

    using SetupFeaturesPromise = DOMPromiseDeferred<IDLSequence<IDLInterface<ApplePaySetupFeature>>>;
    void getSetupFeatures(Document&, SetupFeaturesPromise&&);

    using BeginPromise = DOMPromiseDeferred<IDLBoolean>;
    void begin(Document&, Vector<Ref<ApplePaySetupFeature>>&&, BeginPromise&&);

    // ActiveDOMObject.
    void ref() const final { RefCounted::ref(); }
    void deref() const final { RefCounted::deref(); }

private:
    ApplePaySetup(ScriptExecutionContext&, ApplePaySetupConfiguration&&);

    // ActiveDOMObject
    void stop() final;
    void suspend(ReasonForSuspension) final;

    ApplePaySetupConfiguration m_configuration;
    std::optional<SetupFeaturesPromise> m_setupFeaturesPromise;
    std::optional<BeginPromise> m_beginPromise;
    RefPtr<PendingActivity<ApplePaySetup>> m_pendingActivity;
};

} // namespace WebCore

#endif // ENABLE(APPLE_PAY)

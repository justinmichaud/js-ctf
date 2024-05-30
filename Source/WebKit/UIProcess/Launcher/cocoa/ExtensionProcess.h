/*
 * Copyright (C) 2024 Apple Inc.  All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include "ExtensionCapability.h"
#include "ExtensionCapabilityGrant.h"

#include <wtf/OSObjectPtr.h>
#include <wtf/RetainPtr.h>

#if USE(EXTENSIONKIT)
OBJC_CLASS BEWebContentProcess;
OBJC_CLASS BENetworkingProcess;
OBJC_CLASS BERenderingProcess;
OBJC_CLASS BEProcessCapability;
OBJC_CLASS _SEExtensionProcess;
OBJC_PROTOCOL(BEProcessCapabilityGrant);
OBJC_PROTOCOL(UIInteraction);

namespace WebKit {

#if USE(LEGACY_EXTENSIONKIT_SPI)
using ExtensionProcessVariant = std::variant<RetainPtr<BEWebContentProcess>, RetainPtr<BENetworkingProcess>, RetainPtr<BERenderingProcess>, RetainPtr<_SEExtensionProcess>>;
#else
using ExtensionProcessVariant = std::variant<RetainPtr<BEWebContentProcess>, RetainPtr<BENetworkingProcess>, RetainPtr<BERenderingProcess>>;
#endif

class ExtensionCapability;

class ExtensionProcess {
public:
    ExtensionProcess(BEWebContentProcess *);
    ExtensionProcess(BENetworkingProcess *);
    ExtensionProcess(BERenderingProcess *);
#if USE(LEGACY_EXTENSIONKIT_SPI)
    ExtensionProcess(_SEExtensionProcess *);
#endif

    void invalidate() const;
    OSObjectPtr<xpc_connection_t> makeLibXPCConnection() const;
    RetainPtr<BEProcessCapabilityGrant> grantCapability(BEProcessCapability *) const;
    PlatformGrant grantCapability(const PlatformCapability&) const;
    RetainPtr<UIInteraction> createVisibilityPropagationInteraction() const;

private:
    ExtensionProcessVariant m_process;
};

} // namespace WebKit

#endif // USE(EXTENSIONKIT)

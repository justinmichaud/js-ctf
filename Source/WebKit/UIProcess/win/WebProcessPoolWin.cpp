/*
 * Copyright (C) 2010 Apple Inc. All rights reserved.
 * Copyright (C) 2017 Sony Interactive Entertainment Inc.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS AS IS''
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

#include "config.h"
#include "WebProcessPool.h"

#include "WebProcessCreationParameters.h"
#include <WebCore/NotImplemented.h>

#if ENABLE(REMOTE_INSPECTOR)
#include "AutomationClientWin.h"
#include <JavaScriptCore/RemoteInspector.h>
#include <JavaScriptCore/RemoteInspectorServer.h>
#include <WebCore/WebCoreBundleWin.h>
#include <wtf/text/StringToIntegerConversion.h>
#endif

namespace WebKit {

#if ENABLE(REMOTE_INSPECTOR)
static void initializeRemoteInspectorServer(StringView address)
{
    if (Inspector::RemoteInspectorServer::singleton().isRunning())
        return;

    auto pos = address.find(':');
    if (pos == notFound)
        return;

    auto host = address.left(pos);
    auto port = parseInteger<uint16_t>(address.substring(pos + 1));
    if (!port)
        return;

    auto backendCommands = WebCore::webKitBundlePath({ "WebKit.Resources"_s, "WebInspectorUI"_s, "Protocol"_s, "InspectorBackendCommands.js"_s });
    Inspector::RemoteInspector::singleton().setBackendCommandsPath(backendCommands);
    Inspector::RemoteInspectorServer::singleton().start(host.utf8().data(), port.value());
}
#endif

void WebProcessPool::platformInitialize(NeedsGlobalStaticInitialization)
{
#if ENABLE(REMOTE_INSPECTOR)
    if (const char* address = getenv("WEBKIT_INSPECTOR_SERVER"))
        initializeRemoteInspectorServer(StringView::fromLatin1(address));

    // Currently the socket port Remote Inspector can have only one client at most.
    // Therefore, if multiple process pools are created, the first one is targeted and the second and subsequent ones are ignored.
    if (!Inspector::RemoteInspector::singleton().client())
        setAutomationClient(WTF::makeUnique<AutomationClient>(*this));
#endif
}

void WebProcessPool::platformInitializeNetworkProcess(NetworkProcessCreationParameters&)
{
    notImplemented();
}

void WebProcessPool::platformInitializeWebProcess(const WebProcessProxy&, WebProcessCreationParameters&)
{
    notImplemented();
}

void WebProcessPool::platformInvalidateContext()
{
    notImplemented();
}

void WebProcessPool::platformResolvePathsForSandboxExtensions()
{
}

} // namespace WebKit

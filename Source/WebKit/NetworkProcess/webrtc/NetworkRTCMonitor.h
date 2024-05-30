/*
 * Copyright (C) 2017 Apple Inc. All rights reserved.
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

#if USE(LIBWEBRTC)

#include "RTCNetwork.h"
#include <WebCore/LibWebRTCMacros.h>
#include <wtf/WeakPtr.h>

ALLOW_COMMA_BEGIN

#include <webrtc/rtc_base/thread.h>
#include <webrtc/rtc_base/network.h>

ALLOW_COMMA_END


namespace WebKit {
class NetworkRTCMonitor;
}

namespace WTF {
template<typename T> struct IsDeprecatedWeakRefSmartPointerException;
template<> struct IsDeprecatedWeakRefSmartPointerException<WebKit::NetworkRTCMonitor> : std::true_type { };
}

namespace IPC {
class Connection;
class Decoder;
}

namespace WebKit {

class NetworkRTCProvider;

class NetworkRTCMonitor final : public CanMakeWeakPtr<NetworkRTCMonitor> {
public:
    explicit NetworkRTCMonitor(NetworkRTCProvider& rtcProvider) : m_rtcProvider(rtcProvider) { }
    ~NetworkRTCMonitor();

    void didReceiveMessage(IPC::Connection&, IPC::Decoder&);
    void stopUpdating();
    bool isStarted() const { return m_isStarted; }
    NetworkRTCProvider& rtcProvider() { return m_rtcProvider; }

    void onNetworksChanged(const Vector<RTCNetwork>&, const RTCNetwork::IPAddress&, const RTCNetwork::IPAddress&);

    const RTCNetwork::IPAddress& ipv4() const;
    const RTCNetwork::IPAddress& ipv6()  const;

private:
    void startUpdatingIfNeeded();

    NetworkRTCProvider& m_rtcProvider;
    std::unique_ptr<rtc::BasicNetworkManager> m_manager;
    bool m_isStarted { false };
};

} // namespace WebKit

#endif // USE(LIBWEBRTC)

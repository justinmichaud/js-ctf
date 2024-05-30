/*
 * Copyright (C) 2015 Apple Inc. All rights reserved.
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

#include "NavigationActionData.h"
#include "NetworkActivityTracker.h"
#include "PolicyDecision.h"
#include "WebPageProxyIdentifier.h"
#include <WebCore/BlobDataFileReference.h>
#include <WebCore/FrameIdentifier.h>
#include <WebCore/PageIdentifier.h>
#include <WebCore/ResourceLoaderOptions.h>
#include <WebCore/ResourceRequest.h>
#include <WebCore/SecurityOrigin.h>
#include <WebCore/ShouldRelaxThirdPartyCookieBlocking.h>
#include <wtf/ProcessID.h>

namespace WebKit {

enum class PreconnectOnly : bool { No, Yes };

class NetworkLoadParameters {
public:
    NetworkLoadParameters() = default;
    NetworkLoadParameters(WebPageProxyIdentifier webPageProxyID, WebCore::PageIdentifier webPageID, WebCore::FrameIdentifier webFrameID, RefPtr<WebCore::SecurityOrigin>&& topOrigin, RefPtr<WebCore::SecurityOrigin>&& sourceOrigin, WTF::ProcessID parentPID, WebCore::ResourceRequest&& request, WebCore::ContentSniffingPolicy contentSniffingPolicy, WebCore::ContentEncodingSniffingPolicy contentEncodingSniffingPolicy, WebCore::StoredCredentialsPolicy storedCredentialsPolicy, WebCore::ClientCredentialPolicy clientCredentialPolicy, bool shouldClearReferrerOnHTTPSToHTTPRedirect, bool needsCertificateInfo, bool isMainFrameNavigation, std::optional<NavigationActionData>&& mainResourceNavigationDataForAnyFrame, WebCore::ShouldRelaxThirdPartyCookieBlocking shouldRelaxThirdPartyCookieBlocking, PreconnectOnly shouldPreconnectOnly, std::optional<NavigatingToAppBoundDomain> isNavigatingToAppBoundDomain, bool hadMainFrameMainResourcePrivateRelayed, bool allowPrivacyProxy, OptionSet<WebCore::AdvancedPrivacyProtections> advancedPrivacyProtections)
        : webPageProxyID(webPageProxyID)
        , webPageID(webPageID)
        , webFrameID(webFrameID)
        , topOrigin(WTFMove(topOrigin))
        , sourceOrigin(WTFMove(sourceOrigin))
        , parentPID(parentPID)
        , request(WTFMove(request))
        , contentSniffingPolicy(contentSniffingPolicy)
        , contentEncodingSniffingPolicy(contentEncodingSniffingPolicy)
        , storedCredentialsPolicy(storedCredentialsPolicy)
        , clientCredentialPolicy(clientCredentialPolicy)
        , shouldClearReferrerOnHTTPSToHTTPRedirect(shouldClearReferrerOnHTTPSToHTTPRedirect)
        , needsCertificateInfo(needsCertificateInfo)
        , isMainFrameNavigation(isMainFrameNavigation)
        , mainResourceNavigationDataForAnyFrame(mainResourceNavigationDataForAnyFrame)
        , shouldRelaxThirdPartyCookieBlocking(shouldRelaxThirdPartyCookieBlocking)
        , shouldPreconnectOnly(shouldPreconnectOnly)
        , isNavigatingToAppBoundDomain(isNavigatingToAppBoundDomain)
        , hadMainFrameMainResourcePrivateRelayed(hadMainFrameMainResourcePrivateRelayed)
        , allowPrivacyProxy(allowPrivacyProxy)
        , advancedPrivacyProtections(advancedPrivacyProtections)
    {
    }
    
    WebPageProxyIdentifier webPageProxyID;
    WebCore::PageIdentifier webPageID;
    WebCore::FrameIdentifier webFrameID;
    RefPtr<WebCore::SecurityOrigin> topOrigin;
    RefPtr<WebCore::SecurityOrigin> sourceOrigin;
    WTF::ProcessID parentPID { 0 };
#if HAVE(AUDIT_TOKEN)
    std::optional<audit_token_t> networkProcessAuditToken;
#endif
    WebCore::ResourceRequest request;
    WebCore::ContentSniffingPolicy contentSniffingPolicy { WebCore::ContentSniffingPolicy::SniffContent };
    WebCore::ContentEncodingSniffingPolicy contentEncodingSniffingPolicy { WebCore::ContentEncodingSniffingPolicy::Default };
    WebCore::StoredCredentialsPolicy storedCredentialsPolicy { WebCore::StoredCredentialsPolicy::DoNotUse };
    WebCore::ClientCredentialPolicy clientCredentialPolicy { WebCore::ClientCredentialPolicy::CannotAskClientForCredentials };
    bool shouldClearReferrerOnHTTPSToHTTPRedirect { true };
    bool needsCertificateInfo { false };
    bool isMainFrameNavigation { false };
    std::optional<NavigationActionData> mainResourceNavigationDataForAnyFrame;
    WebCore::ShouldRelaxThirdPartyCookieBlocking shouldRelaxThirdPartyCookieBlocking { WebCore::ShouldRelaxThirdPartyCookieBlocking::No };
    Vector<RefPtr<WebCore::BlobDataFileReference>> blobFileReferences;
    PreconnectOnly shouldPreconnectOnly { PreconnectOnly::No };
    std::optional<NetworkActivityTracker> networkActivityTracker;
    std::optional<NavigatingToAppBoundDomain> isNavigatingToAppBoundDomain { NavigatingToAppBoundDomain::No };
    bool hadMainFrameMainResourcePrivateRelayed { false };
    bool allowPrivacyProxy { true };
    OptionSet<WebCore::AdvancedPrivacyProtections> advancedPrivacyProtections;
};

} // namespace WebKit

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

#include <WebCore/PrivateClickMeasurement.h>
#include <WebCore/RegistrableDomain.h>

namespace WebCore {
class CertificateInfo;
}

namespace WebKit {

namespace Daemon {
class Connection;
}

enum class PrivateClickMeasurementAttributionType : bool { Unattributed, Attributed };

class PrivateClickMeasurementManager;

namespace PCM {

class ManagerInterface {
public:
    virtual ~ManagerInterface() { };

    using AttributionDestinationSite = WebCore::PCM::AttributionDestinationSite;
    using AttributionTriggerData = WebCore::PCM::AttributionTriggerData;
    using PrivateClickMeasurement = WebCore::PrivateClickMeasurement;
    using RegistrableDomain = WebCore::RegistrableDomain;
    using SourceSite = WebCore::PCM::SourceSite;
    using ApplicationBundleIdentifier = String;

    virtual void storeUnattributed(PrivateClickMeasurement&&, CompletionHandler<void()>&&) = 0;
    virtual void handleAttribution(AttributionTriggerData&&, const URL& requestURL, WebCore::RegistrableDomain&& redirectDomain, const URL& firstPartyURL, const ApplicationBundleIdentifier&) = 0;
    virtual void clear(CompletionHandler<void()>&&) = 0;
    virtual void clearForRegistrableDomain(RegistrableDomain&&, CompletionHandler<void()>&&) = 0;
    virtual void migratePrivateClickMeasurementFromLegacyStorage(PrivateClickMeasurement&&, PrivateClickMeasurementAttributionType) = 0;
    virtual void setDebugModeIsEnabled(bool) = 0;

    virtual void toStringForTesting(CompletionHandler<void(String)>&&) const = 0;
    virtual void setOverrideTimerForTesting(bool value) = 0;
    virtual void setTokenPublicKeyURLForTesting(URL&&) = 0;
    virtual void setTokenSignatureURLForTesting(URL&&) = 0;
    virtual void setAttributionReportURLsForTesting(URL&& sourceURL, URL&& destinationURL) = 0;
    virtual void markAllUnattributedAsExpiredForTesting() = 0;
    virtual void markAttributedPrivateClickMeasurementsAsExpiredForTesting(CompletionHandler<void()>&&) = 0;
    virtual void setPCMFraudPreventionValuesForTesting(String&& unlinkableToken, String&& secretToken, String&& signature, String&& keyID) = 0;
    virtual void startTimerImmediatelyForTesting() = 0;
    virtual void setPrivateClickMeasurementAppBundleIDForTesting(ApplicationBundleIdentifier&&) = 0;
    virtual void destroyStoreForTesting(CompletionHandler<void()>&&) = 0;
    virtual void allowTLSCertificateChainForLocalPCMTesting(const WebCore::CertificateInfo&) = 0;
};

constexpr auto protocolVersionKey { "version"_s };
constexpr uint64_t protocolVersionValue { 1 };

constexpr auto protocolDebugMessageLevelKey { "debug message level"_s };
constexpr auto protocolDebugMessageKey { "debug message"_s };

constexpr auto protocolMessageTypeKey { "message type"_s };
enum class MessageType : uint8_t {
    StoreUnattributed,
    HandleAttribution,
    Clear,
    ClearForRegistrableDomain,
    MigratePrivateClickMeasurementFromLegacyStorage,
    SetDebugModeIsEnabled,
    ToStringForTesting,
    SetOverrideTimerForTesting,
    SetTokenPublicKeyURLForTesting,
    SetTokenSignatureURLForTesting,
    SetAttributionReportURLsForTesting,
    MarkAllUnattributedAsExpiredForTesting,
    MarkAttributedPrivateClickMeasurementsAsExpiredForTesting,
    SetPCMFraudPreventionValuesForTesting,
    StartTimerImmediatelyForTesting,
    SetPrivateClickMeasurementAppBundleIDForTesting,
    DestroyStoreForTesting,
    AllowTLSCertificateChainForLocalPCMTesting
};

constexpr auto protocolEncodedMessageKey { "encoded message"_s };
using EncodedMessage = Vector<uint8_t>;

void decodeMessageAndSendToManager(const Daemon::Connection&, MessageType, std::span<const uint8_t> encodedMessage, CompletionHandler<void(Vector<uint8_t>&&)>&&);
void doDailyActivityInManager();
bool messageTypeSendsReply(MessageType);

void initializePCMStorageInDirectory(const String&);

} // namespace PCM

} // namespace WebKit

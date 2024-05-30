/*
 * Copyright (C) 2019 Apple Inc. All rights reserved.
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

#include "SecurityOriginData.h"
#include <wtf/HashSet.h>
#include <wtf/HashTraits.h>
#include <wtf/text/StringHash.h>

namespace WebCore {

class Document;
class HTMLIFrameElement;

class PermissionsPolicy {
public:
    static PermissionsPolicy defaultPolicy(Document& document) { return PermissionsPolicy { document, nullptr }; }
    static PermissionsPolicy parse(Document& document, const HTMLIFrameElement& frame) { return PermissionsPolicy { document, &frame }; }

    enum class Feature : uint8_t {
        Camera,
        Microphone,
        SpeakerSelection,
        DisplayCapture,
        Gamepad,
        Geolocation,
        Payment,
        ScreenWakeLock,
        SyncXHR,
        Fullscreen,
        WebShare,
#if ENABLE(DEVICE_ORIENTATION)
        Gyroscope,
        Accelerometer,
        Magnetometer,
#endif
#if ENABLE(WEB_AUTHN)
        PublickeyCredentialsGetRule,
#endif
#if ENABLE(WEBXR)
        XRSpatialTracking,
#endif
        PrivateToken,
        Invalid
    };
    bool allows(Feature, const SecurityOriginData&) const;

private:
    PermissionsPolicy(Document&, const HTMLIFrameElement*);

    // https://w3c.github.io/webappsec-permissions-policy/#allowlists
    class Allowlist {
    public:
        Allowlist() = default;
        enum AllowAllOriginsTag { AllowAllOrigins };
        explicit Allowlist(AllowAllOriginsTag) : m_origins(AllowAllOrigins) { }
        explicit Allowlist(const SecurityOriginData& origin): m_origins(HashSet<SecurityOriginData> { origin }) { }
        explicit Allowlist(HashSet<SecurityOriginData>&& origins) : m_origins(WTFMove(origins)) { }
        bool matches(const SecurityOriginData&) const;

    private:
        std::variant<HashSet<SecurityOriginData>, AllowAllOriginsTag> m_origins;
    };
    Ref<SecurityOrigin> declaredOrigin(const HTMLIFrameElement&) const;
    Allowlist parseAllowlist(StringView, const SecurityOriginData& containerOrigin, const SecurityOriginData& targetOrigin, bool useStarAsDefaultAllowlistValue);

    // https://w3c.github.io/webappsec-permissions-policy/#policy-directives
    using PolicyDirective = HashMap<Feature, Allowlist, IntHash<Feature>, WTF::StrongEnumHashTraits<Feature>>;
    PolicyDirective parsePolicyDirective(StringView, const SecurityOriginData& containerOrigin, const SecurityOriginData& targetOrigin, bool useStarAsDefaultAllowlistValue);

    PolicyDirective m_effectivePolicy;
};

enum class LogPermissionsPolicyFailure : bool { No, Yes };
extern bool isPermissionsPolicyAllowedByDocumentAndAllOwners(PermissionsPolicy::Feature, const Document&, LogPermissionsPolicyFailure = LogPermissionsPolicyFailure::Yes);

} // namespace WebCore

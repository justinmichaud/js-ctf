/*
 * Copyright (C) 2018-2021 Apple Inc. All rights reserved.
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

#if PLATFORM(COCOA)

#include <wtf/Forward.h>
#include <wtf/spi/cocoa/SecuritySPI.h>
#include <wtf/spi/darwin/XPCSPI.h>

namespace WTF {

class String;

WTF_EXPORT_PRIVATE bool hasEntitlement(SecTaskRef, ASCIILiteral entitlement);
WTF_EXPORT_PRIVATE bool hasEntitlement(audit_token_t, ASCIILiteral entitlement);
WTF_EXPORT_PRIVATE bool hasEntitlement(xpc_connection_t, StringView entitlement);
WTF_EXPORT_PRIVATE bool hasEntitlement(xpc_connection_t, ASCIILiteral entitlement);
WTF_EXPORT_PRIVATE bool processHasEntitlement(ASCIILiteral entitlement);
WTF_EXPORT_PRIVATE bool hasEntitlementValue(audit_token_t, ASCIILiteral entitlement, ASCIILiteral value);
WTF_EXPORT_PRIVATE bool hasEntitlementValueInArray(audit_token_t, ASCIILiteral entitlement, ASCIILiteral value);

} // namespace WTF

#endif

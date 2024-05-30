/*
 * Copyright (C) 2022-2023 Apple Inc. All rights reserved.
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

#if ENABLE(WK_WEB_EXTENSIONS)

#include "JSWebExtensionAPIExtension.h"
#include "WebExtensionAPIObject.h"

OBJC_CLASS NSString;
OBJC_CLASS NSURL;

namespace WebKit {

class WebPage;

class WebExtensionAPIExtension : public WebExtensionAPIObject, public JSWebExtensionWrappable {
    WEB_EXTENSION_DECLARE_JS_WRAPPER_CLASS(WebExtensionAPIExtension, extension, extension);

public:
    enum class ViewType : uint8_t {
        Popup,
        Tab,
    };

#if PLATFORM(COCOA)
    bool isPropertyAllowed(const ASCIILiteral& propertyName, WebPage&);

    bool isInIncognitoContext(WebPage&);
    void isAllowedFileSchemeAccess(Ref<WebExtensionCallbackHandler>&&);
    void isAllowedIncognitoAccess(Ref<WebExtensionCallbackHandler>&&);

    NSURL *getURL(NSString *resourcePath, NSString **outExceptionString);
    JSValue *getBackgroundPage(JSContextRef);
    NSArray *getViews(JSContextRef, NSDictionary *filter, NSString **outExceptionString);
#endif

private:
    static bool parseViewFilters(NSDictionary *, std::optional<ViewType>&, std::optional<WebExtensionTabIdentifier>&, std::optional<WebExtensionWindowIdentifier>&, NSString *sourceKey, NSString **outExceptionString);
};

} // namespace WebKit

#endif // ENABLE(WK_WEB_EXTENSIONS)

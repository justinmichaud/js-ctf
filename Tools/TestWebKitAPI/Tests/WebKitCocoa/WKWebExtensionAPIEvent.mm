/*
 * Copyright (C) 2022 Apple Inc. All rights reserved.
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

#import "config.h"

#if ENABLE(WK_WEB_EXTENSIONS)

#import "WebExtensionUtilities.h"

namespace TestWebKitAPI {

static auto *eventManifest = @{ @"manifest_version": @3, @"background": @{ @"scripts": @[ @"background.js" ], @"persistent": @NO } };

TEST(WKWebExtensionAPIEvent, Errors)
{
    auto *backgroundScript = Util::constructScript(@[
        @"browser.test.assertThrows(() => browser.runtime.onStartup.addListener('bad'), /'listener' value is invalid, because a function is expected/i)",
        @"browser.test.assertThrows(() => browser.runtime.onStartup.removeListener('bad'), /'listener' value is invalid, because a function is expected/i)",
        @"browser.test.assertThrows(() => browser.runtime.onStartup.hasListener('bad'), /'listener' value is invalid, because a function is expected/i)",

        @"browser.test.notifyPass()"
    ]);

    Util::loadAndRunExtension(eventManifest, @{ @"background.js": backgroundScript });
}

TEST(WKWebExtensionAPIEvent, TestEventListener)
{
    auto *backgroundScript = Util::constructScript(@[
        // Setup
        @"function listener() { }",
        @"browser.test.assertFalse(browser.runtime.onStartup.hasListener(listener), 'Should not have listener')",
        @"browser.runtime.onStartup.addListener(listener)",

        // Test
        @"browser.test.assertTrue(browser.runtime.onStartup.hasListener(listener), 'Should have listener')",
        @"browser.runtime.onStartup.removeListener(listener)",
        @"browser.test.assertFalse(browser.runtime.onStartup.hasListener(listener), 'Should not have listener')",
        @"browser.runtime.onStartup.addListener(listener)",

        // Finish.
        @"browser.test.notifyPass()"
    ]);

    Util::loadAndRunExtension(eventManifest, @{ @"background.js": backgroundScript });
}

} // namespace TestWebKitAPI

#endif // ENABLE(WK_WEB_EXTENSIONS)

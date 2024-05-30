/*
 * Copyright (C) 2013 Apple Inc. All rights reserved.
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

#if WK_HAVE_C_SPI && PLATFORM(MAC)

#import "JavaScriptTest.h"
#import "PlatformUtilities.h"
#import "Test.h"
#import "TestBrowsingContextLoadDelegate.h"
#import "TestProtocol.h"
#import <WebKit/WKBrowsingContextGroupPrivate.h>
#import <WebKit/WKPreferencesPrivate.h>
#import <WebKit/WKRetainPtr.h>
#import <WebKit/WKString.h>
#import <WebKit/WKWebViewPrivate.h>
#import <wtf/RetainPtr.h>

static bool testFinished = false;

namespace TestWebKitAPI {

TEST(WebKit2CustomProtocolsTest, SyncXHR)
{
    [TestProtocol registerWithScheme:@"http"];

    // Allow file URLs to load non-file resources
    auto wkView = adoptNS([[WKWebView alloc] initWithFrame:NSMakeRect(0, 0, 800, 600)]);
    wkView.get().configuration.preferences._universalAccessFromFileURLsAllowed = YES;
    RetainPtr<TestBrowsingContextLoadDelegate> delegate = adoptNS([[TestBrowsingContextLoadDelegate alloc] initWithBlockToRunOnLoad:^(WKWebView *sender) {
        EXPECT_JS_EQ(wkView.get()._pageRefForTransitionToWKWebView, "window._testResult", "PASS");
        testFinished = true;
    }]);
    wkView.get().navigationDelegate = delegate.get();

    WKPageLoadURL(wkView.get()._pageRefForTransitionToWKWebView, Util::createURLForResource("custom-protocol-sync-xhr", "html"));

    TestWebKitAPI::Util::run(&testFinished);
    [TestProtocol unregister];
}

} // namespace TestWebKitAPI

#endif

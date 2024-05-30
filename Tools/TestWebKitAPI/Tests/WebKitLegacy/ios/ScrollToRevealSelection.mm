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

#if HAVE(UIWEBVIEW)

IGNORE_WARNINGS_BEGIN("deprecated-implementations")

#import "PlatformUtilities.h"
#import "UIKitSPIForTesting.h"
#import <wtf/RetainPtr.h>

@interface LegacyLoadingDelegate : NSObject <UIWebViewDelegate>
- (void)waitForDidFinishLoad;
@end

@implementation LegacyLoadingDelegate {
    bool _loadComplete;
}

- (void)webViewDidFinishLoad:(UIWebView *)webView
{
    _loadComplete = true;
}

- (void)waitForDidFinishLoad
{
    EXPECT_FALSE(_loadComplete);
    TestWebKitAPI::Util::run(&_loadComplete);
}

@end

TEST(WebKitLegacy, ScrollToRevealSelection)
{
    auto window = adoptNS([[UIWindow alloc] initWithFrame:CGRectMake(0, 0, 320, 500)]);
    [window setHidden:NO];
    auto webView = adoptNS([[UIWebView alloc] initWithFrame:CGRectMake(0, 0, 320, 500)]);
    [window addSubview:webView.get()];
    auto delegate = adoptNS([[LegacyLoadingDelegate alloc] init]);
    [webView setDelegate:delegate.get()];
    [webView loadHTMLString:@"<meta name='viewport' content='width=device-width, initial-scale=1'><body style='font-size: 100px;' contenteditable>" baseURL:nil];
    [delegate waitForDidFinishLoad];
    [webView stringByEvaluatingJavaScriptFromString:@"document.body.focus()"];
    for (int i = 0; i < 10; ++i)
        [[webView _browserView] insertText:@"\n"];

    EXPECT_GT([[webView scrollView] contentOffset].y, 0);
}

IGNORE_WARNINGS_END

#endif // PLATFORM(IOS_FAMILY)

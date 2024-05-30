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

TEST(WKWebExtensionAPINamespace, NoWebNavigationObjectWithoutPermission)
{
    auto *manifest = @{
        @"manifest_version": @3,
        @"permissions": @[ @"webNavigation" ],
        @"background": @{
            @"scripts": @[ @"background.js" ],
            @"type": @"module",
            @"persistent": @NO
        }
    };

    auto *backgroundScript = Util::constructScript(@[
        @"browser.test.assertEq(typeof browser.webNavigation, 'undefined')",
        @"browser.test.notifyPass()"
    ]);

    auto extension = adoptNS([[_WKWebExtension alloc] _initWithManifestDictionary:manifest resources:@{ @"background.js": backgroundScript }]);
    auto manager = adoptNS([[TestWebExtensionManager alloc] initForExtension:extension.get()]);

    // Deny the permission, since TestWebKitAPI auto grants all requested permissions.
    [manager.get().context setPermissionStatus:_WKWebExtensionContextPermissionStatusDeniedExplicitly forPermission:_WKWebExtensionPermissionWebNavigation];

    [manager loadAndRun];
}

TEST(WKWebExtensionAPINamespace, WebNavigationObjectWithPermission)
{
    auto *manifest = @{
        @"manifest_version": @3,
        @"permissions": @[ @"webNavigation" ],
        @"background": @{
            @"scripts": @[ @"background.js" ],
            @"type": @"module",
            @"persistent": @NO
        }
    };

    auto *backgroundScript = Util::constructScript(@[
        @"browser.test.assertEq(typeof browser.webNavigation, 'object')",
        @"browser.test.notifyPass()"
    ]);

    // TestWebKitAPI auto grants all requested permissions.

    Util::loadAndRunExtension(manifest, @{ @"background.js": backgroundScript });
}

TEST(WKWebExtensionAPINamespace, NoNotificationsObjectWithoutPermission)
{
    auto *manifest = @{
        @"manifest_version": @3,
        @"permissions": @[ @"notifications" ],
        @"background": @{
            @"scripts": @[ @"background.js" ],
            @"type": @"module",
            @"persistent": @NO
        }
    };

    auto *backgroundScript = Util::constructScript(@[
        @"browser.test.assertEq(typeof browser.notifications, 'undefined')",
        @"browser.test.notifyPass()"
    ]);

    auto extension = adoptNS([[_WKWebExtension alloc] _initWithManifestDictionary:manifest resources:@{ @"background.js": backgroundScript }]);
    auto manager = adoptNS([[TestWebExtensionManager alloc] initForExtension:extension.get()]);

    // Deny the permission, since TestWebKitAPI auto grants all requested permissions.
    [manager.get().context setPermissionStatus:_WKWebExtensionContextPermissionStatusDeniedExplicitly forPermission:@"notifications"];

    [manager loadAndRun];
}

TEST(WKWebExtensionAPINamespace, NotificationsObjectWithPermission)
{
    auto *manifest = @{
        @"manifest_version": @3,
        @"permissions": @[ @"notifications" ],
        @"background": @{
            @"scripts": @[ @"background.js" ],
            @"type": @"module",
            @"persistent": @NO
        }
    };

    auto *backgroundScript = Util::constructScript(@[
        @"browser.test.assertEq(typeof browser.notifications, 'object')",
        @"browser.test.notifyPass()"
    ]);

    // TestWebKitAPI auto grants all requested permissions.

    Util::loadAndRunExtension(manifest, @{ @"background.js": backgroundScript });
}

TEST(WKWebExtensionAPINamespace, NotificationsUnsupported)
{
    auto *manifest = @{
        @"manifest_version": @3,
        @"permissions": @[ @"notifications" ],
        @"background": @{
            @"scripts": @[ @"background.js" ],
            @"type": @"module",
            @"persistent": @NO
        }
    };

    auto *backgroundScript = Util::constructScript(@[
        @"browser.test.assertEq(browser.notifications, undefined)",

        @"browser.test.notifyPass()"
    ]);

    auto extension = adoptNS([[_WKWebExtension alloc] _initWithManifestDictionary:manifest resources:@{ @"background.js": backgroundScript }]);
    auto manager = adoptNS([[TestWebExtensionManager alloc] initForExtension:extension.get()]);

    manager.get().context.unsupportedAPIs = [NSSet setWithObject:@"browser.notifications"];

    [manager loadAndRun];
}


TEST(WKWebExtensionAPINamespace, ObjectEquality)
{
    auto *manifest = @{
        @"manifest_version": @3,
        @"permissions": @[ @"storage", @"tabs" ],
        @"background": @{
            @"scripts": @[ @"background.js" ],
            @"type": @"module",
            @"persistent": @NO
        }
    };

    auto *backgroundScript = Util::constructScript(@[
        @"browser.test.assertEq(browser.storage, browser.storage)",
        @"browser.test.assertEq(browser.storage.local, browser.storage.local)",
        @"browser.test.assertEq(browser.storage.session, browser.storage.session)",
        @"browser.test.assertEq(browser.storage.sync, browser.storage.sync)",
        @"browser.test.assertEq(browser.tabs, browser.tabs)",
        @"browser.test.assertEq(browser.windows, browser.windows)",

        @"browser.test.notifyPass()"
    ]);

    Util::loadAndRunExtension(manifest, @{ @"background.js": backgroundScript });
}

} // namespace TestWebKitAPI

#endif // ENABLE(WK_WEB_EXTENSIONS)

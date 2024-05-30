/*
 * Copyright (C) 2014-2023 Apple Inc. All rights reserved.
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
#import "WebPageProxy.h"

#import "APIAttachment.h"
#import "APIPageConfiguration.h"
#import "APIUIClient.h"
#import "AppleMediaServicesUISPI.h"
#import "CocoaImage.h"
#import "Connection.h"
#import "CoreTelephonyUtilities.h"
#import "DataDetectionResult.h"
#import "InsertTextOptions.h"
#import "LoadParameters.h"
#import "MessageSenderInlines.h"
#import "PageClient.h"
#import "PlaybackSessionManagerProxy.h"
#import "QuickLookThumbnailLoader.h"
#import "RemoteLayerTreeTransaction.h"
#import "SafeBrowsingSPI.h"
#import "SafeBrowsingWarning.h"
#import "SharedBufferReference.h"
#import "SynapseSPI.h"
#import "VideoPresentationManagerProxy.h"
#import "WKErrorInternal.h"
#import "WKWebView.h"
#import "WebContextMenuProxy.h"
#import "WebFrameProxy.h"
#import "WebPage.h"
#import "WebPageMessages.h"
#import "WebPageProxyInternals.h"
#import "WebPasteboardProxy.h"
#import "WebPrivacyHelpers.h"
#import "WebProcessMessages.h"
#import "WebProcessPool.h"
#import "WebProcessProxy.h"
#import "WebScreenOrientationManagerProxy.h"
#import "WebsiteDataStore.h"
#import <Foundation/NSURLRequest.h>
#import <WebCore/ApplePayAMSUIRequest.h>
#import <WebCore/DragItem.h>
#import <WebCore/GeometryUtilities.h>
#import <WebCore/HighlightVisibility.h>
#import <WebCore/LocalCurrentGraphicsContext.h>
#import <WebCore/NetworkExtensionContentFilter.h>
#import <WebCore/NotImplemented.h>
#import <WebCore/NowPlayingInfo.h>
#import <WebCore/RunLoopObserver.h>
#import <WebCore/SearchPopupMenuCocoa.h>
#import <WebCore/TextAlternativeWithRange.h>
#import <WebCore/ValidationBubble.h>
#import <pal/spi/cocoa/QuartzCoreSPI.h>
#import <pal/spi/ios/BrowserEngineKitSPI.h>
#import <pal/spi/mac/QuarantineSPI.h>
#import <wtf/BlockPtr.h>
#import <wtf/SoftLinking.h>
#import <wtf/cf/TypeCastsCF.h>
#import <wtf/cocoa/SpanCocoa.h>

#if ENABLE(MEDIA_USAGE)
#import "MediaUsageManagerCocoa.h"
#endif

#if ENABLE(APP_HIGHLIGHTS)
SOFT_LINK_PRIVATE_FRAMEWORK_OPTIONAL(Synapse)
SOFT_LINK_CLASS_OPTIONAL(Synapse, SYNotesActivationObserver)
#endif

#if USE(APPKIT)
#import <AppKit/NSImage.h>
#else
#import <UIKit/UIImage.h>
#endif

#if PLATFORM(IOS_FAMILY)
#import <WebCore/RenderThemeIOS.h>
#import "UIKitSPI.h"
#else
#import <WebCore/RenderThemeMac.h>
#endif

#if PLATFORM(IOS) || PLATFORM(VISION)
#import <pal/spi/cocoa/WebFilterEvaluatorSPI.h>

SOFT_LINK_PRIVATE_FRAMEWORK(WebContentAnalysis);
SOFT_LINK_CLASS(WebContentAnalysis, WebFilterEvaluator);
#endif

#if HAVE(SCREEN_CAPTURE_KIT)
#import <WebCore/ScreenCaptureKitSharingSessionManager.h>
#endif

#if ENABLE(APPLE_PAY_AMS_UI)
SOFT_LINK_PRIVATE_FRAMEWORK_OPTIONAL(AppleMediaServices)
SOFT_LINK_CLASS_OPTIONAL(AppleMediaServices, AMSEngagementRequest)

SOFT_LINK_PRIVATE_FRAMEWORK_OPTIONAL(AppleMediaServicesUI)
SOFT_LINK_CLASS_OPTIONAL(AppleMediaServicesUI, AMSUIEngagementTask)
#endif

#define MESSAGE_CHECK(assertion) MESSAGE_CHECK_BASE(assertion, process().connection())
#define MESSAGE_CHECK_COMPLETION(assertion, completion) MESSAGE_CHECK_COMPLETION_BASE(assertion, process().connection(), completion)

#define WEBPAGEPROXY_RELEASE_LOG(channel, fmt, ...) RELEASE_LOG(channel, "%p - [pageProxyID=%llu, webPageID=%llu, PID=%i] WebPageProxy::" fmt, this, identifier().toUInt64(), webPageID().toUInt64(), m_process->processID(), ##__VA_ARGS__)

namespace WebKit {
using namespace WebCore;

constexpr IntSize iconSize = IntSize(400, 400);

static bool exceedsRenderTreeSizeSizeThreshold(uint64_t thresholdSize, uint64_t committedSize)
{
    const double thesholdSizeFraction = 0.5; // Empirically-derived.
    return committedSize > thresholdSize * thesholdSizeFraction;
}

void WebPageProxy::didCommitLayerTree(const WebKit::RemoteLayerTreeTransaction& layerTreeTransaction)
{
    themeColorChanged(layerTreeTransaction.themeColor());
    pageExtendedBackgroundColorDidChange(layerTreeTransaction.pageExtendedBackgroundColor());
    sampledPageTopColorChanged(layerTreeTransaction.sampledPageTopColor());

    if (!m_hasUpdatedRenderingAfterDidCommitLoad) {
        if (layerTreeTransaction.transactionID() >= internals().firstLayerTreeTransactionIdAfterDidCommitLoad) {
            m_hasUpdatedRenderingAfterDidCommitLoad = true;
            stopMakingViewBlankDueToLackOfRenderingUpdateIfNecessary();
            internals().lastVisibleContentRectUpdate = { };
        }
    }

    protectedPageClient()->didCommitLayerTree(layerTreeTransaction);

    // FIXME: Remove this special mechanism and fold it into the transaction's layout milestones.
    if (internals().observedLayoutMilestones.contains(WebCore::LayoutMilestone::ReachedSessionRestorationRenderTreeSizeThreshold) && !m_hitRenderTreeSizeThreshold
        && exceedsRenderTreeSizeSizeThreshold(m_sessionRestorationRenderTreeSize, layerTreeTransaction.renderTreeSize())) {
        m_hitRenderTreeSizeThreshold = true;
        didReachLayoutMilestone(WebCore::LayoutMilestone::ReachedSessionRestorationRenderTreeSizeThreshold);
    }
}

void WebPageProxy::layerTreeCommitComplete()
{
    protectedPageClient()->layerTreeCommitComplete();
}

#if ENABLE(DATA_DETECTION)

void WebPageProxy::setDataDetectionResult(const DataDetectionResult& dataDetectionResult)
{
    m_dataDetectionResults = dataDetectionResult.results;
}

void WebPageProxy::handleClickForDataDetectionResult(const DataDetectorElementInfo& info, const IntPoint& clickLocation)
{
    protectedPageClient()->handleClickForDataDetectionResult(info, clickLocation);
}

#endif

void WebPageProxy::saveRecentSearches(const String& name, const Vector<WebCore::RecentSearch>& searchItems)
{
    MESSAGE_CHECK(!name.isNull());

    m_websiteDataStore->saveRecentSearches(name, searchItems);
}

void WebPageProxy::loadRecentSearches(const String& name, CompletionHandler<void(Vector<WebCore::RecentSearch>&&)>&& completionHandler)
{
    MESSAGE_CHECK_COMPLETION(!name.isNull(), completionHandler({ }));

    m_websiteDataStore->loadRecentSearches(name, WTFMove(completionHandler));
}

void WebPageProxy::grantAccessToCurrentPasteboardData(const String& pasteboardName, std::optional<FrameIdentifier> frameID)
{
    if (!hasRunningProcess())
        return;
    if (frameID) {
        if (auto* frame = WebFrameProxy::webFrame(*frameID)) {
            WebPasteboardProxy::singleton().grantAccessToCurrentData(frame->process(), pasteboardName);
            return;
        }
    }
    WebPasteboardProxy::singleton().grantAccessToCurrentData(m_process, pasteboardName);
}

void WebPageProxy::beginSafeBrowsingCheck(const URL& url, bool forMainFrameNavigation, WebFramePolicyListenerProxy& listener)
{
#if HAVE(SAFE_BROWSING)
    SSBLookupContext *context = [SSBLookupContext sharedLookupContext];
    if (!context)
        return listener.didReceiveSafeBrowsingResults({ });
    [context lookUpURL:url completionHandler:makeBlockPtr([listener = Ref { listener }, forMainFrameNavigation, url = url] (SSBLookupResult *result, NSError *error) mutable {
        RunLoop::main().dispatch([listener = WTFMove(listener), result = retainPtr(result), error = retainPtr(error), forMainFrameNavigation, url = WTFMove(url)] {
            if (error) {
                listener->didReceiveSafeBrowsingResults({ });
                return;
            }

            for (SSBServiceLookupResult *lookupResult in [result serviceLookupResults]) {
                if (lookupResult.isPhishing || lookupResult.isMalware || lookupResult.isUnwantedSoftware) {
                    listener->didReceiveSafeBrowsingResults(SafeBrowsingWarning::create(url, forMainFrameNavigation, lookupResult));
                    return;
                }
            }
            listener->didReceiveSafeBrowsingResults({ });
        });
    }).get()];
#else
    listener.didReceiveSafeBrowsingResults({ });
#endif
}

#if ENABLE(CONTENT_FILTERING)
void WebPageProxy::contentFilterDidBlockLoadForFrame(const WebCore::ContentFilterUnblockHandler& unblockHandler, FrameIdentifier frameID)
{
    contentFilterDidBlockLoadForFrameShared(m_process.copyRef(), unblockHandler, frameID);
}

void WebPageProxy::contentFilterDidBlockLoadForFrameShared(Ref<WebProcessProxy>&& process, const WebCore::ContentFilterUnblockHandler& unblockHandler, FrameIdentifier frameID)
{
    if (RefPtr frame = WebFrameProxy::webFrame(frameID))
        frame->contentFilterDidBlockLoad(unblockHandler);
}
#endif

void WebPageProxy::addPlatformLoadParameters(WebProcessProxy& process, LoadParameters& loadParameters)
{
    loadParameters.dataDetectionReferenceDate = m_uiClient->dataDetectionReferenceDate();
}

void WebPageProxy::createSandboxExtensionsIfNeeded(const Vector<String>& files, SandboxExtension::Handle& fileReadHandle, Vector<SandboxExtension::Handle>& fileUploadHandles)
{
    if (!files.size())
        return;

    if (files.size() == 1) {
        BOOL isDirectory;
        if ([[NSFileManager defaultManager] fileExistsAtPath:files[0] isDirectory:&isDirectory] && !isDirectory) {
            ASSERT(process().connection() && process().connection()->getAuditToken());
            if (process().connection() && process().connection()->getAuditToken()) {
                if (auto handle = SandboxExtension::createHandleForReadByAuditToken("/"_s, *(process().connection()->getAuditToken())))
                    fileReadHandle = WTFMove(*handle);
            } else if (auto handle = SandboxExtension::createHandle("/"_s, SandboxExtension::Type::ReadOnly))
                fileReadHandle = WTFMove(*handle);
            willAcquireUniversalFileReadSandboxExtension(m_process);
        }
    }

    for (auto& file : files) {
        if (![[NSFileManager defaultManager] fileExistsAtPath:file])
            continue;
        if (auto handle = SandboxExtension::createHandle(file, SandboxExtension::Type::ReadOnly))
            fileUploadHandles.append(WTFMove(*handle));
    }
}

void WebPageProxy::scrollingNodeScrollViewDidScroll(ScrollingNodeID nodeID)
{
    protectedPageClient()->scrollingNodeScrollViewDidScroll(nodeID);
}

bool WebPageProxy::scrollingUpdatesDisabledForTesting()
{
    return protectedPageClient()->scrollingUpdatesDisabledForTesting();
}

#if ENABLE(DRAG_SUPPORT)

void WebPageProxy::startDrag(const DragItem& dragItem, ShareableBitmap::Handle&& dragImageHandle)
{
    protectedPageClient()->startDrag(dragItem, WTFMove(dragImageHandle));
}

#endif

#if ENABLE(ATTACHMENT_ELEMENT)

void WebPageProxy::platformRegisterAttachment(Ref<API::Attachment>&& attachment, const String& preferredFileName, const IPC::SharedBufferReference& bufferCopy)
{
    if (bufferCopy.isEmpty())
        return;

    auto fileWrapper = adoptNS([protectedPageClient()->allocFileWrapperInstance() initRegularFileWithContents:bufferCopy.unsafeBuffer()->createNSData().get()]);
    [fileWrapper setPreferredFilename:preferredFileName];
    attachment->setFileWrapper(fileWrapper.get());
}

void WebPageProxy::platformRegisterAttachment(Ref<API::Attachment>&& attachment, const String& filePath)
{
    if (!filePath)
        return;

    auto fileWrapper = adoptNS([protectedPageClient()->allocFileWrapperInstance() initWithURL:[NSURL fileURLWithPath:filePath] options:0 error:nil]);
    attachment->setFileWrapper(fileWrapper.get());
}

void WebPageProxy::platformCloneAttachment(Ref<API::Attachment>&& fromAttachment, Ref<API::Attachment>&& toAttachment)
{
    fromAttachment->doWithFileWrapper([&](NSFileWrapper *fileWrapper) {
        toAttachment->setFileWrapper(fileWrapper);
    });
}

static RefPtr<WebCore::ShareableBitmap> convertPlatformImageToBitmap(CocoaImage *image, const WebCore::FloatSize& fittingSize)
{
    FloatSize originalThumbnailSize([image size]);
    if (originalThumbnailSize.isEmpty())
        return nullptr;

    auto resultRect = roundedIntRect(largestRectWithAspectRatioInsideRect(originalThumbnailSize.aspectRatio(), { { }, fittingSize }));
    resultRect.setLocation({ });

    auto bitmap = WebCore::ShareableBitmap::create({ resultRect.size() });
    if (!bitmap)
        return nullptr;

    auto graphicsContext = bitmap->createGraphicsContext();
    if (!graphicsContext)
        return nullptr;

    LocalCurrentGraphicsContext savedContext(*graphicsContext);
    [image drawInRect:resultRect];

    return bitmap;
}

RefPtr<WebCore::ShareableBitmap> WebPageProxy::iconForAttachment(const String& fileName, const String& contentType, const String& title, FloatSize& size)
{
#if PLATFORM(IOS_FAMILY)
    auto imageAndSize = RenderThemeIOS::iconForAttachment(fileName, contentType, title);
    auto image = imageAndSize.icon;
    size = imageAndSize.size;
#else
    auto image = RenderThemeMac::iconForAttachment(fileName, contentType, title);
#endif
    return convertPlatformImageToBitmap(image.get(), iconSize);
}

#endif // ENABLE(ATTACHMENT_ELEMENT)

void WebPageProxy::performDictionaryLookupAtLocation(const WebCore::FloatPoint& point)
{
    if (!hasRunningProcess())
        return;
    
    send(Messages::WebPage::PerformDictionaryLookupAtLocation(point));
}

void WebPageProxy::performDictionaryLookupOfCurrentSelection()
{
    if (!hasRunningProcess())
        return;
    
    send(Messages::WebPage::PerformDictionaryLookupOfCurrentSelection());
}

void WebPageProxy::insertDictatedTextAsync(const String& text, const EditingRange& replacementRange, const Vector<TextAlternativeWithRange>& dictationAlternativesWithRange, InsertTextOptions&& options)
{
    if (!hasRunningProcess())
        return;

    Vector<DictationAlternative> dictationAlternatives;
    for (const auto& alternativeWithRange : dictationAlternativesWithRange) {
        if (auto context = protectedPageClient()->addDictationAlternatives(alternativeWithRange.alternatives.get()))
            dictationAlternatives.append({ alternativeWithRange.range, context });
    }

    if (dictationAlternatives.isEmpty()) {
        insertTextAsync(text, replacementRange, WTFMove(options));
        return;
    }

    send(Messages::WebPage::InsertDictatedTextAsync { text, replacementRange, dictationAlternatives, WTFMove(options) });
}

void WebPageProxy::addDictationAlternative(TextAlternativeWithRange&& alternative)
{
    if (!hasRunningProcess())
        return;

    auto nsAlternatives = alternative.alternatives.get();
    auto context = protectedPageClient()->addDictationAlternatives(nsAlternatives);
    sendWithAsyncReply(Messages::WebPage::AddDictationAlternative { nsAlternatives.primaryString, context }, [context, weakThis = WeakPtr { *this }](bool success) {
        if (RefPtr protectedThis = weakThis.get(); protectedThis && !success)
            protectedThis->removeDictationAlternatives(context);
    });
}

void WebPageProxy::dictationAlternativesAtSelection(CompletionHandler<void(Vector<DictationContext>&&)>&& completion)
{
    if (!hasRunningProcess()) {
        completion({ });
        return;
    }

    sendWithAsyncReply(Messages::WebPage::DictationAlternativesAtSelection(), WTFMove(completion));
}

void WebPageProxy::clearDictationAlternatives(Vector<DictationContext>&& alternativesToClear)
{
    if (!hasRunningProcess() || alternativesToClear.isEmpty())
        return;

    send(Messages::WebPage::ClearDictationAlternatives(WTFMove(alternativesToClear)));
}

#if USE(DICTATION_ALTERNATIVES)

PlatformTextAlternatives *WebPageProxy::platformDictationAlternatives(WebCore::DictationContext dictationContext)
{
    return protectedPageClient()->platformDictationAlternatives(dictationContext);
}

#endif

ResourceError WebPageProxy::errorForUnpermittedAppBoundDomainNavigation(const URL& url)
{
    return { WKErrorDomain, WKErrorNavigationAppBoundDomain, url, localizedDescriptionForErrorCode(WKErrorNavigationAppBoundDomain) };
}

#if ENABLE(APPLE_PAY)

IPC::Connection* WebPageProxy::Internals::paymentCoordinatorConnection(const WebPaymentCoordinatorProxy&)
{
    return page.messageSenderConnection();
}

const String& WebPageProxy::Internals::paymentCoordinatorBoundInterfaceIdentifier(const WebPaymentCoordinatorProxy&)
{
    return page.websiteDataStore().configuration().boundInterfaceIdentifier();
}

void WebPageProxy::Internals::getPaymentCoordinatorEmbeddingUserAgent(WebPageProxyIdentifier, CompletionHandler<void(const String&)>&& completionHandler)
{
    completionHandler(page.userAgent());
}

const String& WebPageProxy::Internals::paymentCoordinatorSourceApplicationBundleIdentifier(const WebPaymentCoordinatorProxy&)
{
    return page.websiteDataStore().configuration().sourceApplicationBundleIdentifier();
}

const String& WebPageProxy::Internals::paymentCoordinatorSourceApplicationSecondaryIdentifier(const WebPaymentCoordinatorProxy&)
{
    return page.websiteDataStore().configuration().sourceApplicationSecondaryIdentifier();
}

void WebPageProxy::Internals::paymentCoordinatorAddMessageReceiver(WebPaymentCoordinatorProxy&, IPC::ReceiverName receiverName, IPC::MessageReceiver& messageReceiver)
{
    page.process().addMessageReceiver(receiverName, webPageID, messageReceiver);
}

void WebPageProxy::Internals::paymentCoordinatorRemoveMessageReceiver(WebPaymentCoordinatorProxy&, IPC::ReceiverName receiverName)
{
    page.process().removeMessageReceiver(receiverName, webPageID);
}

#endif

#if ENABLE(SPEECH_SYNTHESIS)

void WebPageProxy::Internals::didStartSpeaking(WebCore::PlatformSpeechSynthesisUtterance&)
{
    if (speechSynthesisData().speakingStartedCompletionHandler)
        speechSynthesisData().speakingStartedCompletionHandler();
}

void WebPageProxy::Internals::didFinishSpeaking(WebCore::PlatformSpeechSynthesisUtterance&)
{
    if (speechSynthesisData().speakingFinishedCompletionHandler)
        speechSynthesisData().speakingFinishedCompletionHandler();
}

void WebPageProxy::Internals::didPauseSpeaking(WebCore::PlatformSpeechSynthesisUtterance&)
{
    if (speechSynthesisData().speakingPausedCompletionHandler)
        speechSynthesisData().speakingPausedCompletionHandler();
}

void WebPageProxy::Internals::didResumeSpeaking(WebCore::PlatformSpeechSynthesisUtterance&)
{
    if (speechSynthesisData().speakingResumedCompletionHandler)
        speechSynthesisData().speakingResumedCompletionHandler();
}

void WebPageProxy::Internals::speakingErrorOccurred(WebCore::PlatformSpeechSynthesisUtterance&)
{
    page.send(Messages::WebPage::SpeakingErrorOccurred());
}

void WebPageProxy::Internals::boundaryEventOccurred(WebCore::PlatformSpeechSynthesisUtterance&, WebCore::SpeechBoundary speechBoundary, unsigned charIndex, unsigned charLength)
{
    page.send(Messages::WebPage::BoundaryEventOccurred(speechBoundary == WebCore::SpeechBoundary::SpeechWordBoundary, charIndex, charLength));
}

void WebPageProxy::Internals::voicesDidChange()
{
    page.send(Messages::WebPage::VoicesDidChange());
}

#endif // ENABLE(SPEECH_SYNTHESIS)

#if HAVE(VISIBILITY_PROPAGATION_VIEW)
void WebPageProxy::didCreateContextInWebProcessForVisibilityPropagation(LayerHostingContextID contextID)
{
    m_contextIDForVisibilityPropagationInWebProcess = contextID;
    protectedPageClient()->didCreateContextInWebProcessForVisibilityPropagation(contextID);
}

#if ENABLE(GPU_PROCESS)
void WebPageProxy::didCreateContextInGPUProcessForVisibilityPropagation(LayerHostingContextID contextID)
{
    m_contextIDForVisibilityPropagationInGPUProcess = contextID;
    protectedPageClient()->didCreateContextInGPUProcessForVisibilityPropagation(contextID);
}
#endif // ENABLE(GPU_PROCESS)

#if ENABLE(MODEL_PROCESS)
void WebPageProxy::didCreateContextInModelProcessForVisibilityPropagation(LayerHostingContextID contextID)
{
    m_contextIDForVisibilityPropagationInModelProcess = contextID;
    protectedPageClient()->didCreateContextInModelProcessForVisibilityPropagation(contextID);
}
#endif // ENABLE(MODEL_PROCESS)
#endif // HAVE(VISIBILITY_PROPAGATION_VIEW)

#if ENABLE(MEDIA_USAGE)
MediaUsageManager& WebPageProxy::mediaUsageManager()
{
    if (!m_mediaUsageManager)
        m_mediaUsageManager = MediaUsageManager::create();

    return *m_mediaUsageManager;
}

void WebPageProxy::addMediaUsageManagerSession(WebCore::MediaSessionIdentifier identifier, const String& bundleIdentifier, const URL& pageURL)
{
    mediaUsageManager().addMediaSession(identifier, bundleIdentifier, pageURL);
}

void WebPageProxy::updateMediaUsageManagerSessionState(WebCore::MediaSessionIdentifier identifier, const WebCore::MediaUsageInfo& info)
{
    mediaUsageManager().updateMediaUsage(identifier, info);
}

void WebPageProxy::removeMediaUsageManagerSession(WebCore::MediaSessionIdentifier identifier)
{
    mediaUsageManager().removeMediaSession(identifier);
}
#endif

#if ENABLE(VIDEO_PRESENTATION_MODE)

void WebPageProxy::didChangePlaybackRate(PlaybackSessionContextIdentifier identifier)
{
    if (internals().currentFullscreenVideoSessionIdentifier == identifier)
        updateFullscreenVideoTextRecognition();
}

void WebPageProxy::didChangeCurrentTime(PlaybackSessionContextIdentifier identifier)
{
    if (internals().currentFullscreenVideoSessionIdentifier == identifier)
        updateFullscreenVideoTextRecognition();
}

void WebPageProxy::updateFullscreenVideoTextRecognition()
{
    if (!protectedPageClient()->isTextRecognitionInFullscreenVideoEnabled())
        return;

    if (internals().currentFullscreenVideoSessionIdentifier && m_playbackSessionManager && m_playbackSessionManager->isPaused(*internals().currentFullscreenVideoSessionIdentifier)) {
        internals().fullscreenVideoTextRecognitionTimer.startOneShot(250_ms);
        return;
    }

    internals().fullscreenVideoTextRecognitionTimer.stop();

    if (!internals().currentFullscreenVideoSessionIdentifier)
        return;

#if PLATFORM(IOS_FAMILY)
    if (RetainPtr controller = m_videoPresentationManager->playerViewController(*internals().currentFullscreenVideoSessionIdentifier))
        protectedPageClient()->cancelTextRecognitionForFullscreenVideo(controller.get());
#endif
}

void WebPageProxy::fullscreenVideoTextRecognitionTimerFired()
{
    if (!internals().currentFullscreenVideoSessionIdentifier || !m_videoPresentationManager)
        return;

    auto identifier = *internals().currentFullscreenVideoSessionIdentifier;
    m_videoPresentationManager->requestBitmapImageForCurrentTime(identifier, [identifier, weakThis = WeakPtr { *this }](std::optional<ShareableBitmap::Handle>&& imageHandle) {
        RefPtr protectedThis = weakThis.get();
        if (!protectedThis || protectedThis->internals().currentFullscreenVideoSessionIdentifier != identifier)
            return;

        auto presentationManager = protectedThis->m_videoPresentationManager;
        if (!presentationManager)
            return;
        if (!imageHandle)
            return;

#if PLATFORM(IOS_FAMILY)
        if (RetainPtr controller = presentationManager->playerViewController(identifier))
            protectedThis->protectedPageClient()->beginTextRecognitionForFullscreenVideo(WTFMove(*imageHandle), controller.get());
#endif
    });
}

#endif // ENABLE(VIDEO_PRESENTATION_MODE)

#if HAVE(QUICKLOOK_THUMBNAILING)

void WebPageProxy::requestThumbnail(WKQLThumbnailLoadOperation *operation)
{
    [operation setCompletionBlock:^{
        RunLoop::main().dispatch([this, operation = retainPtr(operation)] {
            auto identifier = [operation identifier];
            auto convertedImage = convertPlatformImageToBitmap([operation thumbnail], iconSize);
            if (!convertedImage)
                return;
            this->updateAttachmentThumbnail(identifier, convertedImage);
        });
    }];

    [[WKQLThumbnailQueueManager sharedInstance].queue addOperation:operation];
}

void WebPageProxy::requestThumbnail(const API::Attachment& attachment, const String& identifier)
{
    requestThumbnail(adoptNS([[WKQLThumbnailLoadOperation alloc] initWithAttachment:attachment identifier:identifier]).get());
}

void WebPageProxy::requestThumbnailWithPath(const String& filePath, const String& identifier)
{
    requestThumbnail(adoptNS([[WKQLThumbnailLoadOperation alloc] initWithURL:filePath identifier:identifier]).get());
}

#endif // HAVE(QUICKLOOK_THUMBNAILING)

#if ENABLE(ATTACHMENT_ELEMENT) && PLATFORM(MAC)

bool WebPageProxy::updateIconForDirectory(NSFileWrapper *fileWrapper, const String& identifier)
{
    auto image = [fileWrapper icon];
    if (!image)
        return false;

    auto convertedImage = convertPlatformImageToBitmap(image, iconSize);
    if (!convertedImage)
        return false;

    auto handle = convertedImage->createHandle();
    if (!handle)
        return false;
    send(Messages::WebPage::UpdateAttachmentIcon(identifier, WTFMove(handle), iconSize));
    return true;
}

#endif

void WebPageProxy::scheduleActivityStateUpdate()
{
    bool hasScheduledObserver = m_activityStateChangeDispatcher->isScheduled();
    bool hasActiveCATransaction = [CATransaction currentState];

    if (hasScheduledObserver && hasActiveCATransaction) {
        ASSERT(m_hasScheduledActivityStateUpdate);
        m_hasScheduledActivityStateUpdate = false;
        m_activityStateChangeDispatcher->invalidate();
    }

    if (m_hasScheduledActivityStateUpdate)
        return;
    m_hasScheduledActivityStateUpdate = true;

    // If there is an active transaction, we need to dispatch the update after the transaction is committed,
    // to avoid flash caused by web process setting root layer too early.
    // If there is no active transaction, likely there is no root layer change or change is committed,
    // then schedule dispatch on runloop observer to collect changes in the same runloop cycle before dispatching.
    if (hasActiveCATransaction) {
        [CATransaction addCommitHandler:[weakThis = WeakPtr { *this }] {
            // We can't call dispatchActivityStateChange directly underneath this commit handler, because it has side-effects
            // that may result in other frameworks trying to install commit handlers for the same phase, which is not allowed.
            // So, dispatch_async here; we only care that the activity state change doesn't apply until after the active commit is complete.
            WorkQueue::main().dispatch([weakThis] {
                RefPtr protectedThis { weakThis.get() };
                if (!protectedThis)
                    return;

                protectedThis->dispatchActivityStateChange();
            });
        } forPhase:kCATransactionPhasePostCommit];
        return;
    }

    m_activityStateChangeDispatcher->schedule();
}

void WebPageProxy::addActivityStateUpdateCompletionHandler(CompletionHandler<void()>&& completionHandler)
{
    if (!m_hasScheduledActivityStateUpdate) {
        completionHandler();
        return;
    }

    m_activityStateUpdateCallbacks.append(WTFMove(completionHandler));
}

#if ENABLE(APP_HIGHLIGHTS)
void WebPageProxy::createAppHighlightInSelectedRange(WebCore::CreateNewGroupForHighlight createNewGroup, WebCore::HighlightRequestOriginatedInApp requestOriginatedInApp)
{
    if (!hasRunningProcess())
        return;

    setUpHighlightsObserver();

    auto completionHandler = [this, protectedThis = Ref { *this }] (WebCore::AppHighlight&& highlight) {
        MESSAGE_CHECK(!highlight.highlight->isEmpty());
        protectedPageClient()->storeAppHighlight(highlight);
    };
    sendWithAsyncReply(Messages::WebPage::CreateAppHighlightInSelectedRange(createNewGroup, requestOriginatedInApp), WTFMove(completionHandler));
}

void WebPageProxy::restoreAppHighlightsAndScrollToIndex(const Vector<Ref<SharedMemory>>& highlights, const std::optional<unsigned> index)
{
    if (!hasRunningProcess())
        return;

    auto memoryHandles = WTF::compactMap(highlights, [](auto& highlight) {
        return highlight->createHandle(SharedMemory::Protection::ReadOnly);
    });
    
    setUpHighlightsObserver();

    send(Messages::WebPage::RestoreAppHighlightsAndScrollToIndex(WTFMove(memoryHandles), index));
}

void WebPageProxy::setAppHighlightsVisibility(WebCore::HighlightVisibility appHighlightsVisibility)
{
    RELEASE_ASSERT(isMainRunLoop());
    
    if (!hasRunningProcess())
        return;

    send(Messages::WebPage::SetAppHighlightsVisibility(appHighlightsVisibility));
}

bool WebPageProxy::appHighlightsVisibility()
{
    return [m_appHighlightsObserver isVisible];
}

CGRect WebPageProxy::appHighlightsOverlayRect()
{
    if (!m_appHighlightsObserver)
        return CGRectNull;
    return [m_appHighlightsObserver visibleFrame];
}

void WebPageProxy::setUpHighlightsObserver()
{
    if (m_appHighlightsObserver)
        return;

    WeakPtr weakThis { *this };
    auto updateAppHighlightsVisibility = ^(BOOL isVisible) {
        ensureOnMainRunLoop([weakThis, isVisible] {
            if (!weakThis)
                return;
            weakThis->setAppHighlightsVisibility(isVisible ? WebCore::HighlightVisibility::Visible : WebCore::HighlightVisibility::Hidden);
        });
    };
    
    m_appHighlightsObserver = adoptNS([allocSYNotesActivationObserverInstance() initWithHandler:updateAppHighlightsVisibility]);
}

#endif

#if ENABLE(APPLE_PAY_AMS_UI)

void WebPageProxy::startApplePayAMSUISession(URL&& originatingURL, ApplePayAMSUIRequest&& request, CompletionHandler<void(std::optional<bool>&&)>&& completionHandler)
{
    if (!AppleMediaServicesUILibrary()) {
        completionHandler(std::nullopt);
        return;
    }

    // FIXME: When in element fullscreen, UIClient::presentingViewController() may not return the
    // WKFullScreenViewController even though that is the presenting view controller of the WKWebView.
    // We should call PageClientImpl::presentingViewController() instead.
    PlatformViewController *presentingViewController = uiClient().presentingViewController();
    if (!presentingViewController) {
        completionHandler(std::nullopt);
        return;
    }

    auto amsRequest = adoptNS([allocAMSEngagementRequestInstance() initWithRequestDictionary:dynamic_objc_cast<NSDictionary>([NSJSONSerialization JSONObjectWithData:[WTFMove(request.engagementRequest) dataUsingEncoding:NSUTF8StringEncoding] options:0 error:nil])]);
    [amsRequest setOriginatingURL:WTFMove(originatingURL)];

    auto amsBag = retainPtr([getAMSUIEngagementTaskClass() createBagForSubProfile]);

    m_applePayAMSUISession = adoptNS([allocAMSUIEngagementTaskInstance() initWithRequest:amsRequest.get() bag:amsBag.get() presentingViewController:presentingViewController]);
    [m_applePayAMSUISession setRemotePresentation:YES];

    auto amsResult = retainPtr([m_applePayAMSUISession presentEngagement]);
    [amsResult addFinishBlock:makeBlockPtr([completionHandler = WTFMove(completionHandler)] (AMSEngagementResult *result, NSError *error) mutable {
        if (error) {
            completionHandler(std::nullopt);
            return;
        }

        completionHandler(result);
    }).get()];
}

void WebPageProxy::abortApplePayAMSUISession()
{
    [std::exchange(m_applePayAMSUISession, nullptr) cancel];
}

#endif // ENABLE(APPLE_PAY_AMS_UI)

#if ENABLE(CONTEXT_MENUS)

#if HAVE(TRANSLATION_UI_SERVICES)

bool WebPageProxy::canHandleContextMenuTranslation() const
{
    return protectedPageClient()->canHandleContextMenuTranslation();
}

void WebPageProxy::handleContextMenuTranslation(const TranslationContextMenuInfo& info)
{
    return protectedPageClient()->handleContextMenuTranslation(info);
}

#endif // HAVE(TRANSLATION_UI_SERVICES)

#if ENABLE(UNIFIED_TEXT_REPLACEMENT)

bool WebPageProxy::canHandleSwapCharacters() const
{
    return protectedPageClient()->canHandleSwapCharacters();
}

void WebPageProxy::handleContextMenuSwapCharacters(WebCore::IntRect selectionBoundsInRootView)
{
    protectedPageClient()->handleContextMenuSwapCharacters(selectionBoundsInRootView);
}

#endif // ENABLE(UNIFIED_TEXT_REPLACEMENT)

#endif // ENABLE(CONTEXT_MENUS)

void WebPageProxy::requestActiveNowPlayingSessionInfo(CompletionHandler<void(bool, WebCore::NowPlayingInfo&&)>&& callback)
{
    sendWithAsyncReply(Messages::WebPage::RequestActiveNowPlayingSessionInfo(), WTFMove(callback));
}

void WebPageProxy::setLastNavigationWasAppInitiated(ResourceRequest& request)
{
#if ENABLE(APP_PRIVACY_REPORT)
    auto isAppInitiated = request.nsURLRequest(WebCore::HTTPBodyUpdatePolicy::DoNotUpdateHTTPBody).attribution == NSURLRequestAttributionDeveloper;
    if (m_configuration->appInitiatedOverrideValueForTesting() != AttributionOverrideTesting::NoOverride)
        isAppInitiated = m_configuration->appInitiatedOverrideValueForTesting() == AttributionOverrideTesting::AppInitiated;

    request.setIsAppInitiated(isAppInitiated);
    m_lastNavigationWasAppInitiated = isAppInitiated;
#endif
}

void WebPageProxy::lastNavigationWasAppInitiated(CompletionHandler<void(bool)>&& completionHandler)
{
    sendWithAsyncReply(Messages::WebPage::LastNavigationWasAppInitiated(), WTFMove(completionHandler));
}

void WebPageProxy::grantAccessToAssetServices()
{
    auto handles = SandboxExtension::createHandlesForMachLookup({ "com.apple.mobileassetd.v2"_s }, process().auditToken(), SandboxExtension::MachBootstrapOptions::EnableMachBootstrap);
    process().send(Messages::WebProcess::GrantAccessToAssetServices(WTFMove(handles)), 0);
}

void WebPageProxy::revokeAccessToAssetServices()
{
    process().send(Messages::WebProcess::RevokeAccessToAssetServices(), 0);
}

void WebPageProxy::disableURLSchemeCheckInDataDetectors() const
{
    process().send(Messages::WebProcess::DisableURLSchemeCheckInDataDetectors(), 0);
}

void WebPageProxy::switchFromStaticFontRegistryToUserFontRegistry()
{
    if (auto handles = process().fontdMachExtensionHandles())
        process().send(Messages::WebProcess::SwitchFromStaticFontRegistryToUserFontRegistry(WTFMove(*handles)), 0);
}

NSDictionary *WebPageProxy::contentsOfUserInterfaceItem(NSString *userInterfaceItem)
{
#if ENABLE(CONTEXT_MENUS)
    if (m_activeContextMenu && [userInterfaceItem isEqualToString:@"mediaControlsContextMenu"])
        return @{ userInterfaceItem: m_activeContextMenu->platformData() };
#endif // ENABLE(CONTEXT_MENUS)

    return nil;
}

#if PLATFORM(MAC)
bool WebPageProxy::isQuarantinedAndNotUserApproved(const String& fileURLString)
{
    NSURL *fileURL = [NSURL URLWithString:fileURLString];
    if ([fileURL.pathExtension caseInsensitiveCompare:@"webarchive"] != NSOrderedSame)
        return false;

    qtn_file_t qf = qtn_file_alloc();

    int quarantineError = qtn_file_init_with_path(qf, fileURL.path.fileSystemRepresentation);

    if (quarantineError == ENOENT || quarantineError == QTN_NOT_QUARANTINED)
        return false;

    if (quarantineError) {
        // If we fail to check the quarantine status, assume the file is quarantined and not user approved to be safe.
        WEBPAGEPROXY_RELEASE_LOG(Loading, "isQuarantinedAndNotUserApproved: failed to initialize quarantine file with path.");
        qtn_file_free(qf);
        return true;
    }

    uint32_t fileflags = qtn_file_get_flags(qf);
    qtn_file_free(qf);

    if (fileflags & QTN_FLAG_USER_APPROVED)
        return false;

    return true;
}
#endif

#if ENABLE(MULTI_REPRESENTATION_HEIC)

void WebPageProxy::insertMultiRepresentationHEIC(NSData *data, NSString *altText)
{
    send(Messages::WebPage::InsertMultiRepresentationHEIC(span(data), altText));
}

#endif

void WebPageProxy::replaceSelectionWithPasteboardData(const Vector<String>& types, std::span<const uint8_t> data)
{
    send(Messages::WebPage::ReplaceSelectionWithPasteboardData(types, data));
}

RetainPtr<WKWebView> WebPageProxy::cocoaView()
{
    return internals().cocoaView.get();
}

void WebPageProxy::setCocoaView(WKWebView *view)
{
    internals().cocoaView = view;
}

#if ENABLE(IMAGE_ANALYSIS_ENHANCEMENTS)

void WebPageProxy::replaceImageForRemoveBackground(const ElementContext& elementContext, const Vector<String>& types, std::span<const uint8_t> data)
{
    send(Messages::WebPage::ReplaceImageForRemoveBackground(elementContext, types, data));
}

#endif

bool WebPageProxy::useGPUProcessForDOMRenderingEnabled() const
{
    if (id useGPUProcessForDOMRendering = [[NSUserDefaults standardUserDefaults] objectForKey:@"WebKit2GPUProcessForDOMRendering"])
        return [useGPUProcessForDOMRendering boolValue];

    if (preferences().useGPUProcessForDOMRenderingEnabled())
        return true;

#if ENABLE(REMOTE_LAYER_TREE_ON_MAC_BY_DEFAULT)
    if (m_configuration->lockdownModeEnabled())
        return true;
#endif

    HashSet<RefPtr<const WebPageProxy>> visitedPages;
    visitedPages.add(this);
    for (auto* page = m_configuration->relatedPage(); page && !visitedPages.contains(page); page = page->configuration().relatedPage()) {
        if (page->preferences().useGPUProcessForDOMRenderingEnabled())
            return true;
        visitedPages.add(page);
    }

    return false;
}

bool WebPageProxy::shouldForceForegroundPriorityForClientNavigation() const
{
    // The client may request that we do client navigations at foreground priority, even if the
    // view is not visible, as long as the application is foreground.
    if (!configuration().clientNavigationsRunAtForegroundPriority())
        return false;

    // This setting only applies to background views. There is no need to force foreground
    // priority for foreground views since they get foreground priority by virtue of being
    // visible.
    if (isViewVisible())
        return false;

    bool canTakeForegroundAssertions = protectedPageClient()->canTakeForegroundAssertions();
    WEBPAGEPROXY_RELEASE_LOG(Process, "WebPageProxy::shouldForceForegroundPriorityForClientNavigation() returns %d based on PageClient::canTakeForegroundAssertions()", canTakeForegroundAssertions);
    return canTakeForegroundAssertions;
}

#if HAVE(ESIM_AUTOFILL_SYSTEM_SUPPORT)

bool WebPageProxy::shouldAllowAutoFillForCellularIdentifiers() const
{
    return WebKit::shouldAllowAutoFillForCellularIdentifiers(URL { pageLoadState().activeURL() });
}

#endif

#if ENABLE(EXTENSION_CAPABILITIES)

const std::optional<MediaCapability>& WebPageProxy::mediaCapability() const
{
    return internals().mediaCapability;
}

void WebPageProxy::setMediaCapability(std::optional<MediaCapability>&& capability)
{
    if (auto oldCapability = std::exchange(internals().mediaCapability, std::nullopt))
        deactivateMediaCapability(*oldCapability);

    internals().mediaCapability = WTFMove(capability);

    if (!internals().mediaCapability) {
        WEBPAGEPROXY_RELEASE_LOG(ProcessCapabilities, "setMediaCapability: clearing media capability");
        send(Messages::WebPage::SetMediaEnvironment({ }));
        return;
    }

    WEBPAGEPROXY_RELEASE_LOG(ProcessCapabilities, "setMediaCapability: creating (envID=%{public}s) for URL '%{sensitive}s'", internals().mediaCapability->environmentIdentifier().utf8().data(), internals().mediaCapability->webPageURL().string().utf8().data());
    send(Messages::WebPage::SetMediaEnvironment(internals().mediaCapability->environmentIdentifier()));
}

void WebPageProxy::deactivateMediaCapability(MediaCapability& capability)
{
    WEBPAGEPROXY_RELEASE_LOG(ProcessCapabilities, "deactivateMediaCapability: deactivating (envID=%{public}s) for URL '%{sensitive}s'", capability.environmentIdentifier().utf8().data(), capability.webPageURL().string().utf8().data());
    Ref processPool { protectedProcess()->protectedProcessPool() };
    processPool->extensionCapabilityGranter().setMediaCapabilityActive(capability, false);
    processPool->extensionCapabilityGranter().revoke(capability);
}

void WebPageProxy::resetMediaCapability()
{
    if (!preferences().mediaCapabilityGrantsEnabled())
        return;

    URL currentURL { this->currentURL() };

    if (!hasRunningProcess() || !currentURL.isValid()) {
        setMediaCapability(std::nullopt);
        return;
    }

    if (!mediaCapability() || !protocolHostAndPortAreEqual(mediaCapability()->webPageURL(), currentURL))
        setMediaCapability(MediaCapability { WTFMove(currentURL) });
}

void WebPageProxy::updateMediaCapability()
{
    auto& mediaCapability = internals().mediaCapability;
    if (!mediaCapability)
        return;

    if (shouldDeactivateMediaCapability()) {
        deactivateMediaCapability(*mediaCapability);
        return;
    }

    Ref processPool { protectedProcess()->protectedProcessPool() };

    if (shouldActivateMediaCapability())
        processPool->extensionCapabilityGranter().setMediaCapabilityActive(*mediaCapability, true);

    if (mediaCapability->isActivatingOrActive())
        processPool->extensionCapabilityGranter().grant(*mediaCapability);
}

bool WebPageProxy::shouldActivateMediaCapability() const
{
    if (!isViewVisible())
        return false;

    if (internals().mediaState.contains(MediaProducerMediaState::IsPlayingAudio))
        return true;

    if (internals().mediaState.contains(MediaProducerMediaState::IsPlayingVideo))
        return true;

    return MediaProducer::isCapturing(internals().mediaState);
}

bool WebPageProxy::shouldDeactivateMediaCapability() const
{
    if (!mediaCapability() || !mediaCapability()->isActivatingOrActive())
        return false;

    if (internals().mediaState & WebCore::MediaProducer::MediaCaptureMask)
        return false;

    if (internals().mediaState.containsAny(MediaProducerMediaState::HasAudioOrVideo))
        return false;

    if (hasValidAudibleActivity())
        return false;

    return true;
}

#endif // ENABLE(EXTENSION_CAPABILITIES)

#if ENABLE(UNIFIED_TEXT_REPLACEMENT)

void WebPageProxy::setUnifiedTextReplacementActive(bool active)
{
    if (m_isUnifiedTextReplacementActive == active)
        return;

    protectedPageClient()->unifiedTextReplacementActiveWillChange();
    m_isUnifiedTextReplacementActive = active;
    protectedPageClient()->unifiedTextReplacementActiveDidChange();
}

void WebPageProxy::willBeginTextReplacementSession(const std::optional<WebUnifiedTextReplacementSessionData>& session, CompletionHandler<void(const Vector<WebUnifiedTextReplacementContextData>&)>&& completionHandler)
{
    sendWithAsyncReply(Messages::WebPage::WillBeginTextReplacementSession(session), WTFMove(completionHandler));
}

void WebPageProxy::didBeginTextReplacementSession(const WebUnifiedTextReplacementSessionData& session, const Vector<WebKit::WebUnifiedTextReplacementContextData>& contexts)
{
    send(Messages::WebPage::DidBeginTextReplacementSession(session, contexts));
}

void WebPageProxy::textReplacementSessionDidReceiveReplacements(const WebUnifiedTextReplacementSessionData& session, const Vector<WebTextReplacementData>& replacements, const WebUnifiedTextReplacementContextData& context, bool finished)
{
    send(Messages::WebPage::TextReplacementSessionDidReceiveReplacements(session, replacements, context, finished));
}

void WebPageProxy::textReplacementSessionDidUpdateStateForReplacement(const WebUnifiedTextReplacementSessionData& session, WebTextReplacementData::State state, const WebTextReplacementData& replacement, const WebUnifiedTextReplacementContextData& context)
{
    send(Messages::WebPage::TextReplacementSessionDidUpdateStateForReplacement(session, state, replacement, context));
}

void WebPageProxy::didEndTextReplacementSession(const WebUnifiedTextReplacementSessionData& session, bool accepted)
{
    send(Messages::WebPage::DidEndTextReplacementSession(session, accepted));
}

void WebPageProxy::textReplacementSessionDidReceiveTextWithReplacementRange(const WebUnifiedTextReplacementSessionData& session, const WebCore::AttributedString& attributedText, const WebCore::CharacterRange& range, const WebUnifiedTextReplacementContextData& context, bool finished)
{
    send(Messages::WebPage::TextReplacementSessionDidReceiveTextWithReplacementRange(session, attributedText, range, context, finished));
}

void WebPageProxy::textReplacementSessionDidReceiveEditAction(const WebUnifiedTextReplacementSessionData& session, WebTextReplacementData::EditAction action)
{
    send(Messages::WebPage::TextReplacementSessionDidReceiveEditAction(session, action));
}

void WebPageProxy::enableTextIndicatorStyleAfterElementWithID(const String& elementID, const WTF::UUID& uuid)
{
    if (!hasRunningProcess())
        return;

    send(Messages::WebPage::EnableTextIndicatorStyleAfterElementWithID(elementID, uuid));
}

void WebPageProxy::enableTextIndicatorStyleForElementWithID(const String& elementID, const WTF::UUID& uuid)
{
    if (!hasRunningProcess())
        return;

    send(Messages::WebPage::EnableTextIndicatorStyleForElementWithID(elementID, uuid));
}

void WebPageProxy::addTextIndicatorStyleForID(const WTF::UUID& uuid, const TextIndicatorStyle styleType, const WebCore::TextIndicatorData& data)
{
    MESSAGE_CHECK(uuid.isValid());

    internals().textIndicatorDataForChunk.add(uuid, data);

    protectedPageClient()->addTextIndicatorStyleForID(uuid, styleType);
}

void WebPageProxy::getTextIndicatorForID(const WTF::UUID& uuid, CompletionHandler<void(std::optional<WebCore::TextIndicatorData>&&)>&& completionHandler)
{
    if (!hasRunningProcess()) {
        completionHandler(std::nullopt);
        return;
    }

    auto textIndicatorData = internals().textIndicatorDataForChunk.getOptional(uuid);

    if (textIndicatorData) {
        completionHandler(*textIndicatorData);
        return;
    }

    sendWithAsyncReply(Messages::WebPage::CreateTextIndicatorForID(uuid), WTFMove(completionHandler));
}

void WebPageProxy::updateTextIndicatorStyleVisibilityForID(const WTF::UUID& uuid, bool visible, CompletionHandler<void()>&& completionHandler)
{
    if (!hasRunningProcess()) {
        completionHandler();
        return;
    }

    sendWithAsyncReply(Messages::WebPage::UpdateTextIndicatorStyleVisibilityForID(uuid, visible), WTFMove(completionHandler));
}

void WebPageProxy::textReplacementSessionShowInformationForReplacementWithUUIDRelativeToRect(const WTF::UUID& sessionUUID, const WTF::UUID& replacementUUID, WebCore::IntRect selectionBoundsInRootView)
{
    MESSAGE_CHECK(sessionUUID.isValid());

    protectedPageClient()->textReplacementSessionShowInformationForReplacementWithUUIDRelativeToRect(sessionUUID, replacementUUID, selectionBoundsInRootView);
}

void WebPageProxy::textReplacementSessionUpdateStateForReplacementWithUUID(const WTF::UUID& sessionUUID, WebTextReplacementData::State state, const WTF::UUID& replacementUUID)
{
    MESSAGE_CHECK(sessionUUID.isValid());

    protectedPageClient()->textReplacementSessionUpdateStateForReplacementWithUUID(sessionUUID, state, replacementUUID);
}

void WebPageProxy::removeTextIndicatorStyleForID(const WTF::UUID& uuid)
{
    MESSAGE_CHECK(uuid.isValid());

    protectedPageClient()->removeTextIndicatorStyleForID(uuid);
}

#endif

} // namespace WebKit

#undef MESSAGE_CHECK_COMPLETION
#undef MESSAGE_CHECK

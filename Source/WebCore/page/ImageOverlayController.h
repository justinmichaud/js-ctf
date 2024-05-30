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

#include "Color.h"
#include "LayoutRect.h"
#include "PageOverlay.h"
#include <wtf/OptionSet.h>
#include <wtf/Vector.h>
#include <wtf/WeakPtr.h>

#if PLATFORM(MAC)
#include "DataDetectorHighlight.h"
#endif

namespace WebCore {

class Document;
class Element;
class GraphicsContext;
class GraphicsLayer;
class GraphicsLayerClient;
class HTMLElement;
class IntRect;
class FloatQuad;
class LocalFrame;
class Page;
class RenderElement;
class WeakPtrImplWithEventTargetData;
enum class RenderingUpdateStep : uint32_t;
struct GapRects;

class ImageOverlayController final : private PageOverlayClient
#if PLATFORM(MAC)
    , DataDetectorHighlightClient
#endif
{
    WTF_MAKE_FAST_ALLOCATED;
public:
    explicit ImageOverlayController(Page&);

    void selectionQuadsDidChange(LocalFrame&, const Vector<FloatQuad>&);
    void elementUnderMouseDidChange(LocalFrame&, Element*);

#if ENABLE(DATA_DETECTION)
    WEBCORE_EXPORT bool hasActiveDataDetectorHighlightForTesting() const;
    void textRecognitionResultsChanged(HTMLElement&);
#endif

    void documentDetached(const Document&);

private:
    void willMoveToPage(PageOverlay&, Page*) final;
    void didMoveToPage(PageOverlay&, Page*) final { }
    void drawRect(PageOverlay&, GraphicsContext&, const IntRect& dirtyRect) final;
    bool mouseEvent(PageOverlay&, const PlatformMouseEvent& event) final { return platformHandleMouseEvent(event); }

    bool shouldUsePageOverlayToPaintSelection(const RenderElement&);

    PageOverlay& installPageOverlayIfNeeded();
    void uninstallPageOverlayIfNeeded();
    void uninstallPageOverlay();

#if PLATFORM(MAC)
    void updateDataDetectorHighlights(const HTMLElement&);
    void clearDataDetectorHighlights();
    bool handleDataDetectorAction(const HTMLElement&, const IntPoint&);

    // DataDetectorHighlightClient
#if ENABLE(DATA_DETECTION)
    DataDetectorHighlight* activeHighlight() const final { return m_activeDataDetectorHighlight.get(); }
    void scheduleRenderingUpdate(OptionSet<RenderingUpdateStep>) final;
    float deviceScaleFactor() const final;
    RefPtr<GraphicsLayer> createGraphicsLayer(GraphicsLayerClient&) final;
#endif
#endif

    void platformUpdateElementUnderMouse(LocalFrame&, Element* elementUnderMouse);
    bool platformHandleMouseEvent(const PlatformMouseEvent&);

    RefPtr<Page> protectedPage() const;
    RefPtr<PageOverlay> protectedOverlay() const { return m_overlay; }

    SingleThreadWeakPtr<Page> m_page;
    RefPtr<PageOverlay> m_overlay;
    WeakPtr<HTMLElement, WeakPtrImplWithEventTargetData> m_hostElementForSelection;
    Vector<FloatQuad> m_selectionQuads;
    LayoutRect m_selectionClipRect;
    Color m_selectionBackgroundColor { Color::transparentBlack };

#if PLATFORM(MAC)
    using ContainerAndHighlight = std::pair<WeakPtr<HTMLElement, WeakPtrImplWithEventTargetData>, Ref<DataDetectorHighlight>>;
    Vector<ContainerAndHighlight> m_dataDetectorContainersAndHighlights;
    RefPtr<DataDetectorHighlight> m_activeDataDetectorHighlight;
    WeakPtr<HTMLElement, WeakPtrImplWithEventTargetData> m_hostElementForDataDetectors;
#endif
};

} // namespace WebCore

/*
 * Copyright (C) 2009-2023 Apple Inc. All rights reserved.
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

#include "CanvasBase.h"
#include "GraphicsLayerContentsDisplayDelegate.h"
#include "ScriptWrappable.h"
#include <wtf/CheckedRef.h>
#include <wtf/Forward.h>
#include <wtf/IsoMalloc.h>
#include <wtf/Lock.h>
#include <wtf/Noncopyable.h>
#include <wtf/text/StringHash.h>

namespace WebCore {

class CSSStyleImageValue;
class CachedImage;
class CanvasPattern;
class DestinationColorSpace;
class GraphicsLayer;
class HTMLCanvasElement;
class HTMLImageElement;
class HTMLVideoElement;
class ImageBitmap;
class SVGImageElement;
class WebGLObject;
enum class PixelFormat : uint8_t;

class CanvasRenderingContext : public ScriptWrappable, public CanMakeWeakPtr<CanvasRenderingContext> {
    WTF_MAKE_NONCOPYABLE(CanvasRenderingContext);
    WTF_MAKE_ISO_ALLOCATED(CanvasRenderingContext);
public:
    virtual ~CanvasRenderingContext();

    static HashSet<CanvasRenderingContext*>& instances() WTF_REQUIRES_LOCK(instancesLock());
    static Lock& instancesLock() WTF_RETURNS_LOCK(s_instancesLock);

    WEBCORE_EXPORT void ref() const;
    WEBCORE_EXPORT void deref() const;

    CanvasBase& canvasBase() const { return m_canvas; }

    virtual bool is2dBase() const { return false; }
    virtual bool is2d() const { return false; }
    virtual bool isWebGL1() const { return false; }
    virtual bool isWebGL2() const { return false; }
    bool isWebGL() const { return isWebGL1() || isWebGL2(); }
    virtual bool isWebGPU() const { return false; }
    virtual bool isGPUBased() const { return false; }
    virtual bool isAccelerated() const { return false; }
    virtual bool isBitmapRenderer() const { return false; }
    virtual bool isPlaceholder() const { return false; }
    virtual bool isOffscreen2d() const { return false; }
    virtual bool isPaint() const { return false; }

    virtual void clearAccumulatedDirtyRect() { }

    // Canvas 2DContext drawing buffer is the same as display buffer.
    // WebGL, WebGPU draws to drawing buffer. The draw buffer is then swapped to
    // display buffer during preparation and compositor composites the display buffer.
    // toDataURL and similar functions from JS execution reads the drawing buffer.
    // Web Inspector and similar reads from the engine reads both.
    enum class SurfaceBuffer : uint8_t {
        DrawingBuffer,
        DisplayBuffer
    };

    // Draws the source buffer to the canvasBase().buffer().
    virtual void drawBufferToCanvas(SurfaceBuffer) { }
    virtual RefPtr<GraphicsLayerContentsDisplayDelegate> layerContentsDisplayDelegate();
    virtual void setContentsToLayer(GraphicsLayer&);

    bool hasActiveInspectorCanvasCallTracer() const { return m_hasActiveInspectorCanvasCallTracer; }
    void setHasActiveInspectorCanvasCallTracer(bool hasActiveInspectorCanvasCallTracer) { m_hasActiveInspectorCanvasCallTracer = hasActiveInspectorCanvasCallTracer; }

    // Returns true if there are pending deferred operations that might consume memory.
    virtual bool hasDeferredOperations() const { return false; }

    // Called periodically if needsFlush() was true when canvas change happened.
    virtual void flushDeferredOperations() { }

    virtual bool compositingResultsNeedUpdating() const { return false; }
    virtual bool needsPreparationForDisplay() const { return false; }
    // Swaps the current drawing buffer to display buffer.
    virtual void prepareForDisplay() { }

    virtual PixelFormat pixelFormat() const;
    virtual DestinationColorSpace colorSpace() const;
    virtual bool willReadFrequently() const;
    virtual OptionSet<ImageBufferOptions> adjustImageBufferOptionsForTesting(OptionSet<ImageBufferOptions> bufferOptions) { return bufferOptions; }

    void setIsInPreparationForDisplayOrFlush(bool flag) { m_isInPreparationForDisplayOrFlush = flag; }
    bool isInPreparationForDisplayOrFlush() const { return m_isInPreparationForDisplayOrFlush; }

protected:
    explicit CanvasRenderingContext(CanvasBase&);
    bool taintsOrigin(const CanvasPattern*);
    bool taintsOrigin(const CanvasBase*);
    bool taintsOrigin(const CachedImage*);
    bool taintsOrigin(const HTMLImageElement*);
    bool taintsOrigin(const SVGImageElement*);
    bool taintsOrigin(const HTMLVideoElement*);
    bool taintsOrigin(const ImageBitmap*);
    bool taintsOrigin(const URL&);

    template<class T> void checkOrigin(const T* arg)
    {
        if (m_canvas.originClean() && taintsOrigin(arg))
            m_canvas.setOriginTainted();
    }
    void checkOrigin(const URL&);
    void checkOrigin(const CSSStyleImageValue&);

    bool m_isInPreparationForDisplayOrFlush { false };
    bool m_hasActiveInspectorCanvasCallTracer { false };

private:
    static Lock s_instancesLock;

    CanvasBase& m_canvas;
};

} // namespace WebCore

#define SPECIALIZE_TYPE_TRAITS_CANVASRENDERINGCONTEXT(ToValueTypeName, predicate) \
SPECIALIZE_TYPE_TRAITS_BEGIN(ToValueTypeName) \
    static bool isType(const WebCore::CanvasRenderingContext& context) { return context.predicate; } \
SPECIALIZE_TYPE_TRAITS_END()

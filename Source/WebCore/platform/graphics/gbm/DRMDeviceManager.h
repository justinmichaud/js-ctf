/*
 * Copyright (C) 2024 Igalia S.L.
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

#if USE(LIBDRM)

#include <wtf/Noncopyable.h>
#include <wtf/RefPtr.h>

#if USE(GBM)
struct gbm_device;
#endif

namespace WTF {
class CString;
class String;
}

namespace WebCore {

class DRMDeviceNode;

class DRMDeviceManager {
    WTF_MAKE_NONCOPYABLE(DRMDeviceManager);
    WTF_MAKE_FAST_ALLOCATED();
public:
    static DRMDeviceManager& singleton();

    DRMDeviceManager() = default;
    ~DRMDeviceManager();

    void initializeMainDevice(const WTF::String&);
    bool isInitialized() const { return m_mainDevice.isInitialized; }

    enum class NodeType : bool { Primary, Render };
    RefPtr<DRMDeviceNode> mainDeviceNode(NodeType) const;
    RefPtr<DRMDeviceNode> deviceNode(const WTF::CString&);

#if USE(GBM)
    struct gbm_device* mainGBMDeviceNode(NodeType) const;
#endif

private:
    struct {
        bool isInitialized { false };
        RefPtr<DRMDeviceNode> primaryNode;
        RefPtr<DRMDeviceNode> renderNode;
    } m_mainDevice;
};

} // namespace WebCore

#endif // USE(LIBDRM)

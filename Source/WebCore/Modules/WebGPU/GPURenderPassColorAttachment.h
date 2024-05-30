/*
 * Copyright (C) 2021-2023 Apple Inc. All rights reserved.
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

#include "GPUColorDict.h"
#include "GPUIntegralTypes.h"
#include "GPULoadOp.h"
#include "GPUStoreOp.h"
#include "GPUTextureView.h"
#include "WebGPURenderPassColorAttachment.h"
#include <variant>
#include <wtf/RefPtr.h>
#include <wtf/Vector.h>

namespace WebCore {

struct GPURenderPassColorAttachment {
    WebGPU::RenderPassColorAttachment convertToBacking() const
    {
        ASSERT(view);
        return {
            .view = view->backing(),
            .depthSlice = depthSlice,
            .resolveTarget = resolveTarget ? &resolveTarget->backing() : nullptr,
            .clearValue = clearValue ? std::optional { WebCore::convertToBacking(*clearValue) } : std::nullopt,
            .loadOp = WebCore::convertToBacking(loadOp),
            .storeOp = WebCore::convertToBacking(storeOp),
        };
    }

    WeakPtr<GPUTextureView> view;
    std::optional<GPUIntegerCoordinate> depthSlice;
    WeakPtr<GPUTextureView> resolveTarget;

    std::optional<GPUColor> clearValue;
    GPULoadOp loadOp { GPULoadOp::Load };
    GPUStoreOp storeOp { GPUStoreOp::Store };
};

}

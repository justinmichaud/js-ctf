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

#include "config.h"
#include "RemoteTexture.h"

#if ENABLE(GPU_PROCESS)

#include "GPUConnectionToWebProcess.h"
#include "RemoteTextureMessages.h"
#include "RemoteTextureView.h"
#include "StreamServerConnection.h"
#include "WebGPUObjectHeap.h"
#include "WebGPUTextureViewDescriptor.h"
#include <WebCore/WebGPUTexture.h>
#include <WebCore/WebGPUTextureView.h>
#include <WebCore/WebGPUTextureViewDescriptor.h>

#if PLATFORM(COCOA)
#define MESSAGE_CHECK(assertion) do { \
    if (UNLIKELY(!(assertion))) { \
        if (auto connection = m_gpuConnectionToWebProcess.get()) \
            connection->terminateWebProcess(); \
        return; \
    } \
} while (0)
#else
#define MESSAGE_CHECK RELEASE_ASSERT
#endif

namespace WebKit {

RemoteTexture::RemoteTexture(GPUConnectionToWebProcess& gpuConnectionToWebProcess, WebCore::WebGPU::Texture& texture, WebGPU::ObjectHeap& objectHeap, Ref<IPC::StreamServerConnection>&& streamConnection, WebGPUIdentifier identifier)
    : m_backing(texture)
    , m_objectHeap(objectHeap)
    , m_streamConnection(WTFMove(streamConnection))
    , m_identifier(identifier)
    , m_gpuConnectionToWebProcess(gpuConnectionToWebProcess)
{
    m_streamConnection->startReceivingMessages(*this, Messages::RemoteTexture::messageReceiverName(), m_identifier.toUInt64());
}

RemoteTexture::~RemoteTexture() = default;

void RemoteTexture::stopListeningForIPC()
{
    m_streamConnection->stopReceivingMessages(Messages::RemoteTexture::messageReceiverName(), m_identifier.toUInt64());
}

void RemoteTexture::createView(const std::optional<WebGPU::TextureViewDescriptor>& descriptor, WebGPUIdentifier identifier)
{
    std::optional<WebCore::WebGPU::TextureViewDescriptor> convertedDescriptor;
    if (descriptor) {
        auto resultDescriptor = m_objectHeap->convertFromBacking(*descriptor);
        MESSAGE_CHECK(resultDescriptor);
        convertedDescriptor = WTFMove(resultDescriptor);
    }
    auto textureView = m_backing->createView(convertedDescriptor);
    MESSAGE_CHECK(textureView);
    auto remoteTextureView = RemoteTextureView::create(textureView.releaseNonNull(), m_objectHeap, m_streamConnection.copyRef(), identifier);
    m_objectHeap->addObject(identifier, remoteTextureView);
}

void RemoteTexture::destroy()
{
    m_backing->destroy();
}

void RemoteTexture::destruct()
{
    m_objectHeap->removeObject(m_identifier);
}

void RemoteTexture::setLabel(String&& label)
{
    m_backing->setLabel(WTFMove(label));
}

} // namespace WebKit

#undef MESSAGE_CHECK

#endif // ENABLE(GPU_PROCESS)

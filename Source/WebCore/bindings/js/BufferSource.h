/*
 * Copyright (C) 2016 Igalia S.L.
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

#include <JavaScriptCore/ArrayBuffer.h>
#include <JavaScriptCore/ArrayBufferView.h>
#include <span>
#include <variant>
#include <wtf/RefPtr.h>

#if PLATFORM(COCOA) && defined(__OBJC__)
#include <wtf/cocoa/SpanCocoa.h>
OBJC_CLASS NSData;
#endif

namespace WebCore {

class BufferSource {
public:
    using VariantType = std::variant<RefPtr<JSC::ArrayBufferView>, RefPtr<JSC::ArrayBuffer>>;

    BufferSource() { }
    BufferSource(VariantType&& variant)
        : m_variant(WTFMove(variant))
    { }
    explicit BufferSource(std::span<const uint8_t> span)
        : m_variant(JSC::ArrayBuffer::tryCreate(span.data(), span.size_bytes())) { }

    const VariantType& variant() const { return m_variant; }

    const uint8_t* data() const
    {
        return std::visit([](auto& buffer) -> const uint8_t* {
            return buffer ? static_cast<const uint8_t*>(buffer->data()) : nullptr;
        }, m_variant);
    }
    
    void* mutableData() const
    {
        return std::visit([](auto& buffer) -> void* {
            return buffer->data();
        }, m_variant);
    }

    size_t length() const
    {
        return std::visit([](auto& buffer) -> size_t {
            return buffer ? buffer->byteLength() : 0;
        }, m_variant);
    }

    std::span<const uint8_t> span() const { return { data(), length() }; }

private:
    VariantType m_variant;
};

inline BufferSource toBufferSource(std::span<const uint8_t> data)
{
    return BufferSource(JSC::ArrayBuffer::tryCreate(data));
}

#if PLATFORM(COCOA) && defined(__OBJC__)
inline BufferSource toBufferSource(NSData *data)
{
    return BufferSource(JSC::ArrayBuffer::tryCreate(span(data)));
}

inline RetainPtr<NSData> toNSData(const BufferSource& data)
{
    return adoptNS([[NSData alloc] initWithBytes:data.data() length:data.length()]);
}
#endif

} // namespace WebCore

#if PLATFORM(COCOA) && defined(__OBJC__)
using WebCore::toNSData;
#endif

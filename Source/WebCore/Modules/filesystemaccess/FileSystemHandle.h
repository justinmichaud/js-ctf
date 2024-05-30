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

#include "ActiveDOMObject.h"
#include "FileSystemHandleIdentifier.h"
#include "IDLTypes.h"
#include <wtf/IsoMalloc.h>
#include <wtf/ThreadSafeWeakPtr.h>

namespace WebCore {

template<typename> class DOMPromiseDeferred;

class FileSystemStorageConnection;

class FileSystemHandle : public ActiveDOMObject, public ThreadSafeRefCountedAndCanMakeThreadSafeWeakPtr<FileSystemHandle> {
    WTF_MAKE_ISO_ALLOCATED(FileSystemHandle);
public:
    virtual ~FileSystemHandle();

    void ref() const final { ThreadSafeRefCountedAndCanMakeThreadSafeWeakPtr::ref(); }
    void deref() const final { ThreadSafeRefCountedAndCanMakeThreadSafeWeakPtr::deref(); }

    enum class Kind : uint8_t {
        File,
        Directory
    };
    Kind kind() const { return m_kind; }
    const String& name() const { return m_name; }
    FileSystemHandleIdentifier identifier() const { return m_identifier; }
    bool isClosed() const { return m_isClosed; }
    void close();

    void isSameEntry(FileSystemHandle&, DOMPromiseDeferred<IDLBoolean>&&) const;
    void move(FileSystemHandle&, const String& newName, DOMPromiseDeferred<void>&&);

protected:
    FileSystemHandle(ScriptExecutionContext&, Kind, String&& name, FileSystemHandleIdentifier, Ref<FileSystemStorageConnection>&&);
    FileSystemStorageConnection& connection() { return m_connection.get(); }

private:
    // ActiveDOMObject.
    void stop() final;

    Kind m_kind { Kind::File };
    String m_name;
    FileSystemHandleIdentifier m_identifier;
    Ref<FileSystemStorageConnection> m_connection;
    bool m_isClosed { false };
};

} // namespace WebCore

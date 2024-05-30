/*
 * Copyright (C) 2020 Apple Inc. All rights reserved.
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

#if ENABLE(IPC_TESTING_API) || !LOG_DISABLED

#include "MessageNames.h"
#include <wtf/Vector.h>

namespace JSC {

class JSGlobalObject;
class JSValue;

}

namespace IPC {

class Decoder;

#if ENABLE(IPC_TESTING_API)

std::optional<JSC::JSValue> jsValueForArguments(JSC::JSGlobalObject*, MessageName, Decoder&);
std::optional<JSC::JSValue> jsValueForReplyArguments(JSC::JSGlobalObject*, MessageName, Decoder&);

Vector<ASCIILiteral> serializedIdentifiers();

#endif // ENABLE(IPC_TESTING_API)

struct ArgumentDescription {
    ASCIILiteral name;
    ASCIILiteral type;
    ASCIILiteral enumName;
    bool isOptional;
};

std::optional<Vector<ArgumentDescription>> messageArgumentDescriptions(MessageName);
std::optional<Vector<ArgumentDescription>> messageReplyArgumentDescriptions(MessageName);

}

#endif // ENABLE(IPC_TESTING_API) || !LOG_DISABLED

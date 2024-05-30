/*
 * Copyright (C) 2023 Igalia S.L. All rights reserved.
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

#include "JSDOMPromise.h"
#include "NavigationHistoryEntry.h"
#include "NavigationNavigationType.h"
#include "ScriptWrappable.h"

namespace WebCore {

class DOMPromise;

class NavigationTransition final : public RefCounted<NavigationTransition>, public ScriptWrappable {
    WTF_MAKE_ISO_ALLOCATED(NavigationTransition);
public:
    static Ref<NavigationTransition> create(NavigationNavigationType type, Ref<NavigationHistoryEntry>&& fromEntry) { return adoptRef(*new NavigationTransition(type, WTFMove(fromEntry))); };

    NavigationNavigationType navigationType() { return m_navigationType; };
    NavigationHistoryEntry& from() { return m_from; };
    DOMPromise* finished() { return m_finished.get(); };

private:
    explicit NavigationTransition(NavigationNavigationType, Ref<NavigationHistoryEntry>&& fromEntry);

    NavigationNavigationType m_navigationType;
    Ref<NavigationHistoryEntry> m_from;
    RefPtr<DOMPromise> m_finished;
};

} // namespace WebCore

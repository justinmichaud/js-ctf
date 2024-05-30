/*
 * Copyright (C) 2013 Apple Inc. All rights reserved.
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

#include <wtf/URL.h>
#include <wtf/WeakHashSet.h>

namespace WebKit {
class FrameLoadStateObserver;
}

namespace WTF {
template<typename T> struct IsDeprecatedWeakRefSmartPointerException;
template<> struct IsDeprecatedWeakRefSmartPointerException<WebKit::FrameLoadStateObserver> : std::true_type { };
}

namespace WebKit {

class FrameLoadStateObserver : public CanMakeWeakPtr<FrameLoadStateObserver> {
public:
    virtual ~FrameLoadStateObserver() = default;
    virtual void didReceiveProvisionalURL(const URL&) { }
    virtual void didCancelProvisionalLoad() { }
    virtual void didCommitProvisionalLoad() { }
    virtual void didFinishLoad() { }
};

class FrameLoadState {
public:
    ~FrameLoadState();

    enum class State {
        Provisional,
        Committed,
        Finished
    };

    void addObserver(FrameLoadStateObserver&);
    void removeObserver(FrameLoadStateObserver&);

    void didStartProvisionalLoad(const URL&);
    void didExplicitOpen(const URL&);
    void didReceiveServerRedirectForProvisionalLoad(const URL&);
    void didFailProvisionalLoad();
    void didSuspend();

    void didCommitLoad();
    void didFinishLoad();
    void didFailLoad();

    void didSameDocumentNotification(const URL&);

    State state() const { return m_state; }
    const URL& url() const { return m_url; }
    void setURL(const URL&);
    const URL& provisionalURL() const { return m_provisionalURL; }

    void setUnreachableURL(const URL&);
    const URL& unreachableURL() const { return m_unreachableURL; }

private:
    State m_state { State::Finished };
    URL m_url;
    URL m_provisionalURL;
    URL m_unreachableURL;
    URL m_lastUnreachableURL;
    WeakHashSet<FrameLoadStateObserver> m_observers;
};

} // namespace WebKit

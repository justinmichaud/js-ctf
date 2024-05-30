/*
 * Copyright (C) 2022 Apple Inc. All rights reserved.
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
#include "ContextDestructionObserverInlines.h"
#include "EventTarget.h"
#include "ScreenOrientationLockType.h"
#include "ScreenOrientationManager.h"
#include "ScreenOrientationType.h"
#include "VisibilityChangeClient.h"
#include <wtf/RefCounted.h>

namespace WebCore {

class DeferredPromise;

class ScreenOrientation final : public ActiveDOMObject, public EventTarget, public ScreenOrientationManagerObserver, public VisibilityChangeClient, public RefCounted<ScreenOrientation> {
    WTF_MAKE_ISO_ALLOCATED(ScreenOrientation);
public:
    static Ref<ScreenOrientation> create(Document*);
    ~ScreenOrientation();

    using ScreenOrientationManagerObserver::weakPtrFactory;
    using ScreenOrientationManagerObserver::WeakValueType;
    using ScreenOrientationManagerObserver::WeakPtrImplType;

    using LockType = ScreenOrientationLockType;
    using Type = ScreenOrientationType;

    void lock(LockType, Ref<DeferredPromise>&&);
    ExceptionOr<void> unlock();
    Type type() const;
    uint16_t angle() const;

    // ActiveDOMObject.
    void ref() const final { RefCounted::ref(); }
    void deref() const final { RefCounted::deref(); }

private:
    ScreenOrientation(Document*);

    Document* document() const;
    ScreenOrientationManager* manager() const;

    bool shouldListenForChangeNotification() const;

    // VisibilityChangeClient
    void visibilityStateChanged() final;

    // ScreenOrientationManagerObserver
    void screenOrientationDidChange(ScreenOrientationType) final;

    // EventTarget
    enum EventTargetInterfaceType eventTargetInterface() const final { return EventTargetInterfaceType::ScreenOrientation; }
    ScriptExecutionContext* scriptExecutionContext() const final { return ActiveDOMObject::scriptExecutionContext(); }
    void refEventTarget() final { RefCounted::ref(); }
    void derefEventTarget() final { RefCounted::deref(); }
    void eventListenersDidChange() final;

    // ActiveDOMObject.
    bool virtualHasPendingActivity() const final;
    void suspend(ReasonForSuspension) final;
    void resume() final;
    void stop() final;

    bool m_hasChangeEventListener { false };
};

} // namespace WebCore

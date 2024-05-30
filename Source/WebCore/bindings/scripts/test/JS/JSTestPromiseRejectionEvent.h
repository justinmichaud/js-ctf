/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#pragma once

#include "JSDOMConvertDictionary.h"
#include "JSDOMWrapper.h"
#include "JSEvent.h"
#include "TestPromiseRejectionEvent.h"

namespace WebCore {

class JSTestPromiseRejectionEvent : public JSEvent {
public:
    using Base = JSEvent;
    using DOMWrapped = TestPromiseRejectionEvent;
    static JSTestPromiseRejectionEvent* create(JSC::Structure* structure, JSDOMGlobalObject* globalObject, Ref<TestPromiseRejectionEvent>&& impl)
    {
        auto& vm = globalObject->vm();
        JSTestPromiseRejectionEvent* ptr = new (NotNull, JSC::allocateCell<JSTestPromiseRejectionEvent>(vm)) JSTestPromiseRejectionEvent(structure, *globalObject, WTFMove(impl));
        ptr->finishCreation(vm);
        return ptr;
    }

    static JSC::JSObject* createPrototype(JSC::VM&, JSDOMGlobalObject&);
    static JSC::JSObject* prototype(JSC::VM&, JSDOMGlobalObject&);

    DECLARE_INFO;

    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::JSType(JSEventType), StructureFlags), info(), JSC::NonArray);
    }

    static JSC::JSValue getConstructor(JSC::VM&, const JSC::JSGlobalObject*);
    template<typename, JSC::SubspaceAccess mode> static JSC::GCClient::IsoSubspace* subspaceFor(JSC::VM& vm)
    {
        if constexpr (mode == JSC::SubspaceAccess::Concurrently)
            return nullptr;
        return subspaceForImpl(vm);
    }
    static JSC::GCClient::IsoSubspace* subspaceForImpl(JSC::VM& vm);
    static void analyzeHeap(JSCell*, JSC::HeapAnalyzer&);
    TestPromiseRejectionEvent& wrapped() const
    {
        return static_cast<TestPromiseRejectionEvent&>(Base::wrapped());
    }

    Ref<TestPromiseRejectionEvent> protectedWrapped() const;

protected:
    JSTestPromiseRejectionEvent(JSC::Structure*, JSDOMGlobalObject&, Ref<TestPromiseRejectionEvent>&&);

    DECLARE_DEFAULT_FINISH_CREATION;
};

JSC::JSValue toJS(JSC::JSGlobalObject*, JSDOMGlobalObject*, TestPromiseRejectionEvent&);
inline JSC::JSValue toJS(JSC::JSGlobalObject* lexicalGlobalObject, JSDOMGlobalObject* globalObject, TestPromiseRejectionEvent* impl) { return impl ? toJS(lexicalGlobalObject, globalObject, *impl) : JSC::jsNull(); }
JSC::JSValue toJSNewlyCreated(JSC::JSGlobalObject*, JSDOMGlobalObject*, Ref<TestPromiseRejectionEvent>&&);
inline JSC::JSValue toJSNewlyCreated(JSC::JSGlobalObject* lexicalGlobalObject, JSDOMGlobalObject* globalObject, RefPtr<TestPromiseRejectionEvent>&& impl) { return impl ? toJSNewlyCreated(lexicalGlobalObject, globalObject, impl.releaseNonNull()) : JSC::jsNull(); }

template<> struct JSDOMWrapperConverterTraits<TestPromiseRejectionEvent> {
    using WrapperClass = JSTestPromiseRejectionEvent;
    using ToWrappedReturnType = TestPromiseRejectionEvent*;
};
template<> TestPromiseRejectionEvent::Init convertDictionary<TestPromiseRejectionEvent::Init>(JSC::JSGlobalObject&, JSC::JSValue);


} // namespace WebCore

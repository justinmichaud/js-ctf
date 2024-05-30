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

#include "config.h"
#include "JSTestEventConstructor.h"

#include "ActiveDOMObject.h"
#include "ExtendedDOMClientIsoSubspaces.h"
#include "ExtendedDOMIsoSubspaces.h"
#include "JSDOMAttribute.h"
#include "JSDOMBinding.h"
#include "JSDOMConstructor.h"
#include "JSDOMConvertBoolean.h"
#include "JSDOMConvertInterface.h"
#include "JSDOMConvertStrings.h"
#include "JSDOMExceptionHandling.h"
#include "JSDOMGlobalObjectInlines.h"
#include "JSDOMWrapperCache.h"
#include "ScriptExecutionContext.h"
#include "WebCoreJSClientData.h"
#include <JavaScriptCore/HeapAnalyzer.h>
#include <JavaScriptCore/JSCInlines.h>
#include <JavaScriptCore/JSDestructibleObjectHeapCellType.h>
#include <JavaScriptCore/SlotVisitorMacros.h>
#include <JavaScriptCore/SubspaceInlines.h>
#include <wtf/GetPtr.h>
#include <wtf/PointerPreparations.h>
#include <wtf/URL.h>


namespace WebCore {
using namespace JSC;

template<> TestEventConstructor::Init convertDictionary<TestEventConstructor::Init>(JSGlobalObject& lexicalGlobalObject, JSValue value)
{
    auto& vm = JSC::getVM(&lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    bool isNullOrUndefined = value.isUndefinedOrNull();
    auto* object = isNullOrUndefined ? nullptr : value.getObject();
    if (UNLIKELY(!isNullOrUndefined && !object)) {
        throwTypeError(&lexicalGlobalObject, throwScope);
        return { };
    }
    TestEventConstructor::Init result;
    JSValue bubblesValue;
    if (isNullOrUndefined)
        bubblesValue = jsUndefined();
    else {
        bubblesValue = object->get(&lexicalGlobalObject, Identifier::fromString(vm, "bubbles"_s));
        RETURN_IF_EXCEPTION(throwScope, { });
    }
    if (!bubblesValue.isUndefined()) {
        result.bubbles = convert<IDLBoolean>(lexicalGlobalObject, bubblesValue);
        RETURN_IF_EXCEPTION(throwScope, { });
    } else
        result.bubbles = false;
    JSValue cancelableValue;
    if (isNullOrUndefined)
        cancelableValue = jsUndefined();
    else {
        cancelableValue = object->get(&lexicalGlobalObject, Identifier::fromString(vm, "cancelable"_s));
        RETURN_IF_EXCEPTION(throwScope, { });
    }
    if (!cancelableValue.isUndefined()) {
        result.cancelable = convert<IDLBoolean>(lexicalGlobalObject, cancelableValue);
        RETURN_IF_EXCEPTION(throwScope, { });
    } else
        result.cancelable = false;
    JSValue composedValue;
    if (isNullOrUndefined)
        composedValue = jsUndefined();
    else {
        composedValue = object->get(&lexicalGlobalObject, Identifier::fromString(vm, "composed"_s));
        RETURN_IF_EXCEPTION(throwScope, { });
    }
    if (!composedValue.isUndefined()) {
        result.composed = convert<IDLBoolean>(lexicalGlobalObject, composedValue);
        RETURN_IF_EXCEPTION(throwScope, { });
    } else
        result.composed = false;
    JSValue attr2Value;
    if (isNullOrUndefined)
        attr2Value = jsUndefined();
    else {
        attr2Value = object->get(&lexicalGlobalObject, Identifier::fromString(vm, "attr2"_s));
        RETURN_IF_EXCEPTION(throwScope, { });
    }
    if (!attr2Value.isUndefined()) {
        result.attr2 = convert<IDLDOMString>(lexicalGlobalObject, attr2Value);
        RETURN_IF_EXCEPTION(throwScope, { });
    } else
        result.attr2 = emptyString();
#if ENABLE(SPECIAL_EVENT)
    JSValue attr3Value;
    if (isNullOrUndefined)
        attr3Value = jsUndefined();
    else {
        attr3Value = object->get(&lexicalGlobalObject, Identifier::fromString(vm, "attr3"_s));
        RETURN_IF_EXCEPTION(throwScope, { });
    }
    if (!attr3Value.isUndefined()) {
        result.attr3 = convert<IDLDOMString>(lexicalGlobalObject, attr3Value);
        RETURN_IF_EXCEPTION(throwScope, { });
    } else
        result.attr3 = emptyString();
#endif
    return result;
}

// Attributes

static JSC_DECLARE_CUSTOM_GETTER(jsTestEventConstructorConstructor);
static JSC_DECLARE_CUSTOM_GETTER(jsTestEventConstructor_attr1);
static JSC_DECLARE_CUSTOM_GETTER(jsTestEventConstructor_attr2);
#if ENABLE(SPECIAL_EVENT)
static JSC_DECLARE_CUSTOM_GETTER(jsTestEventConstructor_attr3);
#endif

class JSTestEventConstructorPrototype final : public JSC::JSNonFinalObject {
public:
    using Base = JSC::JSNonFinalObject;
    static JSTestEventConstructorPrototype* create(JSC::VM& vm, JSDOMGlobalObject* globalObject, JSC::Structure* structure)
    {
        JSTestEventConstructorPrototype* ptr = new (NotNull, JSC::allocateCell<JSTestEventConstructorPrototype>(vm)) JSTestEventConstructorPrototype(vm, globalObject, structure);
        ptr->finishCreation(vm);
        return ptr;
    }

    DECLARE_INFO;
    template<typename CellType, JSC::SubspaceAccess>
    static JSC::GCClient::IsoSubspace* subspaceFor(JSC::VM& vm)
    {
        STATIC_ASSERT_ISO_SUBSPACE_SHARABLE(JSTestEventConstructorPrototype, Base);
        return &vm.plainObjectSpace();
    }
    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
    }

private:
    JSTestEventConstructorPrototype(JSC::VM& vm, JSC::JSGlobalObject*, JSC::Structure* structure)
        : JSC::JSNonFinalObject(vm, structure)
    {
    }

    void finishCreation(JSC::VM&);
};
STATIC_ASSERT_ISO_SUBSPACE_SHARABLE(JSTestEventConstructorPrototype, JSTestEventConstructorPrototype::Base);

using JSTestEventConstructorDOMConstructor = JSDOMConstructor<JSTestEventConstructor>;

template<> EncodedJSValue JSC_HOST_CALL_ATTRIBUTES JSTestEventConstructorDOMConstructor::construct(JSGlobalObject* lexicalGlobalObject, CallFrame* callFrame)
{
    auto& vm = lexicalGlobalObject->vm();
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* castedThis = jsCast<JSTestEventConstructorDOMConstructor*>(callFrame->jsCallee());
    ASSERT(castedThis);
    if (UNLIKELY(callFrame->argumentCount() < 1))
        return throwVMError(lexicalGlobalObject, throwScope, createNotEnoughArgumentsError(lexicalGlobalObject));
    EnsureStillAliveScope argument0 = callFrame->uncheckedArgument(0);
    auto type = convert<IDLDOMString>(*lexicalGlobalObject, argument0.value());
    RETURN_IF_EXCEPTION(throwScope, encodedJSValue());
    EnsureStillAliveScope argument1 = callFrame->argument(1);
    auto eventInitDict = convert<IDLDictionary<TestEventConstructor::Init>>(*lexicalGlobalObject, argument1.value());
    RETURN_IF_EXCEPTION(throwScope, encodedJSValue());
    auto object = TestEventConstructor::create(WTFMove(type), WTFMove(eventInitDict));
    if constexpr (IsExceptionOr<decltype(object)>)
        RETURN_IF_EXCEPTION(throwScope, { });
    static_assert(TypeOrExceptionOrUnderlyingType<decltype(object)>::isRef);
    auto jsValue = toJSNewlyCreated<IDLInterface<TestEventConstructor>>(*lexicalGlobalObject, *castedThis->globalObject(), throwScope, WTFMove(object));
    if constexpr (IsExceptionOr<decltype(object)>)
        RETURN_IF_EXCEPTION(throwScope, { });
    setSubclassStructureIfNeeded<TestEventConstructor>(lexicalGlobalObject, callFrame, asObject(jsValue));
    RETURN_IF_EXCEPTION(throwScope, { });
    return JSValue::encode(jsValue);
}
JSC_ANNOTATE_HOST_FUNCTION(JSTestEventConstructorDOMConstructorConstruct, JSTestEventConstructorDOMConstructor::construct);

template<> const ClassInfo JSTestEventConstructorDOMConstructor::s_info = { "TestEventConstructor"_s, &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestEventConstructorDOMConstructor) };

template<> JSValue JSTestEventConstructorDOMConstructor::prototypeForStructure(JSC::VM& vm, const JSDOMGlobalObject& globalObject)
{
    return JSEvent::getConstructor(vm, &globalObject);
}

template<> void JSTestEventConstructorDOMConstructor::initializeProperties(VM& vm, JSDOMGlobalObject& globalObject)
{
    putDirect(vm, vm.propertyNames->length, jsNumber(1), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    JSString* nameString = jsNontrivialString(vm, "TestEventConstructor"_s);
    m_originalName.set(vm, this, nameString);
    putDirect(vm, vm.propertyNames->name, nameString, JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    putDirect(vm, vm.propertyNames->prototype, JSTestEventConstructor::prototype(vm, globalObject), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum | JSC::PropertyAttribute::DontDelete);
}

/* Hash table for prototype */

static const HashTableValue JSTestEventConstructorPrototypeTableValues[] =
{
    { "constructor"_s, static_cast<unsigned>(PropertyAttribute::DontEnum), NoIntrinsic, { HashTableValue::GetterSetterType, jsTestEventConstructorConstructor, 0 } },
    { "attr1"_s, JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::CustomAccessor | JSC::PropertyAttribute::DOMAttribute, NoIntrinsic, { HashTableValue::GetterSetterType, jsTestEventConstructor_attr1, 0 } },
    { "attr2"_s, JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::CustomAccessor | JSC::PropertyAttribute::DOMAttribute, NoIntrinsic, { HashTableValue::GetterSetterType, jsTestEventConstructor_attr2, 0 } },
#if ENABLE(SPECIAL_EVENT)
    { "attr3"_s, JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::CustomAccessor | JSC::PropertyAttribute::DOMAttribute, NoIntrinsic, { HashTableValue::GetterSetterType, jsTestEventConstructor_attr3, 0 } },
#else
    { { }, 0, NoIntrinsic, { HashTableValue::End } },
#endif
};

const ClassInfo JSTestEventConstructorPrototype::s_info = { "TestEventConstructor"_s, &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestEventConstructorPrototype) };

void JSTestEventConstructorPrototype::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    reifyStaticProperties(vm, JSTestEventConstructor::info(), JSTestEventConstructorPrototypeTableValues, *this);
    JSC_TO_STRING_TAG_WITHOUT_TRANSITION();
}

const ClassInfo JSTestEventConstructor::s_info = { "TestEventConstructor"_s, &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestEventConstructor) };

JSTestEventConstructor::JSTestEventConstructor(Structure* structure, JSDOMGlobalObject& globalObject, Ref<TestEventConstructor>&& impl)
    : JSEvent(structure, globalObject, WTFMove(impl))
{
}

Ref<TestEventConstructor> JSTestEventConstructor::protectedWrapped() const
{
    return wrapped();
}

static_assert(!std::is_base_of<ActiveDOMObject, TestEventConstructor>::value, "Interface is not marked as [ActiveDOMObject] even though implementation class subclasses ActiveDOMObject.");

JSObject* JSTestEventConstructor::createPrototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    auto* structure = JSTestEventConstructorPrototype::createStructure(vm, &globalObject, JSEvent::prototype(vm, globalObject));
    structure->setMayBePrototype(true);
    return JSTestEventConstructorPrototype::create(vm, &globalObject, structure);
}

JSObject* JSTestEventConstructor::prototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return getDOMPrototype<JSTestEventConstructor>(vm, globalObject);
}

JSValue JSTestEventConstructor::getConstructor(VM& vm, const JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSTestEventConstructorDOMConstructor, DOMConstructorID::TestEventConstructor>(vm, *jsCast<const JSDOMGlobalObject*>(globalObject));
}

JSC_DEFINE_CUSTOM_GETTER(jsTestEventConstructorConstructor, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName))
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* prototype = jsDynamicCast<JSTestEventConstructorPrototype*>(JSValue::decode(thisValue));
    if (UNLIKELY(!prototype))
        return throwVMTypeError(lexicalGlobalObject, throwScope);
    return JSValue::encode(JSTestEventConstructor::getConstructor(vm, prototype->globalObject()));
}

static inline JSValue jsTestEventConstructor_attr1Getter(JSGlobalObject& lexicalGlobalObject, JSTestEventConstructor& thisObject)
{
    auto& vm = JSC::getVM(&lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto& impl = thisObject.wrapped();
    RELEASE_AND_RETURN(throwScope, (toJS<IDLDOMString>(lexicalGlobalObject, throwScope, impl.attr1())));
}

JSC_DEFINE_CUSTOM_GETTER(jsTestEventConstructor_attr1, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<JSTestEventConstructor>::get<jsTestEventConstructor_attr1Getter, CastedThisErrorBehavior::Assert>(*lexicalGlobalObject, thisValue, attributeName);
}

static inline JSValue jsTestEventConstructor_attr2Getter(JSGlobalObject& lexicalGlobalObject, JSTestEventConstructor& thisObject)
{
    auto& vm = JSC::getVM(&lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto& impl = thisObject.wrapped();
    RELEASE_AND_RETURN(throwScope, (toJS<IDLDOMString>(lexicalGlobalObject, throwScope, impl.attr2())));
}

JSC_DEFINE_CUSTOM_GETTER(jsTestEventConstructor_attr2, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<JSTestEventConstructor>::get<jsTestEventConstructor_attr2Getter, CastedThisErrorBehavior::Assert>(*lexicalGlobalObject, thisValue, attributeName);
}

#if ENABLE(SPECIAL_EVENT)
static inline JSValue jsTestEventConstructor_attr3Getter(JSGlobalObject& lexicalGlobalObject, JSTestEventConstructor& thisObject)
{
    auto& vm = JSC::getVM(&lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto& impl = thisObject.wrapped();
    RELEASE_AND_RETURN(throwScope, (toJS<IDLDOMString>(lexicalGlobalObject, throwScope, impl.attr3())));
}

JSC_DEFINE_CUSTOM_GETTER(jsTestEventConstructor_attr3, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<JSTestEventConstructor>::get<jsTestEventConstructor_attr3Getter, CastedThisErrorBehavior::Assert>(*lexicalGlobalObject, thisValue, attributeName);
}

#endif

JSC::GCClient::IsoSubspace* JSTestEventConstructor::subspaceForImpl(JSC::VM& vm)
{
    return WebCore::subspaceForImpl<JSTestEventConstructor, UseCustomHeapCellType::No>(vm,
        [] (auto& spaces) { return spaces.m_clientSubspaceForTestEventConstructor.get(); },
        [] (auto& spaces, auto&& space) { spaces.m_clientSubspaceForTestEventConstructor = std::forward<decltype(space)>(space); },
        [] (auto& spaces) { return spaces.m_subspaceForTestEventConstructor.get(); },
        [] (auto& spaces, auto&& space) { spaces.m_subspaceForTestEventConstructor = std::forward<decltype(space)>(space); }
    );
}

void JSTestEventConstructor::analyzeHeap(JSCell* cell, HeapAnalyzer& analyzer)
{
    auto* thisObject = jsCast<JSTestEventConstructor*>(cell);
    analyzer.setWrappedObjectForCell(cell, &thisObject->wrapped());
    if (thisObject->scriptExecutionContext())
        analyzer.setLabelForCell(cell, "url "_s + thisObject->scriptExecutionContext()->url().string());
    Base::analyzeHeap(cell, analyzer);
}

#if ENABLE(BINDING_INTEGRITY)
#if PLATFORM(WIN)
#pragma warning(disable: 4483)
extern "C" { extern void (*const __identifier("??_7TestEventConstructor@WebCore@@6B@")[])(); }
#else
extern "C" { extern void* _ZTVN7WebCore20TestEventConstructorE[]; }
#endif
template<typename T, typename = std::enable_if_t<std::is_same_v<T, TestEventConstructor>, void>> static inline void verifyVTable(TestEventConstructor* ptr) {
    if constexpr (std::is_polymorphic_v<T>) {
        const void* actualVTablePointer = getVTablePointer<T>(ptr);
#if PLATFORM(WIN)
        void* expectedVTablePointer = __identifier("??_7TestEventConstructor@WebCore@@6B@");
#else
        void* expectedVTablePointer = &_ZTVN7WebCore20TestEventConstructorE[2];
#endif

        // If you hit this assertion you either have a use after free bug, or
        // TestEventConstructor has subclasses. If TestEventConstructor has subclasses that get passed
        // to toJS() we currently require TestEventConstructor you to opt out of binding hardening
        // by adding the SkipVTableValidation attribute to the interface IDL definition
        RELEASE_ASSERT(actualVTablePointer == expectedVTablePointer);
    }
}
#endif
JSC::JSValue toJSNewlyCreated(JSC::JSGlobalObject*, JSDOMGlobalObject* globalObject, Ref<TestEventConstructor>&& impl)
{
#if ENABLE(BINDING_INTEGRITY)
    verifyVTable<TestEventConstructor>(impl.ptr());
#endif
    return createWrapper<TestEventConstructor>(globalObject, WTFMove(impl));
}

JSC::JSValue toJS(JSC::JSGlobalObject* lexicalGlobalObject, JSDOMGlobalObject* globalObject, TestEventConstructor& impl)
{
    return wrap(lexicalGlobalObject, globalObject, impl);
}


}

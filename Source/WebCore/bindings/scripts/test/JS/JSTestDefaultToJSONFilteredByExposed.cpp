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
#include "JSTestDefaultToJSONFilteredByExposed.h"

#include "ActiveDOMObject.h"
#include "ExtendedDOMClientIsoSubspaces.h"
#include "ExtendedDOMIsoSubspaces.h"
#include "JSDOMAttribute.h"
#include "JSDOMBinding.h"
#include "JSDOMConstructorNotConstructable.h"
#include "JSDOMConvertNumbers.h"
#include "JSDOMConvertStrings.h"
#include "JSDOMExceptionHandling.h"
#include "JSDOMGlobalObjectInlines.h"
#include "JSDOMOperation.h"
#include "JSDOMWindowBase.h"
#include "JSDOMWrapperCache.h"
#include "JSWorkerGlobalScopeBase.h"
#include "ScriptExecutionContext.h"
#include "WebCoreJSClientData.h"
#include <JavaScriptCore/FunctionPrototype.h>
#include <JavaScriptCore/HeapAnalyzer.h>
#include <JavaScriptCore/JSCInlines.h>
#include <JavaScriptCore/JSDestructibleObjectHeapCellType.h>
#include <JavaScriptCore/ObjectConstructor.h>
#include <JavaScriptCore/SlotVisitorMacros.h>
#include <JavaScriptCore/SubspaceInlines.h>
#include <wtf/GetPtr.h>
#include <wtf/PointerPreparations.h>
#include <wtf/URL.h>


namespace WebCore {
using namespace JSC;

// Functions

static JSC_DECLARE_HOST_FUNCTION(jsTestDefaultToJSONFilteredByExposedPrototypeFunction_toJSON);

// Attributes

static JSC_DECLARE_CUSTOM_GETTER(jsTestDefaultToJSONFilteredByExposedConstructor);
static JSC_DECLARE_CUSTOM_GETTER(jsTestDefaultToJSONFilteredByExposed_normalAttribute);
static JSC_DECLARE_CUSTOM_GETTER(jsTestDefaultToJSONFilteredByExposed_filteredByExposedWindowAttribute);
static JSC_DECLARE_CUSTOM_GETTER(jsTestDefaultToJSONFilteredByExposed_filteredByExposedWorkerAttribute);

class JSTestDefaultToJSONFilteredByExposedPrototype final : public JSC::JSNonFinalObject {
public:
    using Base = JSC::JSNonFinalObject;
    static JSTestDefaultToJSONFilteredByExposedPrototype* create(JSC::VM& vm, JSDOMGlobalObject* globalObject, JSC::Structure* structure)
    {
        JSTestDefaultToJSONFilteredByExposedPrototype* ptr = new (NotNull, JSC::allocateCell<JSTestDefaultToJSONFilteredByExposedPrototype>(vm)) JSTestDefaultToJSONFilteredByExposedPrototype(vm, globalObject, structure);
        ptr->finishCreation(vm);
        return ptr;
    }

    DECLARE_INFO;
    template<typename CellType, JSC::SubspaceAccess>
    static JSC::GCClient::IsoSubspace* subspaceFor(JSC::VM& vm)
    {
        STATIC_ASSERT_ISO_SUBSPACE_SHARABLE(JSTestDefaultToJSONFilteredByExposedPrototype, Base);
        return &vm.plainObjectSpace();
    }
    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
    }

private:
    JSTestDefaultToJSONFilteredByExposedPrototype(JSC::VM& vm, JSC::JSGlobalObject*, JSC::Structure* structure)
        : JSC::JSNonFinalObject(vm, structure)
    {
    }

    void finishCreation(JSC::VM&);
};
STATIC_ASSERT_ISO_SUBSPACE_SHARABLE(JSTestDefaultToJSONFilteredByExposedPrototype, JSTestDefaultToJSONFilteredByExposedPrototype::Base);

using JSTestDefaultToJSONFilteredByExposedDOMConstructor = JSDOMConstructorNotConstructable<JSTestDefaultToJSONFilteredByExposed>;

template<> const ClassInfo JSTestDefaultToJSONFilteredByExposedDOMConstructor::s_info = { "TestDefaultToJSONFilteredByExposed"_s, &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestDefaultToJSONFilteredByExposedDOMConstructor) };

template<> JSValue JSTestDefaultToJSONFilteredByExposedDOMConstructor::prototypeForStructure(JSC::VM& vm, const JSDOMGlobalObject& globalObject)
{
    UNUSED_PARAM(vm);
    return globalObject.functionPrototype();
}

template<> void JSTestDefaultToJSONFilteredByExposedDOMConstructor::initializeProperties(VM& vm, JSDOMGlobalObject& globalObject)
{
    putDirect(vm, vm.propertyNames->length, jsNumber(0), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    JSString* nameString = jsNontrivialString(vm, "TestDefaultToJSONFilteredByExposed"_s);
    m_originalName.set(vm, this, nameString);
    putDirect(vm, vm.propertyNames->name, nameString, JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    putDirect(vm, vm.propertyNames->prototype, JSTestDefaultToJSONFilteredByExposed::prototype(vm, globalObject), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum | JSC::PropertyAttribute::DontDelete);
}

/* Hash table for prototype */

static const HashTableValue JSTestDefaultToJSONFilteredByExposedPrototypeTableValues[] =
{
    { "constructor"_s, static_cast<unsigned>(PropertyAttribute::DontEnum), NoIntrinsic, { HashTableValue::GetterSetterType, jsTestDefaultToJSONFilteredByExposedConstructor, 0 } },
    { "normalAttribute"_s, JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::CustomAccessor | JSC::PropertyAttribute::DOMAttribute, NoIntrinsic, { HashTableValue::GetterSetterType, jsTestDefaultToJSONFilteredByExposed_normalAttribute, 0 } },
    { "filteredByExposedWindowAttribute"_s, JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::CustomAccessor | JSC::PropertyAttribute::DOMAttribute, NoIntrinsic, { HashTableValue::GetterSetterType, jsTestDefaultToJSONFilteredByExposed_filteredByExposedWindowAttribute, 0 } },
    { "filteredByExposedWorkerAttribute"_s, JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::CustomAccessor | JSC::PropertyAttribute::DOMAttribute, NoIntrinsic, { HashTableValue::GetterSetterType, jsTestDefaultToJSONFilteredByExposed_filteredByExposedWorkerAttribute, 0 } },
    { "toJSON"_s, static_cast<unsigned>(JSC::PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, jsTestDefaultToJSONFilteredByExposedPrototypeFunction_toJSON, 0 } },
};

const ClassInfo JSTestDefaultToJSONFilteredByExposedPrototype::s_info = { "TestDefaultToJSONFilteredByExposed"_s, &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestDefaultToJSONFilteredByExposedPrototype) };

void JSTestDefaultToJSONFilteredByExposedPrototype::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    reifyStaticProperties(vm, JSTestDefaultToJSONFilteredByExposed::info(), JSTestDefaultToJSONFilteredByExposedPrototypeTableValues, *this);
    bool hasDisabledRuntimeProperties = false;
    if (!(globalObject())->inherits<JSDOMWindowBase>()) {
        hasDisabledRuntimeProperties = true;
        auto propertyName = Identifier::fromString(vm, "filteredByExposedWindowAttribute"_s);
        VM::DeletePropertyModeScope scope(vm, VM::DeletePropertyMode::IgnoreConfigurable);
        DeletePropertySlot slot;
        JSObject::deleteProperty(this, globalObject(), propertyName, slot);
    }
    if (!(globalObject())->inherits<JSWorkerGlobalScopeBase>()) {
        hasDisabledRuntimeProperties = true;
        auto propertyName = Identifier::fromString(vm, "filteredByExposedWorkerAttribute"_s);
        VM::DeletePropertyModeScope scope(vm, VM::DeletePropertyMode::IgnoreConfigurable);
        DeletePropertySlot slot;
        JSObject::deleteProperty(this, globalObject(), propertyName, slot);
    }
    if (hasDisabledRuntimeProperties && structure()->isDictionary())
        flattenDictionaryObject(vm);
    JSC_TO_STRING_TAG_WITHOUT_TRANSITION();
}

const ClassInfo JSTestDefaultToJSONFilteredByExposed::s_info = { "TestDefaultToJSONFilteredByExposed"_s, &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestDefaultToJSONFilteredByExposed) };

JSTestDefaultToJSONFilteredByExposed::JSTestDefaultToJSONFilteredByExposed(Structure* structure, JSDOMGlobalObject& globalObject, Ref<TestDefaultToJSONFilteredByExposed>&& impl)
    : JSDOMWrapper<TestDefaultToJSONFilteredByExposed>(structure, globalObject, WTFMove(impl))
{
}

static_assert(!std::is_base_of<ActiveDOMObject, TestDefaultToJSONFilteredByExposed>::value, "Interface is not marked as [ActiveDOMObject] even though implementation class subclasses ActiveDOMObject.");

JSObject* JSTestDefaultToJSONFilteredByExposed::createPrototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    auto* structure = JSTestDefaultToJSONFilteredByExposedPrototype::createStructure(vm, &globalObject, globalObject.objectPrototype());
    structure->setMayBePrototype(true);
    return JSTestDefaultToJSONFilteredByExposedPrototype::create(vm, &globalObject, structure);
}

JSObject* JSTestDefaultToJSONFilteredByExposed::prototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return getDOMPrototype<JSTestDefaultToJSONFilteredByExposed>(vm, globalObject);
}

JSValue JSTestDefaultToJSONFilteredByExposed::getConstructor(VM& vm, const JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSTestDefaultToJSONFilteredByExposedDOMConstructor, DOMConstructorID::TestDefaultToJSONFilteredByExposed>(vm, *jsCast<const JSDOMGlobalObject*>(globalObject));
}

void JSTestDefaultToJSONFilteredByExposed::destroy(JSC::JSCell* cell)
{
    JSTestDefaultToJSONFilteredByExposed* thisObject = static_cast<JSTestDefaultToJSONFilteredByExposed*>(cell);
    thisObject->JSTestDefaultToJSONFilteredByExposed::~JSTestDefaultToJSONFilteredByExposed();
}

JSC_DEFINE_CUSTOM_GETTER(jsTestDefaultToJSONFilteredByExposedConstructor, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName))
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* prototype = jsDynamicCast<JSTestDefaultToJSONFilteredByExposedPrototype*>(JSValue::decode(thisValue));
    if (UNLIKELY(!prototype))
        return throwVMTypeError(lexicalGlobalObject, throwScope);
    return JSValue::encode(JSTestDefaultToJSONFilteredByExposed::getConstructor(vm, prototype->globalObject()));
}

static inline JSValue jsTestDefaultToJSONFilteredByExposed_normalAttributeGetter(JSGlobalObject& lexicalGlobalObject, JSTestDefaultToJSONFilteredByExposed& thisObject)
{
    auto& vm = JSC::getVM(&lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto& impl = thisObject.wrapped();
    RELEASE_AND_RETURN(throwScope, (toJS<IDLLong>(lexicalGlobalObject, throwScope, impl.normalAttribute())));
}

JSC_DEFINE_CUSTOM_GETTER(jsTestDefaultToJSONFilteredByExposed_normalAttribute, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<JSTestDefaultToJSONFilteredByExposed>::get<jsTestDefaultToJSONFilteredByExposed_normalAttributeGetter, CastedThisErrorBehavior::Assert>(*lexicalGlobalObject, thisValue, attributeName);
}

static inline JSValue jsTestDefaultToJSONFilteredByExposed_filteredByExposedWindowAttributeGetter(JSGlobalObject& lexicalGlobalObject, JSTestDefaultToJSONFilteredByExposed& thisObject)
{
    auto& vm = JSC::getVM(&lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto& impl = thisObject.wrapped();
    RELEASE_AND_RETURN(throwScope, (toJS<IDLDouble>(lexicalGlobalObject, throwScope, impl.filteredByExposedWindowAttribute())));
}

JSC_DEFINE_CUSTOM_GETTER(jsTestDefaultToJSONFilteredByExposed_filteredByExposedWindowAttribute, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<JSTestDefaultToJSONFilteredByExposed>::get<jsTestDefaultToJSONFilteredByExposed_filteredByExposedWindowAttributeGetter, CastedThisErrorBehavior::Assert>(*lexicalGlobalObject, thisValue, attributeName);
}

static inline JSValue jsTestDefaultToJSONFilteredByExposed_filteredByExposedWorkerAttributeGetter(JSGlobalObject& lexicalGlobalObject, JSTestDefaultToJSONFilteredByExposed& thisObject)
{
    auto& vm = JSC::getVM(&lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto& impl = thisObject.wrapped();
    RELEASE_AND_RETURN(throwScope, (toJS<IDLDOMString>(lexicalGlobalObject, throwScope, impl.filteredByExposedWorkerAttribute())));
}

JSC_DEFINE_CUSTOM_GETTER(jsTestDefaultToJSONFilteredByExposed_filteredByExposedWorkerAttribute, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<JSTestDefaultToJSONFilteredByExposed>::get<jsTestDefaultToJSONFilteredByExposed_filteredByExposedWorkerAttributeGetter, CastedThisErrorBehavior::Assert>(*lexicalGlobalObject, thisValue, attributeName);
}

static inline EncodedJSValue jsTestDefaultToJSONFilteredByExposedPrototypeFunction_toJSONBody(JSGlobalObject* lexicalGlobalObject, CallFrame*, JSTestDefaultToJSONFilteredByExposed* castedThis)
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    UNUSED_PARAM(throwScope);
    auto& impl = castedThis->wrapped();
    auto* result = constructEmptyObject(lexicalGlobalObject);
    auto normalAttributeValue = toJS<IDLLong>(*lexicalGlobalObject, throwScope, impl.normalAttribute());
    RETURN_IF_EXCEPTION(throwScope, { });
    result->putDirect(vm, Identifier::fromString(vm, "normalAttribute"_s), normalAttributeValue);
    if ((castedThis->globalObject())->inherits<JSDOMWindowBase>()) {
        auto filteredByExposedWindowAttributeValue = toJS<IDLDouble>(*lexicalGlobalObject, throwScope, impl.filteredByExposedWindowAttribute());
        RETURN_IF_EXCEPTION(throwScope, { });
        result->putDirect(vm, Identifier::fromString(vm, "filteredByExposedWindowAttribute"_s), filteredByExposedWindowAttributeValue);
    }
    if ((castedThis->globalObject())->inherits<JSWorkerGlobalScopeBase>()) {
        auto filteredByExposedWorkerAttributeValue = toJS<IDLDOMString>(*lexicalGlobalObject, throwScope, impl.filteredByExposedWorkerAttribute());
        RETURN_IF_EXCEPTION(throwScope, { });
        result->putDirect(vm, Identifier::fromString(vm, "filteredByExposedWorkerAttribute"_s), filteredByExposedWorkerAttributeValue);
    }
    return JSValue::encode(result);
}

JSC_DEFINE_HOST_FUNCTION(jsTestDefaultToJSONFilteredByExposedPrototypeFunction_toJSON, (JSGlobalObject* lexicalGlobalObject, CallFrame* callFrame))
{
    return IDLOperation<JSTestDefaultToJSONFilteredByExposed>::call<jsTestDefaultToJSONFilteredByExposedPrototypeFunction_toJSONBody>(*lexicalGlobalObject, *callFrame, "toJSON");
}

JSC::GCClient::IsoSubspace* JSTestDefaultToJSONFilteredByExposed::subspaceForImpl(JSC::VM& vm)
{
    return WebCore::subspaceForImpl<JSTestDefaultToJSONFilteredByExposed, UseCustomHeapCellType::No>(vm,
        [] (auto& spaces) { return spaces.m_clientSubspaceForTestDefaultToJSONFilteredByExposed.get(); },
        [] (auto& spaces, auto&& space) { spaces.m_clientSubspaceForTestDefaultToJSONFilteredByExposed = std::forward<decltype(space)>(space); },
        [] (auto& spaces) { return spaces.m_subspaceForTestDefaultToJSONFilteredByExposed.get(); },
        [] (auto& spaces, auto&& space) { spaces.m_subspaceForTestDefaultToJSONFilteredByExposed = std::forward<decltype(space)>(space); }
    );
}

void JSTestDefaultToJSONFilteredByExposed::analyzeHeap(JSCell* cell, HeapAnalyzer& analyzer)
{
    auto* thisObject = jsCast<JSTestDefaultToJSONFilteredByExposed*>(cell);
    analyzer.setWrappedObjectForCell(cell, &thisObject->wrapped());
    if (thisObject->scriptExecutionContext())
        analyzer.setLabelForCell(cell, "url "_s + thisObject->scriptExecutionContext()->url().string());
    Base::analyzeHeap(cell, analyzer);
}

bool JSTestDefaultToJSONFilteredByExposedOwner::isReachableFromOpaqueRoots(JSC::Handle<JSC::Unknown> handle, void*, AbstractSlotVisitor& visitor, ASCIILiteral* reason)
{
    UNUSED_PARAM(handle);
    UNUSED_PARAM(visitor);
    UNUSED_PARAM(reason);
    return false;
}

void JSTestDefaultToJSONFilteredByExposedOwner::finalize(JSC::Handle<JSC::Unknown> handle, void* context)
{
    auto* jsTestDefaultToJSONFilteredByExposed = static_cast<JSTestDefaultToJSONFilteredByExposed*>(handle.slot()->asCell());
    auto& world = *static_cast<DOMWrapperWorld*>(context);
    uncacheWrapper(world, jsTestDefaultToJSONFilteredByExposed->protectedWrapped().ptr(), jsTestDefaultToJSONFilteredByExposed);
}

#if ENABLE(BINDING_INTEGRITY)
#if PLATFORM(WIN)
#pragma warning(disable: 4483)
extern "C" { extern void (*const __identifier("??_7TestDefaultToJSONFilteredByExposed@WebCore@@6B@")[])(); }
#else
extern "C" { extern void* _ZTVN7WebCore34TestDefaultToJSONFilteredByExposedE[]; }
#endif
template<typename T, typename = std::enable_if_t<std::is_same_v<T, TestDefaultToJSONFilteredByExposed>, void>> static inline void verifyVTable(TestDefaultToJSONFilteredByExposed* ptr) {
    if constexpr (std::is_polymorphic_v<T>) {
        const void* actualVTablePointer = getVTablePointer<T>(ptr);
#if PLATFORM(WIN)
        void* expectedVTablePointer = __identifier("??_7TestDefaultToJSONFilteredByExposed@WebCore@@6B@");
#else
        void* expectedVTablePointer = &_ZTVN7WebCore34TestDefaultToJSONFilteredByExposedE[2];
#endif

        // If you hit this assertion you either have a use after free bug, or
        // TestDefaultToJSONFilteredByExposed has subclasses. If TestDefaultToJSONFilteredByExposed has subclasses that get passed
        // to toJS() we currently require TestDefaultToJSONFilteredByExposed you to opt out of binding hardening
        // by adding the SkipVTableValidation attribute to the interface IDL definition
        RELEASE_ASSERT(actualVTablePointer == expectedVTablePointer);
    }
}
#endif
JSC::JSValue toJSNewlyCreated(JSC::JSGlobalObject*, JSDOMGlobalObject* globalObject, Ref<TestDefaultToJSONFilteredByExposed>&& impl)
{
#if ENABLE(BINDING_INTEGRITY)
    verifyVTable<TestDefaultToJSONFilteredByExposed>(impl.ptr());
#endif
    return createWrapper<TestDefaultToJSONFilteredByExposed>(globalObject, WTFMove(impl));
}

JSC::JSValue toJS(JSC::JSGlobalObject* lexicalGlobalObject, JSDOMGlobalObject* globalObject, TestDefaultToJSONFilteredByExposed& impl)
{
    return wrap(lexicalGlobalObject, globalObject, impl);
}

TestDefaultToJSONFilteredByExposed* JSTestDefaultToJSONFilteredByExposed::toWrapped(JSC::VM&, JSC::JSValue value)
{
    if (auto* wrapper = jsDynamicCast<JSTestDefaultToJSONFilteredByExposed*>(value))
        return &wrapper->wrapped();
    return nullptr;
}

}

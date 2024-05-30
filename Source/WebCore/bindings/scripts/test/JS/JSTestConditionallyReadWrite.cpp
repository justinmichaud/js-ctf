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
#include "JSTestConditionallyReadWrite.h"

#include "ActiveDOMObject.h"
#include "DOMPromiseProxy.h"
#include "Document.h"
#include "ExtendedDOMClientIsoSubspaces.h"
#include "ExtendedDOMIsoSubspaces.h"
#include "JSDOMAttribute.h"
#include "JSDOMBinding.h"
#include "JSDOMConstructorNotConstructable.h"
#include "JSDOMConvertInterface.h"
#include "JSDOMConvertNumbers.h"
#include "JSDOMConvertPromise.h"
#include "JSDOMExceptionHandling.h"
#include "JSDOMGlobalObject.h"
#include "JSDOMGlobalObjectInlines.h"
#include "JSDOMWrapperCache.h"
#include "JSNode.h"
#include "ScriptExecutionContext.h"
#include "WebCoreJSClientData.h"
#include <JavaScriptCore/FunctionPrototype.h>
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

// Attributes

static JSC_DECLARE_CUSTOM_GETTER(jsTestConditionallyReadWriteConstructor);
static JSC_DECLARE_CUSTOM_GETTER(jsTestConditionallyReadWrite_conditionallyReadWriteAttribute);
#if ENABLE(CONDITION)
static JSC_DECLARE_CUSTOM_SETTER(setJSTestConditionallyReadWrite_conditionallyReadWriteAttribute);
#endif
#if ENABLE(CONDITION2)
static JSC_DECLARE_CUSTOM_GETTER(jsTestConditionallyReadWrite_conditionalAndConditionallyReadWriteAttribute);
#if ENABLE(CONDITION)
static JSC_DECLARE_CUSTOM_SETTER(setJSTestConditionallyReadWrite_conditionalAndConditionallyReadWriteAttribute);
#endif
#endif
static JSC_DECLARE_CUSTOM_GETTER(jsTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttribute);
static JSC_DECLARE_CUSTOM_SETTER(setJSTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttribute);
static JSC_DECLARE_CUSTOM_GETTER(jsTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttributeUnforgeable);
static JSC_DECLARE_CUSTOM_SETTER(setJSTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttributeUnforgeable);
static JSC_DECLARE_CUSTOM_GETTER(jsTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttributeUnforgeablePrivate);
static JSC_DECLARE_CUSTOM_SETTER(setJSTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttributeUnforgeablePrivate);
static JSC_DECLARE_CUSTOM_GETTER(jsTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttributePromise);
static JSC_DECLARE_CUSTOM_SETTER(setJSTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttributePromise);

class JSTestConditionallyReadWritePrototype final : public JSC::JSNonFinalObject {
public:
    using Base = JSC::JSNonFinalObject;
    static JSTestConditionallyReadWritePrototype* create(JSC::VM& vm, JSDOMGlobalObject* globalObject, JSC::Structure* structure)
    {
        JSTestConditionallyReadWritePrototype* ptr = new (NotNull, JSC::allocateCell<JSTestConditionallyReadWritePrototype>(vm)) JSTestConditionallyReadWritePrototype(vm, globalObject, structure);
        ptr->finishCreation(vm);
        return ptr;
    }

    DECLARE_INFO;
    template<typename CellType, JSC::SubspaceAccess>
    static JSC::GCClient::IsoSubspace* subspaceFor(JSC::VM& vm)
    {
        STATIC_ASSERT_ISO_SUBSPACE_SHARABLE(JSTestConditionallyReadWritePrototype, Base);
        return &vm.plainObjectSpace();
    }
    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
    }

private:
    JSTestConditionallyReadWritePrototype(JSC::VM& vm, JSC::JSGlobalObject*, JSC::Structure* structure)
        : JSC::JSNonFinalObject(vm, structure)
    {
    }

    void finishCreation(JSC::VM&);
};
STATIC_ASSERT_ISO_SUBSPACE_SHARABLE(JSTestConditionallyReadWritePrototype, JSTestConditionallyReadWritePrototype::Base);

using JSTestConditionallyReadWriteDOMConstructor = JSDOMConstructorNotConstructable<JSTestConditionallyReadWrite>;

/* Hash table */

static const struct CompactHashIndex JSTestConditionallyReadWriteTableIndex[4] = {
    { 0, -1 },
    { -1, -1 },
    { -1, -1 },
    { -1, -1 },
};


static const HashTableValue JSTestConditionallyReadWriteTableValues[] =
{
    { "enabledConditionallyReadWriteBySettingAttributeUnforgeable"_s, JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::CustomAccessor | JSC::PropertyAttribute::DOMAttribute, NoIntrinsic, { HashTableValue::GetterSetterType, jsTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttributeUnforgeable, setJSTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttributeUnforgeable } },
};

static const HashTable JSTestConditionallyReadWriteTable = { 1, 3, static_cast<uint8_t>(JSC::PropertyAttribute::CustomAccessor | JSC::PropertyAttribute::DOMAttribute | JSC::PropertyAttribute::DontDelete), JSTestConditionallyReadWrite::info(), JSTestConditionallyReadWriteTableValues, JSTestConditionallyReadWriteTableIndex };
template<> const ClassInfo JSTestConditionallyReadWriteDOMConstructor::s_info = { "TestConditionallyReadWrite"_s, &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestConditionallyReadWriteDOMConstructor) };

template<> JSValue JSTestConditionallyReadWriteDOMConstructor::prototypeForStructure(JSC::VM& vm, const JSDOMGlobalObject& globalObject)
{
    UNUSED_PARAM(vm);
    return globalObject.functionPrototype();
}

template<> void JSTestConditionallyReadWriteDOMConstructor::initializeProperties(VM& vm, JSDOMGlobalObject& globalObject)
{
    putDirect(vm, vm.propertyNames->length, jsNumber(0), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    JSString* nameString = jsNontrivialString(vm, "TestConditionallyReadWrite"_s);
    m_originalName.set(vm, this, nameString);
    putDirect(vm, vm.propertyNames->name, nameString, JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    putDirect(vm, vm.propertyNames->prototype, JSTestConditionallyReadWrite::prototype(vm, globalObject), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum | JSC::PropertyAttribute::DontDelete);
}

/* Hash table for prototype */

static const HashTableValue JSTestConditionallyReadWritePrototypeTableValues[] =
{
    { "constructor"_s, static_cast<unsigned>(PropertyAttribute::DontEnum), NoIntrinsic, { HashTableValue::GetterSetterType, jsTestConditionallyReadWriteConstructor, 0 } },
#if ENABLE(CONDITION)
    { "conditionallyReadWriteAttribute"_s, JSC::PropertyAttribute::CustomAccessor | JSC::PropertyAttribute::DOMAttribute, NoIntrinsic, { HashTableValue::GetterSetterType, jsTestConditionallyReadWrite_conditionallyReadWriteAttribute, setJSTestConditionallyReadWrite_conditionallyReadWriteAttribute } },
#else
    { "conditionallyReadWriteAttribute"_s, JSC::PropertyAttribute::CustomAccessor | JSC::PropertyAttribute::DOMAttribute | PropertyAttribute::ReadOnly, NoIntrinsic, { HashTableValue::GetterSetterType, jsTestConditionallyReadWrite_conditionallyReadWriteAttribute, 0 } },
#endif
#if ENABLE(CONDITION2)
#if ENABLE(CONDITION)
    { "conditionalAndConditionallyReadWriteAttribute"_s, JSC::PropertyAttribute::CustomAccessor | JSC::PropertyAttribute::DOMAttribute, NoIntrinsic, { HashTableValue::GetterSetterType, jsTestConditionallyReadWrite_conditionalAndConditionallyReadWriteAttribute, setJSTestConditionallyReadWrite_conditionalAndConditionallyReadWriteAttribute } },
#else
    { "conditionalAndConditionallyReadWriteAttribute"_s, JSC::PropertyAttribute::CustomAccessor | JSC::PropertyAttribute::DOMAttribute | PropertyAttribute::ReadOnly, NoIntrinsic, { HashTableValue::GetterSetterType, jsTestConditionallyReadWrite_conditionalAndConditionallyReadWriteAttribute, 0 } },
#endif
#else
    { { }, 0, NoIntrinsic, { HashTableValue::End } },
#endif
    { "enabledConditionallyReadWriteBySettingAttribute"_s, JSC::PropertyAttribute::CustomAccessor | JSC::PropertyAttribute::DOMAttribute, NoIntrinsic, { HashTableValue::GetterSetterType, jsTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttribute, setJSTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttribute } },
    { "enabledConditionallyReadWriteBySettingAttributePromise"_s, static_cast<unsigned>(JSC::PropertyAttribute::CustomAccessor), NoIntrinsic, { HashTableValue::GetterSetterType, jsTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttributePromise, setJSTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttributePromise } },
};

const ClassInfo JSTestConditionallyReadWritePrototype::s_info = { "TestConditionallyReadWrite"_s, &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestConditionallyReadWritePrototype) };

void JSTestConditionallyReadWritePrototype::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    reifyStaticProperties(vm, JSTestConditionallyReadWrite::info(), JSTestConditionallyReadWritePrototypeTableValues, *this);
    bool hasDisabledRuntimeProperties = false;
    if (!downcast<Document>(jsCast<JSDOMGlobalObject*>(globalObject())->scriptExecutionContext())->settingsValues().testFeatureEnabled) {
        hasDisabledRuntimeProperties = true;
        auto propertyName = Identifier::fromString(vm, "enabledConditionallyReadWriteBySettingAttribute"_s);
        VM::DeletePropertyModeScope scope(vm, VM::DeletePropertyMode::IgnoreConfigurable);
        DeletePropertySlot slot;
        JSObject::deleteProperty(this, globalObject(), propertyName, slot);
    }
    if (!downcast<Document>(jsCast<JSDOMGlobalObject*>(globalObject())->scriptExecutionContext())->settingsValues().testFeatureEnabled) {
        hasDisabledRuntimeProperties = true;
        auto propertyName = Identifier::fromString(vm, "enabledConditionallyReadWriteBySettingAttributePromise"_s);
        VM::DeletePropertyModeScope scope(vm, VM::DeletePropertyMode::IgnoreConfigurable);
        DeletePropertySlot slot;
        JSObject::deleteProperty(this, globalObject(), propertyName, slot);
    }
    // Adding back attribute, but as readonly, after removing the read-write variant above. 
    if (!downcast<Document>(jsCast<JSDOMGlobalObject*>(globalObject())->scriptExecutionContext())->settingsValues().testFeatureEnabled)
        putDirectCustomAccessor(vm, builtinNames(vm).enabledConditionallyReadWriteBySettingAttributePublicName(), JSC::DOMAttributeGetterSetter::create(vm, jsTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttribute, nullptr, JSC::DOMAttributeAnnotation { JSTestConditionallyReadWrite::info(), nullptr }), attributesForStructure(JSC::PropertyAttribute::CustomAccessor | JSC::PropertyAttribute::DOMAttribute));
    // Adding back attribute, but as readonly, after removing the read-write variant above. 
    if (!downcast<Document>(jsCast<JSDOMGlobalObject*>(globalObject())->scriptExecutionContext())->settingsValues().testFeatureEnabled)
        putDirectCustomAccessor(vm, builtinNames(vm).enabledConditionallyReadWriteBySettingAttributePromisePublicName(), CustomGetterSetter::create(vm, jsTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttributePromise, nullptr), attributesForStructure(static_cast<unsigned>(JSC::PropertyAttribute::CustomAccessor)));
    if (hasDisabledRuntimeProperties && structure()->isDictionary())
        flattenDictionaryObject(vm);
    JSC_TO_STRING_TAG_WITHOUT_TRANSITION();
}

const ClassInfo JSTestConditionallyReadWrite::s_info = { "TestConditionallyReadWrite"_s, &Base::s_info, &JSTestConditionallyReadWriteTable, nullptr, CREATE_METHOD_TABLE(JSTestConditionallyReadWrite) };

JSTestConditionallyReadWrite::JSTestConditionallyReadWrite(Structure* structure, JSDOMGlobalObject& globalObject, Ref<TestConditionallyReadWrite>&& impl)
    : JSDOMWrapper<TestConditionallyReadWrite>(structure, globalObject, WTFMove(impl))
{
}

static_assert(!std::is_base_of<ActiveDOMObject, TestConditionallyReadWrite>::value, "Interface is not marked as [ActiveDOMObject] even though implementation class subclasses ActiveDOMObject.");

void JSTestConditionallyReadWrite::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    ASSERT(inherits(info()));

    putDirectCustomAccessor(vm, builtinNames(vm).enabledConditionallyReadWriteBySettingAttributeUnforgeablePrivatePrivateName(), CustomGetterSetter::create(vm, jsTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttributeUnforgeablePrivate, nullptr), attributesForStructure(JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly));
}

JSObject* JSTestConditionallyReadWrite::createPrototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    auto* structure = JSTestConditionallyReadWritePrototype::createStructure(vm, &globalObject, globalObject.objectPrototype());
    structure->setMayBePrototype(true);
    return JSTestConditionallyReadWritePrototype::create(vm, &globalObject, structure);
}

JSObject* JSTestConditionallyReadWrite::prototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return getDOMPrototype<JSTestConditionallyReadWrite>(vm, globalObject);
}

JSValue JSTestConditionallyReadWrite::getConstructor(VM& vm, const JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSTestConditionallyReadWriteDOMConstructor, DOMConstructorID::TestConditionallyReadWrite>(vm, *jsCast<const JSDOMGlobalObject*>(globalObject));
}

void JSTestConditionallyReadWrite::destroy(JSC::JSCell* cell)
{
    JSTestConditionallyReadWrite* thisObject = static_cast<JSTestConditionallyReadWrite*>(cell);
    thisObject->JSTestConditionallyReadWrite::~JSTestConditionallyReadWrite();
}

JSC_DEFINE_CUSTOM_GETTER(jsTestConditionallyReadWriteConstructor, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName))
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* prototype = jsDynamicCast<JSTestConditionallyReadWritePrototype*>(JSValue::decode(thisValue));
    if (UNLIKELY(!prototype))
        return throwVMTypeError(lexicalGlobalObject, throwScope);
    return JSValue::encode(JSTestConditionallyReadWrite::getConstructor(vm, prototype->globalObject()));
}

static inline JSValue jsTestConditionallyReadWrite_conditionallyReadWriteAttributeGetter(JSGlobalObject& lexicalGlobalObject, JSTestConditionallyReadWrite& thisObject)
{
    auto& vm = JSC::getVM(&lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto& impl = thisObject.wrapped();
    RELEASE_AND_RETURN(throwScope, (toJS<IDLInterface<Node>>(lexicalGlobalObject, *thisObject.globalObject(), throwScope, impl.conditionallyReadWriteAttribute())));
}

JSC_DEFINE_CUSTOM_GETTER(jsTestConditionallyReadWrite_conditionallyReadWriteAttribute, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<JSTestConditionallyReadWrite>::get<jsTestConditionallyReadWrite_conditionallyReadWriteAttributeGetter, CastedThisErrorBehavior::Assert>(*lexicalGlobalObject, thisValue, attributeName);
}

#if ENABLE(CONDITION)
static inline bool setJSTestConditionallyReadWrite_conditionallyReadWriteAttributeSetter(JSGlobalObject& lexicalGlobalObject, JSTestConditionallyReadWrite& thisObject, JSValue value)
{
    auto& vm = JSC::getVM(&lexicalGlobalObject);
    UNUSED_PARAM(vm);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto& impl = thisObject.wrapped();
    RefPtr nativeValue = convert<IDLInterface<Node>>(lexicalGlobalObject, value, [](JSC::JSGlobalObject& lexicalGlobalObject, JSC::ThrowScope& scope) { throwAttributeTypeError(lexicalGlobalObject, scope, "TestConditionallyReadWrite"_s, "conditionallyReadWriteAttribute"_s, "Node"_s); });
    RETURN_IF_EXCEPTION(throwScope, false);
    invokeFunctorPropagatingExceptionIfNecessary(lexicalGlobalObject, throwScope, [&] {
        return impl.setConditionallyReadWriteAttribute(*nativeValue);
    });
    return true;
}

JSC_DEFINE_CUSTOM_SETTER(setJSTestConditionallyReadWrite_conditionallyReadWriteAttribute, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, EncodedJSValue encodedValue, PropertyName attributeName))
{
    return IDLAttribute<JSTestConditionallyReadWrite>::set<setJSTestConditionallyReadWrite_conditionallyReadWriteAttributeSetter>(*lexicalGlobalObject, thisValue, encodedValue, attributeName);
}

#endif

#if ENABLE(CONDITION2)
static inline JSValue jsTestConditionallyReadWrite_conditionalAndConditionallyReadWriteAttributeGetter(JSGlobalObject& lexicalGlobalObject, JSTestConditionallyReadWrite& thisObject)
{
    auto& vm = JSC::getVM(&lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto& impl = thisObject.wrapped();
    RELEASE_AND_RETURN(throwScope, (toJS<IDLInterface<Node>>(lexicalGlobalObject, *thisObject.globalObject(), throwScope, impl.conditionalAndConditionallyReadWriteAttribute())));
}

JSC_DEFINE_CUSTOM_GETTER(jsTestConditionallyReadWrite_conditionalAndConditionallyReadWriteAttribute, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<JSTestConditionallyReadWrite>::get<jsTestConditionallyReadWrite_conditionalAndConditionallyReadWriteAttributeGetter, CastedThisErrorBehavior::Assert>(*lexicalGlobalObject, thisValue, attributeName);
}

#endif

#if ENABLE(CONDITION2)
#if ENABLE(CONDITION)
static inline bool setJSTestConditionallyReadWrite_conditionalAndConditionallyReadWriteAttributeSetter(JSGlobalObject& lexicalGlobalObject, JSTestConditionallyReadWrite& thisObject, JSValue value)
{
    auto& vm = JSC::getVM(&lexicalGlobalObject);
    UNUSED_PARAM(vm);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto& impl = thisObject.wrapped();
    RefPtr nativeValue = convert<IDLInterface<Node>>(lexicalGlobalObject, value, [](JSC::JSGlobalObject& lexicalGlobalObject, JSC::ThrowScope& scope) { throwAttributeTypeError(lexicalGlobalObject, scope, "TestConditionallyReadWrite"_s, "conditionalAndConditionallyReadWriteAttribute"_s, "Node"_s); });
    RETURN_IF_EXCEPTION(throwScope, false);
    invokeFunctorPropagatingExceptionIfNecessary(lexicalGlobalObject, throwScope, [&] {
        return impl.setConditionalAndConditionallyReadWriteAttribute(*nativeValue);
    });
    return true;
}

JSC_DEFINE_CUSTOM_SETTER(setJSTestConditionallyReadWrite_conditionalAndConditionallyReadWriteAttribute, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, EncodedJSValue encodedValue, PropertyName attributeName))
{
    return IDLAttribute<JSTestConditionallyReadWrite>::set<setJSTestConditionallyReadWrite_conditionalAndConditionallyReadWriteAttributeSetter>(*lexicalGlobalObject, thisValue, encodedValue, attributeName);
}

#endif

#endif

static inline JSValue jsTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttributeGetter(JSGlobalObject& lexicalGlobalObject, JSTestConditionallyReadWrite& thisObject)
{
    auto& vm = JSC::getVM(&lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto& impl = thisObject.wrapped();
    RELEASE_AND_RETURN(throwScope, (toJS<IDLInterface<Node>>(lexicalGlobalObject, *thisObject.globalObject(), throwScope, impl.enabledConditionallyReadWriteBySettingAttribute())));
}

JSC_DEFINE_CUSTOM_GETTER(jsTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttribute, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<JSTestConditionallyReadWrite>::get<jsTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttributeGetter, CastedThisErrorBehavior::Assert>(*lexicalGlobalObject, thisValue, attributeName);
}

static inline bool setJSTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttributeSetter(JSGlobalObject& lexicalGlobalObject, JSTestConditionallyReadWrite& thisObject, JSValue value)
{
    auto& vm = JSC::getVM(&lexicalGlobalObject);
    UNUSED_PARAM(vm);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto& impl = thisObject.wrapped();
    RefPtr nativeValue = convert<IDLInterface<Node>>(lexicalGlobalObject, value, [](JSC::JSGlobalObject& lexicalGlobalObject, JSC::ThrowScope& scope) { throwAttributeTypeError(lexicalGlobalObject, scope, "TestConditionallyReadWrite"_s, "enabledConditionallyReadWriteBySettingAttribute"_s, "Node"_s); });
    RETURN_IF_EXCEPTION(throwScope, false);
    invokeFunctorPropagatingExceptionIfNecessary(lexicalGlobalObject, throwScope, [&] {
        return impl.setEnabledConditionallyReadWriteBySettingAttribute(*nativeValue);
    });
    return true;
}

JSC_DEFINE_CUSTOM_SETTER(setJSTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttribute, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, EncodedJSValue encodedValue, PropertyName attributeName))
{
    return IDLAttribute<JSTestConditionallyReadWrite>::set<setJSTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttributeSetter>(*lexicalGlobalObject, thisValue, encodedValue, attributeName);
}

static inline JSValue jsTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttributeUnforgeableGetter(JSGlobalObject& lexicalGlobalObject, JSTestConditionallyReadWrite& thisObject)
{
    auto& vm = JSC::getVM(&lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto& impl = thisObject.wrapped();
    RELEASE_AND_RETURN(throwScope, (toJS<IDLInterface<Node>>(lexicalGlobalObject, *thisObject.globalObject(), throwScope, impl.enabledConditionallyReadWriteBySettingAttributeUnforgeable())));
}

JSC_DEFINE_CUSTOM_GETTER(jsTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttributeUnforgeable, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<JSTestConditionallyReadWrite>::get<jsTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttributeUnforgeableGetter, CastedThisErrorBehavior::Assert>(*lexicalGlobalObject, thisValue, attributeName);
}

static inline bool setJSTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttributeUnforgeableSetter(JSGlobalObject& lexicalGlobalObject, JSTestConditionallyReadWrite& thisObject, JSValue value)
{
    auto& vm = JSC::getVM(&lexicalGlobalObject);
    UNUSED_PARAM(vm);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto& impl = thisObject.wrapped();
    RefPtr nativeValue = convert<IDLInterface<Node>>(lexicalGlobalObject, value, [](JSC::JSGlobalObject& lexicalGlobalObject, JSC::ThrowScope& scope) { throwAttributeTypeError(lexicalGlobalObject, scope, "TestConditionallyReadWrite"_s, "enabledConditionallyReadWriteBySettingAttributeUnforgeable"_s, "Node"_s); });
    RETURN_IF_EXCEPTION(throwScope, false);
    invokeFunctorPropagatingExceptionIfNecessary(lexicalGlobalObject, throwScope, [&] {
        return impl.setEnabledConditionallyReadWriteBySettingAttributeUnforgeable(*nativeValue);
    });
    return true;
}

JSC_DEFINE_CUSTOM_SETTER(setJSTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttributeUnforgeable, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, EncodedJSValue encodedValue, PropertyName attributeName))
{
    return IDLAttribute<JSTestConditionallyReadWrite>::set<setJSTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttributeUnforgeableSetter>(*lexicalGlobalObject, thisValue, encodedValue, attributeName);
}

static inline JSValue jsTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttributeUnforgeablePrivateGetter(JSGlobalObject& lexicalGlobalObject, JSTestConditionallyReadWrite& thisObject)
{
    auto& vm = JSC::getVM(&lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto& impl = thisObject.wrapped();
    RELEASE_AND_RETURN(throwScope, (toJS<IDLInterface<Node>>(lexicalGlobalObject, *thisObject.globalObject(), throwScope, impl.enabledConditionallyReadWriteBySettingAttributeUnforgeablePrivate())));
}

JSC_DEFINE_CUSTOM_GETTER(jsTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttributeUnforgeablePrivate, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<JSTestConditionallyReadWrite>::get<jsTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttributeUnforgeablePrivateGetter>(*lexicalGlobalObject, thisValue, attributeName);
}

static inline bool setJSTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttributeUnforgeablePrivateSetter(JSGlobalObject& lexicalGlobalObject, JSTestConditionallyReadWrite& thisObject, JSValue value)
{
    auto& vm = JSC::getVM(&lexicalGlobalObject);
    UNUSED_PARAM(vm);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto& impl = thisObject.wrapped();
    RefPtr nativeValue = convert<IDLInterface<Node>>(lexicalGlobalObject, value, [](JSC::JSGlobalObject& lexicalGlobalObject, JSC::ThrowScope& scope) { throwAttributeTypeError(lexicalGlobalObject, scope, "TestConditionallyReadWrite"_s, "enabledConditionallyReadWriteBySettingAttributeUnforgeablePrivate"_s, "Node"_s); });
    RETURN_IF_EXCEPTION(throwScope, false);
    invokeFunctorPropagatingExceptionIfNecessary(lexicalGlobalObject, throwScope, [&] {
        return impl.setEnabledConditionallyReadWriteBySettingAttributeUnforgeablePrivate(*nativeValue);
    });
    return true;
}

JSC_DEFINE_CUSTOM_SETTER(setJSTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttributeUnforgeablePrivate, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, EncodedJSValue encodedValue, PropertyName attributeName))
{
    return IDLAttribute<JSTestConditionallyReadWrite>::set<setJSTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttributeUnforgeablePrivateSetter>(*lexicalGlobalObject, thisValue, encodedValue, attributeName);
}

static inline JSValue jsTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttributePromiseGetter(JSGlobalObject& lexicalGlobalObject, JSTestConditionallyReadWrite& thisObject)
{
    auto& vm = JSC::getVM(&lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto& impl = thisObject.wrapped();
    RELEASE_AND_RETURN(throwScope, (toJS<IDLPromise<IDLDouble>>(lexicalGlobalObject, *thisObject.globalObject(), throwScope, [&]() -> decltype(auto) { return impl.enabledConditionallyReadWriteBySettingAttributePromise(); })));
}

JSC_DEFINE_CUSTOM_GETTER(jsTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttributePromise, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<JSTestConditionallyReadWrite>::get<jsTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttributePromiseGetter, CastedThisErrorBehavior::RejectPromise>(*lexicalGlobalObject, thisValue, attributeName);
}

static inline bool setJSTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttributePromiseSetter(JSGlobalObject& lexicalGlobalObject, JSTestConditionallyReadWrite& thisObject, JSValue value)
{
    auto& vm = JSC::getVM(&lexicalGlobalObject);
    UNUSED_PARAM(vm);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto& impl = thisObject.wrapped();
    auto nativeValue = convert<IDLPromise<IDLDouble>>(lexicalGlobalObject, value);
    RETURN_IF_EXCEPTION(throwScope, false);
    invokeFunctorPropagatingExceptionIfNecessary(lexicalGlobalObject, throwScope, [&] {
        return impl.setEnabledConditionallyReadWriteBySettingAttributePromise(nativeValue.releaseNonNull());
    });
    return true;
}

JSC_DEFINE_CUSTOM_SETTER(setJSTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttributePromise, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, EncodedJSValue encodedValue, PropertyName attributeName))
{
    return IDLAttribute<JSTestConditionallyReadWrite>::set<setJSTestConditionallyReadWrite_enabledConditionallyReadWriteBySettingAttributePromiseSetter>(*lexicalGlobalObject, thisValue, encodedValue, attributeName);
}

JSC::GCClient::IsoSubspace* JSTestConditionallyReadWrite::subspaceForImpl(JSC::VM& vm)
{
    return WebCore::subspaceForImpl<JSTestConditionallyReadWrite, UseCustomHeapCellType::No>(vm,
        [] (auto& spaces) { return spaces.m_clientSubspaceForTestConditionallyReadWrite.get(); },
        [] (auto& spaces, auto&& space) { spaces.m_clientSubspaceForTestConditionallyReadWrite = std::forward<decltype(space)>(space); },
        [] (auto& spaces) { return spaces.m_subspaceForTestConditionallyReadWrite.get(); },
        [] (auto& spaces, auto&& space) { spaces.m_subspaceForTestConditionallyReadWrite = std::forward<decltype(space)>(space); }
    );
}

void JSTestConditionallyReadWrite::analyzeHeap(JSCell* cell, HeapAnalyzer& analyzer)
{
    auto* thisObject = jsCast<JSTestConditionallyReadWrite*>(cell);
    analyzer.setWrappedObjectForCell(cell, &thisObject->wrapped());
    if (thisObject->scriptExecutionContext())
        analyzer.setLabelForCell(cell, "url "_s + thisObject->scriptExecutionContext()->url().string());
    Base::analyzeHeap(cell, analyzer);
}

bool JSTestConditionallyReadWriteOwner::isReachableFromOpaqueRoots(JSC::Handle<JSC::Unknown> handle, void*, AbstractSlotVisitor& visitor, ASCIILiteral* reason)
{
    UNUSED_PARAM(handle);
    UNUSED_PARAM(visitor);
    UNUSED_PARAM(reason);
    return false;
}

void JSTestConditionallyReadWriteOwner::finalize(JSC::Handle<JSC::Unknown> handle, void* context)
{
    auto* jsTestConditionallyReadWrite = static_cast<JSTestConditionallyReadWrite*>(handle.slot()->asCell());
    auto& world = *static_cast<DOMWrapperWorld*>(context);
    uncacheWrapper(world, jsTestConditionallyReadWrite->protectedWrapped().ptr(), jsTestConditionallyReadWrite);
}

#if ENABLE(BINDING_INTEGRITY)
#if PLATFORM(WIN)
#pragma warning(disable: 4483)
extern "C" { extern void (*const __identifier("??_7TestConditionallyReadWrite@WebCore@@6B@")[])(); }
#else
extern "C" { extern void* _ZTVN7WebCore26TestConditionallyReadWriteE[]; }
#endif
template<typename T, typename = std::enable_if_t<std::is_same_v<T, TestConditionallyReadWrite>, void>> static inline void verifyVTable(TestConditionallyReadWrite* ptr) {
    if constexpr (std::is_polymorphic_v<T>) {
        const void* actualVTablePointer = getVTablePointer<T>(ptr);
#if PLATFORM(WIN)
        void* expectedVTablePointer = __identifier("??_7TestConditionallyReadWrite@WebCore@@6B@");
#else
        void* expectedVTablePointer = &_ZTVN7WebCore26TestConditionallyReadWriteE[2];
#endif

        // If you hit this assertion you either have a use after free bug, or
        // TestConditionallyReadWrite has subclasses. If TestConditionallyReadWrite has subclasses that get passed
        // to toJS() we currently require TestConditionallyReadWrite you to opt out of binding hardening
        // by adding the SkipVTableValidation attribute to the interface IDL definition
        RELEASE_ASSERT(actualVTablePointer == expectedVTablePointer);
    }
}
#endif
JSC::JSValue toJSNewlyCreated(JSC::JSGlobalObject*, JSDOMGlobalObject* globalObject, Ref<TestConditionallyReadWrite>&& impl)
{
#if ENABLE(BINDING_INTEGRITY)
    verifyVTable<TestConditionallyReadWrite>(impl.ptr());
#endif
    return createWrapper<TestConditionallyReadWrite>(globalObject, WTFMove(impl));
}

JSC::JSValue toJS(JSC::JSGlobalObject* lexicalGlobalObject, JSDOMGlobalObject* globalObject, TestConditionallyReadWrite& impl)
{
    return wrap(lexicalGlobalObject, globalObject, impl);
}

TestConditionallyReadWrite* JSTestConditionallyReadWrite::toWrapped(JSC::VM&, JSC::JSValue value)
{
    if (auto* wrapper = jsDynamicCast<JSTestConditionallyReadWrite*>(value))
        return &wrapper->wrapped();
    return nullptr;
}

}

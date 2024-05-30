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
#include "JSTestIndexedSetterWithIdentifier.h"

#include "ActiveDOMObject.h"
#include "Document.h"
#include "DocumentInlines.h"
#include "ExtendedDOMClientIsoSubspaces.h"
#include "ExtendedDOMIsoSubspaces.h"
#include "IDLTypes.h"
#include "JSDOMBinding.h"
#include "JSDOMConstructorNotConstructable.h"
#include "JSDOMConvertBase.h"
#include "JSDOMConvertNumbers.h"
#include "JSDOMConvertStrings.h"
#include "JSDOMExceptionHandling.h"
#include "JSDOMGlobalObjectInlines.h"
#include "JSDOMOperation.h"
#include "JSDOMWrapperCache.h"
#include "Quirks.h"
#include "ScriptExecutionContext.h"
#include "WebCoreJSClientData.h"
#include <JavaScriptCore/FunctionPrototype.h>
#include <JavaScriptCore/HeapAnalyzer.h>
#include <JavaScriptCore/JSCInlines.h>
#include <JavaScriptCore/JSDestructibleObjectHeapCellType.h>
#include <JavaScriptCore/PropertyNameArray.h>
#include <JavaScriptCore/SlotVisitorMacros.h>
#include <JavaScriptCore/SubspaceInlines.h>
#include <wtf/GetPtr.h>
#include <wtf/PointerPreparations.h>
#include <wtf/URL.h>


namespace WebCore {
using namespace JSC;

// Functions

static JSC_DECLARE_HOST_FUNCTION(jsTestIndexedSetterWithIdentifierPrototypeFunction_indexedSetter);

// Attributes

static JSC_DECLARE_CUSTOM_GETTER(jsTestIndexedSetterWithIdentifierConstructor);

class JSTestIndexedSetterWithIdentifierPrototype final : public JSC::JSNonFinalObject {
public:
    using Base = JSC::JSNonFinalObject;
    static JSTestIndexedSetterWithIdentifierPrototype* create(JSC::VM& vm, JSDOMGlobalObject* globalObject, JSC::Structure* structure)
    {
        JSTestIndexedSetterWithIdentifierPrototype* ptr = new (NotNull, JSC::allocateCell<JSTestIndexedSetterWithIdentifierPrototype>(vm)) JSTestIndexedSetterWithIdentifierPrototype(vm, globalObject, structure);
        ptr->finishCreation(vm);
        return ptr;
    }

    DECLARE_INFO;
    template<typename CellType, JSC::SubspaceAccess>
    static JSC::GCClient::IsoSubspace* subspaceFor(JSC::VM& vm)
    {
        STATIC_ASSERT_ISO_SUBSPACE_SHARABLE(JSTestIndexedSetterWithIdentifierPrototype, Base);
        return &vm.plainObjectSpace();
    }
    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
    }

private:
    JSTestIndexedSetterWithIdentifierPrototype(JSC::VM& vm, JSC::JSGlobalObject*, JSC::Structure* structure)
        : JSC::JSNonFinalObject(vm, structure)
    {
    }

    void finishCreation(JSC::VM&);
};
STATIC_ASSERT_ISO_SUBSPACE_SHARABLE(JSTestIndexedSetterWithIdentifierPrototype, JSTestIndexedSetterWithIdentifierPrototype::Base);

using JSTestIndexedSetterWithIdentifierDOMConstructor = JSDOMConstructorNotConstructable<JSTestIndexedSetterWithIdentifier>;

template<> const ClassInfo JSTestIndexedSetterWithIdentifierDOMConstructor::s_info = { "TestIndexedSetterWithIdentifier"_s, &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestIndexedSetterWithIdentifierDOMConstructor) };

template<> JSValue JSTestIndexedSetterWithIdentifierDOMConstructor::prototypeForStructure(JSC::VM& vm, const JSDOMGlobalObject& globalObject)
{
    UNUSED_PARAM(vm);
    return globalObject.functionPrototype();
}

template<> void JSTestIndexedSetterWithIdentifierDOMConstructor::initializeProperties(VM& vm, JSDOMGlobalObject& globalObject)
{
    putDirect(vm, vm.propertyNames->length, jsNumber(0), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    JSString* nameString = jsNontrivialString(vm, "TestIndexedSetterWithIdentifier"_s);
    m_originalName.set(vm, this, nameString);
    putDirect(vm, vm.propertyNames->name, nameString, JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    putDirect(vm, vm.propertyNames->prototype, JSTestIndexedSetterWithIdentifier::prototype(vm, globalObject), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum | JSC::PropertyAttribute::DontDelete);
}

/* Hash table for prototype */

static const HashTableValue JSTestIndexedSetterWithIdentifierPrototypeTableValues[] =
{
    { "constructor"_s, static_cast<unsigned>(PropertyAttribute::DontEnum), NoIntrinsic, { HashTableValue::GetterSetterType, jsTestIndexedSetterWithIdentifierConstructor, 0 } },
    { "indexedSetter"_s, static_cast<unsigned>(JSC::PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, jsTestIndexedSetterWithIdentifierPrototypeFunction_indexedSetter, 2 } },
};

const ClassInfo JSTestIndexedSetterWithIdentifierPrototype::s_info = { "TestIndexedSetterWithIdentifier"_s, &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestIndexedSetterWithIdentifierPrototype) };

void JSTestIndexedSetterWithIdentifierPrototype::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    reifyStaticProperties(vm, JSTestIndexedSetterWithIdentifier::info(), JSTestIndexedSetterWithIdentifierPrototypeTableValues, *this);
    JSC_TO_STRING_TAG_WITHOUT_TRANSITION();
}

const ClassInfo JSTestIndexedSetterWithIdentifier::s_info = { "TestIndexedSetterWithIdentifier"_s, &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestIndexedSetterWithIdentifier) };

JSTestIndexedSetterWithIdentifier::JSTestIndexedSetterWithIdentifier(Structure* structure, JSDOMGlobalObject& globalObject, Ref<TestIndexedSetterWithIdentifier>&& impl)
    : JSDOMWrapper<TestIndexedSetterWithIdentifier>(structure, globalObject, WTFMove(impl))
{
}

static_assert(!std::is_base_of<ActiveDOMObject, TestIndexedSetterWithIdentifier>::value, "Interface is not marked as [ActiveDOMObject] even though implementation class subclasses ActiveDOMObject.");

JSObject* JSTestIndexedSetterWithIdentifier::createPrototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    auto* structure = JSTestIndexedSetterWithIdentifierPrototype::createStructure(vm, &globalObject, globalObject.objectPrototype());
    structure->setMayBePrototype(true);
    return JSTestIndexedSetterWithIdentifierPrototype::create(vm, &globalObject, structure);
}

JSObject* JSTestIndexedSetterWithIdentifier::prototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return getDOMPrototype<JSTestIndexedSetterWithIdentifier>(vm, globalObject);
}

JSValue JSTestIndexedSetterWithIdentifier::getConstructor(VM& vm, const JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSTestIndexedSetterWithIdentifierDOMConstructor, DOMConstructorID::TestIndexedSetterWithIdentifier>(vm, *jsCast<const JSDOMGlobalObject*>(globalObject));
}

void JSTestIndexedSetterWithIdentifier::destroy(JSC::JSCell* cell)
{
    JSTestIndexedSetterWithIdentifier* thisObject = static_cast<JSTestIndexedSetterWithIdentifier*>(cell);
    thisObject->JSTestIndexedSetterWithIdentifier::~JSTestIndexedSetterWithIdentifier();
}

bool JSTestIndexedSetterWithIdentifier::legacyPlatformObjectGetOwnProperty(JSObject* object, JSGlobalObject* lexicalGlobalObject, PropertyName propertyName, PropertySlot& slot, bool ignoreNamedProperties)
{
    UNUSED_PARAM(ignoreNamedProperties);
    auto throwScope = DECLARE_THROW_SCOPE(JSC::getVM(lexicalGlobalObject));
    auto* thisObject = jsCast<JSTestIndexedSetterWithIdentifier*>(object);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());
    if (auto index = parseIndex(propertyName)) {
        if (auto item = thisObject->wrapped().item(index.value()); LIKELY(!!item)) {
            auto value = toJS<IDLDOMString>(*lexicalGlobalObject, throwScope, WTFMove(item));
            RETURN_IF_EXCEPTION(throwScope, false);
            slot.setValue(thisObject, 0, value);
            return true;
        }
    }
    return JSObject::getOwnPropertySlot(object, lexicalGlobalObject, propertyName, slot);
}

bool JSTestIndexedSetterWithIdentifier::getOwnPropertySlot(JSObject* object, JSGlobalObject* lexicalGlobalObject, PropertyName propertyName, PropertySlot& slot)
{
    bool ignoreNamedProperties = false;
    return legacyPlatformObjectGetOwnProperty(object, lexicalGlobalObject, propertyName, slot, ignoreNamedProperties);
}

bool JSTestIndexedSetterWithIdentifier::getOwnPropertySlotByIndex(JSObject* object, JSGlobalObject* lexicalGlobalObject, unsigned index, PropertySlot& slot)
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* thisObject = jsCast<JSTestIndexedSetterWithIdentifier*>(object);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());
    if (LIKELY(index <= MAX_ARRAY_INDEX)) {
        if (auto item = thisObject->wrapped().item(index); LIKELY(!!item)) {
            auto value = toJS<IDLDOMString>(*lexicalGlobalObject, throwScope, WTFMove(item));
            RETURN_IF_EXCEPTION(throwScope, false);
            slot.setValue(thisObject, 0, value);
            return true;
        }
    }
    return JSObject::getOwnPropertySlotByIndex(object, lexicalGlobalObject, index, slot);
}

void JSTestIndexedSetterWithIdentifier::getOwnPropertyNames(JSObject* object, JSGlobalObject* lexicalGlobalObject, PropertyNameArray& propertyNames, DontEnumPropertiesMode mode)
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto* thisObject = jsCast<JSTestIndexedSetterWithIdentifier*>(object);
    ASSERT_GC_OBJECT_INHERITS(object, info());
    for (unsigned i = 0, count = thisObject->wrapped().length(); i < count; ++i)
        propertyNames.add(Identifier::from(vm, i));
    JSObject::getOwnPropertyNames(object, lexicalGlobalObject, propertyNames, mode);
}

bool JSTestIndexedSetterWithIdentifier::put(JSCell* cell, JSGlobalObject* lexicalGlobalObject, PropertyName propertyName, JSValue value, PutPropertySlot& putPropertySlot)
{
    auto* thisObject = jsCast<JSTestIndexedSetterWithIdentifier*>(cell);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());

    if (UNLIKELY(thisObject != putPropertySlot.thisValue()))
        return JSObject::put(thisObject, lexicalGlobalObject, propertyName, value, putPropertySlot);
    auto throwScope = DECLARE_THROW_SCOPE(lexicalGlobalObject->vm());

    if (auto index = parseIndex(propertyName)) {
        auto nativeValue = convert<IDLDOMString>(*lexicalGlobalObject, value);
        RETURN_IF_EXCEPTION(throwScope, true);
        invokeFunctorPropagatingExceptionIfNecessary(*lexicalGlobalObject, throwScope, [&] { return thisObject->wrapped().indexedSetter(index.value(), WTFMove(nativeValue)); });
        return true;
    }

    throwScope.assertNoException();
    RELEASE_AND_RETURN(throwScope, JSObject::put(thisObject, lexicalGlobalObject, propertyName, value, putPropertySlot));
}

bool JSTestIndexedSetterWithIdentifier::putByIndex(JSCell* cell, JSGlobalObject* lexicalGlobalObject, unsigned index, JSValue value, bool shouldThrow)
{
    auto* thisObject = jsCast<JSTestIndexedSetterWithIdentifier*>(cell);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());

    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);

    if (LIKELY(index <= MAX_ARRAY_INDEX)) {
        auto nativeValue = convert<IDLDOMString>(*lexicalGlobalObject, value);
        RETURN_IF_EXCEPTION(throwScope, true);
        invokeFunctorPropagatingExceptionIfNecessary(*lexicalGlobalObject, throwScope, [&] { return thisObject->wrapped().indexedSetter(index, WTFMove(nativeValue)); });
        return true;
    }

    throwScope.assertNoException();
    auto propertyName = Identifier::from(vm, index);
    PutPropertySlot putPropertySlot(thisObject, shouldThrow);
    RELEASE_AND_RETURN(throwScope, ordinarySetSlow(lexicalGlobalObject, thisObject, propertyName, value, putPropertySlot.thisValue(), shouldThrow));
}

bool JSTestIndexedSetterWithIdentifier::defineOwnProperty(JSObject* object, JSGlobalObject* lexicalGlobalObject, PropertyName propertyName, const PropertyDescriptor& propertyDescriptor, bool shouldThrow)
{
    auto* thisObject = jsCast<JSTestIndexedSetterWithIdentifier*>(object);
    ASSERT_GC_OBJECT_INHERITS(thisObject, info());

    auto throwScope = DECLARE_THROW_SCOPE(lexicalGlobalObject->vm());

    if (auto index = parseIndex(propertyName)) {
        if (!propertyDescriptor.isDataDescriptor())
            return typeError(lexicalGlobalObject, throwScope, shouldThrow, "Cannot set indexed properties on this object"_s);
        auto nativeValue = convert<IDLDOMString>(*lexicalGlobalObject, propertyDescriptor.value());
        RETURN_IF_EXCEPTION(throwScope, true);
        invokeFunctorPropagatingExceptionIfNecessary(*lexicalGlobalObject, throwScope, [&] { return thisObject->wrapped().indexedSetter(index.value(), WTFMove(nativeValue)); });
        return true;
    }

    PropertyDescriptor newPropertyDescriptor = propertyDescriptor;
    throwScope.release();
    return JSObject::defineOwnProperty(object, lexicalGlobalObject, propertyName, newPropertyDescriptor, shouldThrow);
}

bool JSTestIndexedSetterWithIdentifier::deleteProperty(JSCell* cell, JSGlobalObject* lexicalGlobalObject, PropertyName propertyName, DeletePropertySlot& slot)
{
    auto& thisObject = *jsCast<JSTestIndexedSetterWithIdentifier*>(cell);
    auto& impl = thisObject.wrapped();

    // Temporary quirk for ungap/@custom-elements polyfill (rdar://problem/111008826), consider removing in 2025.
    if (auto* document = dynamicDowncast<Document>(jsDynamicCast<JSDOMGlobalObject*>(lexicalGlobalObject)->scriptExecutionContext())) {
        if (UNLIKELY(document->quirks().needsConfigurableIndexedPropertiesQuirk()))
            return JSObject::deleteProperty(cell, lexicalGlobalObject, propertyName, slot);
    }

    if (auto index = parseIndex(propertyName))
        return !impl.isSupportedPropertyIndex(index.value());
    return JSObject::deleteProperty(cell, lexicalGlobalObject, propertyName, slot);
}

bool JSTestIndexedSetterWithIdentifier::deletePropertyByIndex(JSCell* cell, JSGlobalObject* lexicalGlobalObject, unsigned index)
{
    UNUSED_PARAM(lexicalGlobalObject);
    auto& thisObject = *jsCast<JSTestIndexedSetterWithIdentifier*>(cell);
    auto& impl = thisObject.wrapped();

    // Temporary quirk for ungap/@custom-elements polyfill (rdar://problem/111008826), consider removing in 2025.
    if (auto* document = dynamicDowncast<Document>(jsDynamicCast<JSDOMGlobalObject*>(lexicalGlobalObject)->scriptExecutionContext())) {
        if (UNLIKELY(document->quirks().needsConfigurableIndexedPropertiesQuirk()))
            return JSObject::deletePropertyByIndex(cell, lexicalGlobalObject, index);
    }

    return !impl.isSupportedPropertyIndex(index);
}

JSC_DEFINE_CUSTOM_GETTER(jsTestIndexedSetterWithIdentifierConstructor, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName))
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* prototype = jsDynamicCast<JSTestIndexedSetterWithIdentifierPrototype*>(JSValue::decode(thisValue));
    if (UNLIKELY(!prototype))
        return throwVMTypeError(lexicalGlobalObject, throwScope);
    return JSValue::encode(JSTestIndexedSetterWithIdentifier::getConstructor(vm, prototype->globalObject()));
}

static inline JSC::EncodedJSValue jsTestIndexedSetterWithIdentifierPrototypeFunction_indexedSetterBody(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, typename IDLOperation<JSTestIndexedSetterWithIdentifier>::ClassParameter castedThis)
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    UNUSED_PARAM(throwScope);
    UNUSED_PARAM(callFrame);
    auto& impl = castedThis->wrapped();
    if (UNLIKELY(callFrame->argumentCount() < 2))
        return throwVMError(lexicalGlobalObject, throwScope, createNotEnoughArgumentsError(lexicalGlobalObject));
    EnsureStillAliveScope argument0 = callFrame->uncheckedArgument(0);
    auto index = convert<IDLUnsignedLong>(*lexicalGlobalObject, argument0.value());
    RETURN_IF_EXCEPTION(throwScope, encodedJSValue());
    EnsureStillAliveScope argument1 = callFrame->uncheckedArgument(1);
    auto value = convert<IDLDOMString>(*lexicalGlobalObject, argument1.value());
    RETURN_IF_EXCEPTION(throwScope, encodedJSValue());
    RELEASE_AND_RETURN(throwScope, JSValue::encode(toJS<IDLUndefined>(*lexicalGlobalObject, throwScope, [&]() -> decltype(auto) { return impl.indexedSetter(WTFMove(index), WTFMove(value)); })));
}

JSC_DEFINE_HOST_FUNCTION(jsTestIndexedSetterWithIdentifierPrototypeFunction_indexedSetter, (JSGlobalObject* lexicalGlobalObject, CallFrame* callFrame))
{
    return IDLOperation<JSTestIndexedSetterWithIdentifier>::call<jsTestIndexedSetterWithIdentifierPrototypeFunction_indexedSetterBody>(*lexicalGlobalObject, *callFrame, "indexedSetter");
}

JSC::GCClient::IsoSubspace* JSTestIndexedSetterWithIdentifier::subspaceForImpl(JSC::VM& vm)
{
    return WebCore::subspaceForImpl<JSTestIndexedSetterWithIdentifier, UseCustomHeapCellType::No>(vm,
        [] (auto& spaces) { return spaces.m_clientSubspaceForTestIndexedSetterWithIdentifier.get(); },
        [] (auto& spaces, auto&& space) { spaces.m_clientSubspaceForTestIndexedSetterWithIdentifier = std::forward<decltype(space)>(space); },
        [] (auto& spaces) { return spaces.m_subspaceForTestIndexedSetterWithIdentifier.get(); },
        [] (auto& spaces, auto&& space) { spaces.m_subspaceForTestIndexedSetterWithIdentifier = std::forward<decltype(space)>(space); }
    );
}

void JSTestIndexedSetterWithIdentifier::analyzeHeap(JSCell* cell, HeapAnalyzer& analyzer)
{
    auto* thisObject = jsCast<JSTestIndexedSetterWithIdentifier*>(cell);
    analyzer.setWrappedObjectForCell(cell, &thisObject->wrapped());
    if (thisObject->scriptExecutionContext())
        analyzer.setLabelForCell(cell, "url "_s + thisObject->scriptExecutionContext()->url().string());
    Base::analyzeHeap(cell, analyzer);
}

bool JSTestIndexedSetterWithIdentifierOwner::isReachableFromOpaqueRoots(JSC::Handle<JSC::Unknown> handle, void*, AbstractSlotVisitor& visitor, ASCIILiteral* reason)
{
    UNUSED_PARAM(handle);
    UNUSED_PARAM(visitor);
    UNUSED_PARAM(reason);
    return false;
}

void JSTestIndexedSetterWithIdentifierOwner::finalize(JSC::Handle<JSC::Unknown> handle, void* context)
{
    auto* jsTestIndexedSetterWithIdentifier = static_cast<JSTestIndexedSetterWithIdentifier*>(handle.slot()->asCell());
    auto& world = *static_cast<DOMWrapperWorld*>(context);
    uncacheWrapper(world, jsTestIndexedSetterWithIdentifier->protectedWrapped().ptr(), jsTestIndexedSetterWithIdentifier);
}

#if ENABLE(BINDING_INTEGRITY)
#if PLATFORM(WIN)
#pragma warning(disable: 4483)
extern "C" { extern void (*const __identifier("??_7TestIndexedSetterWithIdentifier@WebCore@@6B@")[])(); }
#else
extern "C" { extern void* _ZTVN7WebCore31TestIndexedSetterWithIdentifierE[]; }
#endif
template<typename T, typename = std::enable_if_t<std::is_same_v<T, TestIndexedSetterWithIdentifier>, void>> static inline void verifyVTable(TestIndexedSetterWithIdentifier* ptr) {
    if constexpr (std::is_polymorphic_v<T>) {
        const void* actualVTablePointer = getVTablePointer<T>(ptr);
#if PLATFORM(WIN)
        void* expectedVTablePointer = __identifier("??_7TestIndexedSetterWithIdentifier@WebCore@@6B@");
#else
        void* expectedVTablePointer = &_ZTVN7WebCore31TestIndexedSetterWithIdentifierE[2];
#endif

        // If you hit this assertion you either have a use after free bug, or
        // TestIndexedSetterWithIdentifier has subclasses. If TestIndexedSetterWithIdentifier has subclasses that get passed
        // to toJS() we currently require TestIndexedSetterWithIdentifier you to opt out of binding hardening
        // by adding the SkipVTableValidation attribute to the interface IDL definition
        RELEASE_ASSERT(actualVTablePointer == expectedVTablePointer);
    }
}
#endif
JSC::JSValue toJSNewlyCreated(JSC::JSGlobalObject*, JSDOMGlobalObject* globalObject, Ref<TestIndexedSetterWithIdentifier>&& impl)
{
#if ENABLE(BINDING_INTEGRITY)
    verifyVTable<TestIndexedSetterWithIdentifier>(impl.ptr());
#endif
    return createWrapper<TestIndexedSetterWithIdentifier>(globalObject, WTFMove(impl));
}

JSC::JSValue toJS(JSC::JSGlobalObject* lexicalGlobalObject, JSDOMGlobalObject* globalObject, TestIndexedSetterWithIdentifier& impl)
{
    return wrap(lexicalGlobalObject, globalObject, impl);
}

TestIndexedSetterWithIdentifier* JSTestIndexedSetterWithIdentifier::toWrapped(JSC::VM&, JSC::JSValue value)
{
    if (auto* wrapper = jsDynamicCast<JSTestIndexedSetterWithIdentifier*>(value))
        return &wrapper->wrapped();
    return nullptr;
}

}

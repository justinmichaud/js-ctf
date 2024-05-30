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

#if ENABLE(ConditionDerived)

#include "JSTestOperationConditional.h"

#include "ActiveDOMObject.h"
#include "ExtendedDOMClientIsoSubspaces.h"
#include "ExtendedDOMIsoSubspaces.h"
#include "JSDOMBinding.h"
#include "JSDOMConstructorNotConstructable.h"
#include "JSDOMExceptionHandling.h"
#include "JSDOMGlobalObjectInlines.h"
#include "JSDOMOperation.h"
#include "JSDOMWrapperCache.h"
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

#if ENABLE(ConditionBase) || (ENABLE(ConditionBase) && ENABLE(ConditionOperation))
#include "IDLTypes.h"
#include "JSDOMConvertBase.h"
#endif


namespace WebCore {
using namespace JSC;

// Functions

#if ENABLE(ConditionBase)
static JSC_DECLARE_HOST_FUNCTION(jsTestOperationConditionalPrototypeFunction_nonConditionalOperation);
#endif
#if ENABLE(ConditionBase) && ENABLE(ConditionOperation)
static JSC_DECLARE_HOST_FUNCTION(jsTestOperationConditionalPrototypeFunction_conditionalOperation);
#endif

// Attributes

static JSC_DECLARE_CUSTOM_GETTER(jsTestOperationConditionalConstructor);

class JSTestOperationConditionalPrototype final : public JSC::JSNonFinalObject {
public:
    using Base = JSC::JSNonFinalObject;
    static JSTestOperationConditionalPrototype* create(JSC::VM& vm, JSDOMGlobalObject* globalObject, JSC::Structure* structure)
    {
        JSTestOperationConditionalPrototype* ptr = new (NotNull, JSC::allocateCell<JSTestOperationConditionalPrototype>(vm)) JSTestOperationConditionalPrototype(vm, globalObject, structure);
        ptr->finishCreation(vm);
        return ptr;
    }

    DECLARE_INFO;
    template<typename CellType, JSC::SubspaceAccess>
    static JSC::GCClient::IsoSubspace* subspaceFor(JSC::VM& vm)
    {
        STATIC_ASSERT_ISO_SUBSPACE_SHARABLE(JSTestOperationConditionalPrototype, Base);
        return &vm.plainObjectSpace();
    }
    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
    }

private:
    JSTestOperationConditionalPrototype(JSC::VM& vm, JSC::JSGlobalObject*, JSC::Structure* structure)
        : JSC::JSNonFinalObject(vm, structure)
    {
    }

    void finishCreation(JSC::VM&);
};
STATIC_ASSERT_ISO_SUBSPACE_SHARABLE(JSTestOperationConditionalPrototype, JSTestOperationConditionalPrototype::Base);

using JSTestOperationConditionalDOMConstructor = JSDOMConstructorNotConstructable<JSTestOperationConditional>;

template<> const ClassInfo JSTestOperationConditionalDOMConstructor::s_info = { "TestOperationConditional"_s, &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestOperationConditionalDOMConstructor) };

template<> JSValue JSTestOperationConditionalDOMConstructor::prototypeForStructure(JSC::VM& vm, const JSDOMGlobalObject& globalObject)
{
    UNUSED_PARAM(vm);
    return globalObject.functionPrototype();
}

template<> void JSTestOperationConditionalDOMConstructor::initializeProperties(VM& vm, JSDOMGlobalObject& globalObject)
{
    putDirect(vm, vm.propertyNames->length, jsNumber(0), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    JSString* nameString = jsNontrivialString(vm, "TestOperationConditional"_s);
    m_originalName.set(vm, this, nameString);
    putDirect(vm, vm.propertyNames->name, nameString, JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    putDirect(vm, vm.propertyNames->prototype, JSTestOperationConditional::prototype(vm, globalObject), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum | JSC::PropertyAttribute::DontDelete);
}

/* Hash table for prototype */

static const HashTableValue JSTestOperationConditionalPrototypeTableValues[] =
{
    { "constructor"_s, static_cast<unsigned>(PropertyAttribute::DontEnum), NoIntrinsic, { HashTableValue::GetterSetterType, jsTestOperationConditionalConstructor, 0 } },
#if ENABLE(ConditionBase)
    { "nonConditionalOperation"_s, static_cast<unsigned>(JSC::PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, jsTestOperationConditionalPrototypeFunction_nonConditionalOperation, 0 } },
#else
    { { }, 0, NoIntrinsic, { HashTableValue::End } },
#endif
#if ENABLE(ConditionBase) && ENABLE(ConditionOperation)
    { "conditionalOperation"_s, static_cast<unsigned>(JSC::PropertyAttribute::Function), NoIntrinsic, { HashTableValue::NativeFunctionType, jsTestOperationConditionalPrototypeFunction_conditionalOperation, 0 } },
#else
    { { }, 0, NoIntrinsic, { HashTableValue::End } },
#endif
};

const ClassInfo JSTestOperationConditionalPrototype::s_info = { "TestOperationConditional"_s, &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestOperationConditionalPrototype) };

void JSTestOperationConditionalPrototype::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    reifyStaticProperties(vm, JSTestOperationConditional::info(), JSTestOperationConditionalPrototypeTableValues, *this);
    JSC_TO_STRING_TAG_WITHOUT_TRANSITION();
}

const ClassInfo JSTestOperationConditional::s_info = { "TestOperationConditional"_s, &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestOperationConditional) };

JSTestOperationConditional::JSTestOperationConditional(Structure* structure, JSDOMGlobalObject& globalObject, Ref<TestOperationConditional>&& impl)
    : JSDOMWrapper<TestOperationConditional>(structure, globalObject, WTFMove(impl))
{
}

static_assert(!std::is_base_of<ActiveDOMObject, TestOperationConditional>::value, "Interface is not marked as [ActiveDOMObject] even though implementation class subclasses ActiveDOMObject.");

JSObject* JSTestOperationConditional::createPrototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    auto* structure = JSTestOperationConditionalPrototype::createStructure(vm, &globalObject, globalObject.objectPrototype());
    structure->setMayBePrototype(true);
    return JSTestOperationConditionalPrototype::create(vm, &globalObject, structure);
}

JSObject* JSTestOperationConditional::prototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return getDOMPrototype<JSTestOperationConditional>(vm, globalObject);
}

JSValue JSTestOperationConditional::getConstructor(VM& vm, const JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSTestOperationConditionalDOMConstructor, DOMConstructorID::TestOperationConditional>(vm, *jsCast<const JSDOMGlobalObject*>(globalObject));
}

void JSTestOperationConditional::destroy(JSC::JSCell* cell)
{
    JSTestOperationConditional* thisObject = static_cast<JSTestOperationConditional*>(cell);
    thisObject->JSTestOperationConditional::~JSTestOperationConditional();
}

JSC_DEFINE_CUSTOM_GETTER(jsTestOperationConditionalConstructor, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName))
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* prototype = jsDynamicCast<JSTestOperationConditionalPrototype*>(JSValue::decode(thisValue));
    if (UNLIKELY(!prototype))
        return throwVMTypeError(lexicalGlobalObject, throwScope);
    return JSValue::encode(JSTestOperationConditional::getConstructor(vm, prototype->globalObject()));
}

#if ENABLE(ConditionBase)
static inline JSC::EncodedJSValue jsTestOperationConditionalPrototypeFunction_nonConditionalOperationBody(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, typename IDLOperation<JSTestOperationConditional>::ClassParameter castedThis)
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    UNUSED_PARAM(throwScope);
    UNUSED_PARAM(callFrame);
    auto& impl = castedThis->wrapped();
    RELEASE_AND_RETURN(throwScope, JSValue::encode(toJS<IDLUndefined>(*lexicalGlobalObject, throwScope, [&]() -> decltype(auto) { return impl.nonConditionalOperation(); })));
}

JSC_DEFINE_HOST_FUNCTION(jsTestOperationConditionalPrototypeFunction_nonConditionalOperation, (JSGlobalObject* lexicalGlobalObject, CallFrame* callFrame))
{
    return IDLOperation<JSTestOperationConditional>::call<jsTestOperationConditionalPrototypeFunction_nonConditionalOperationBody>(*lexicalGlobalObject, *callFrame, "nonConditionalOperation");
}

#endif

#if ENABLE(ConditionBase) && ENABLE(ConditionOperation)
static inline JSC::EncodedJSValue jsTestOperationConditionalPrototypeFunction_conditionalOperationBody(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, typename IDLOperation<JSTestOperationConditional>::ClassParameter castedThis)
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    UNUSED_PARAM(throwScope);
    UNUSED_PARAM(callFrame);
    auto& impl = castedThis->wrapped();
    RELEASE_AND_RETURN(throwScope, JSValue::encode(toJS<IDLUndefined>(*lexicalGlobalObject, throwScope, [&]() -> decltype(auto) { return impl.conditionalOperation(); })));
}

JSC_DEFINE_HOST_FUNCTION(jsTestOperationConditionalPrototypeFunction_conditionalOperation, (JSGlobalObject* lexicalGlobalObject, CallFrame* callFrame))
{
    return IDLOperation<JSTestOperationConditional>::call<jsTestOperationConditionalPrototypeFunction_conditionalOperationBody>(*lexicalGlobalObject, *callFrame, "conditionalOperation");
}

#endif

JSC::GCClient::IsoSubspace* JSTestOperationConditional::subspaceForImpl(JSC::VM& vm)
{
    return WebCore::subspaceForImpl<JSTestOperationConditional, UseCustomHeapCellType::No>(vm,
        [] (auto& spaces) { return spaces.m_clientSubspaceForTestOperationConditional.get(); },
        [] (auto& spaces, auto&& space) { spaces.m_clientSubspaceForTestOperationConditional = std::forward<decltype(space)>(space); },
        [] (auto& spaces) { return spaces.m_subspaceForTestOperationConditional.get(); },
        [] (auto& spaces, auto&& space) { spaces.m_subspaceForTestOperationConditional = std::forward<decltype(space)>(space); }
    );
}

void JSTestOperationConditional::analyzeHeap(JSCell* cell, HeapAnalyzer& analyzer)
{
    auto* thisObject = jsCast<JSTestOperationConditional*>(cell);
    analyzer.setWrappedObjectForCell(cell, &thisObject->wrapped());
    if (thisObject->scriptExecutionContext())
        analyzer.setLabelForCell(cell, "url "_s + thisObject->scriptExecutionContext()->url().string());
    Base::analyzeHeap(cell, analyzer);
}

bool JSTestOperationConditionalOwner::isReachableFromOpaqueRoots(JSC::Handle<JSC::Unknown> handle, void*, AbstractSlotVisitor& visitor, ASCIILiteral* reason)
{
    UNUSED_PARAM(handle);
    UNUSED_PARAM(visitor);
    UNUSED_PARAM(reason);
    return false;
}

void JSTestOperationConditionalOwner::finalize(JSC::Handle<JSC::Unknown> handle, void* context)
{
    auto* jsTestOperationConditional = static_cast<JSTestOperationConditional*>(handle.slot()->asCell());
    auto& world = *static_cast<DOMWrapperWorld*>(context);
    uncacheWrapper(world, jsTestOperationConditional->protectedWrapped().ptr(), jsTestOperationConditional);
}

#if ENABLE(BINDING_INTEGRITY)
#if PLATFORM(WIN)
#pragma warning(disable: 4483)
extern "C" { extern void (*const __identifier("??_7TestOperationConditional@WebCore@@6B@")[])(); }
#else
extern "C" { extern void* _ZTVN7WebCore24TestOperationConditionalE[]; }
#endif
template<typename T, typename = std::enable_if_t<std::is_same_v<T, TestOperationConditional>, void>> static inline void verifyVTable(TestOperationConditional* ptr) {
    if constexpr (std::is_polymorphic_v<T>) {
        const void* actualVTablePointer = getVTablePointer<T>(ptr);
#if PLATFORM(WIN)
        void* expectedVTablePointer = __identifier("??_7TestOperationConditional@WebCore@@6B@");
#else
        void* expectedVTablePointer = &_ZTVN7WebCore24TestOperationConditionalE[2];
#endif

        // If you hit this assertion you either have a use after free bug, or
        // TestOperationConditional has subclasses. If TestOperationConditional has subclasses that get passed
        // to toJS() we currently require TestOperationConditional you to opt out of binding hardening
        // by adding the SkipVTableValidation attribute to the interface IDL definition
        RELEASE_ASSERT(actualVTablePointer == expectedVTablePointer);
    }
}
#endif
JSC::JSValue toJSNewlyCreated(JSC::JSGlobalObject*, JSDOMGlobalObject* globalObject, Ref<TestOperationConditional>&& impl)
{
#if ENABLE(BINDING_INTEGRITY)
    verifyVTable<TestOperationConditional>(impl.ptr());
#endif
    return createWrapper<TestOperationConditional>(globalObject, WTFMove(impl));
}

JSC::JSValue toJS(JSC::JSGlobalObject* lexicalGlobalObject, JSDOMGlobalObject* globalObject, TestOperationConditional& impl)
{
    return wrap(lexicalGlobalObject, globalObject, impl);
}

TestOperationConditional* JSTestOperationConditional::toWrapped(JSC::VM&, JSC::JSValue value)
{
    if (auto* wrapper = jsDynamicCast<JSTestOperationConditional*>(value))
        return &wrapper->wrapped();
    return nullptr;
}

}

#endif // ENABLE(ConditionDerived)

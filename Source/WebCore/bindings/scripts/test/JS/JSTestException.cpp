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
#include "JSTestException.h"

#include "ActiveDOMObject.h"
#include "ExtendedDOMClientIsoSubspaces.h"
#include "ExtendedDOMIsoSubspaces.h"
#include "JSDOMAttribute.h"
#include "JSDOMBinding.h"
#include "JSDOMConstructorNotConstructable.h"
#include "JSDOMConvertStrings.h"
#include "JSDOMExceptionHandling.h"
#include "JSDOMGlobalObjectInlines.h"
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


namespace WebCore {
using namespace JSC;

// Attributes

static JSC_DECLARE_CUSTOM_GETTER(jsTestExceptionConstructor);
static JSC_DECLARE_CUSTOM_GETTER(jsTestException_name);

class JSTestExceptionPrototype final : public JSC::JSNonFinalObject {
public:
    using Base = JSC::JSNonFinalObject;
    static JSTestExceptionPrototype* create(JSC::VM& vm, JSDOMGlobalObject* globalObject, JSC::Structure* structure)
    {
        JSTestExceptionPrototype* ptr = new (NotNull, JSC::allocateCell<JSTestExceptionPrototype>(vm)) JSTestExceptionPrototype(vm, globalObject, structure);
        ptr->finishCreation(vm);
        return ptr;
    }

    DECLARE_INFO;
    template<typename CellType, JSC::SubspaceAccess>
    static JSC::GCClient::IsoSubspace* subspaceFor(JSC::VM& vm)
    {
        STATIC_ASSERT_ISO_SUBSPACE_SHARABLE(JSTestExceptionPrototype, Base);
        return &vm.plainObjectSpace();
    }
    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
    }

private:
    JSTestExceptionPrototype(JSC::VM& vm, JSC::JSGlobalObject*, JSC::Structure* structure)
        : JSC::JSNonFinalObject(vm, structure)
    {
    }

    void finishCreation(JSC::VM&);
};
STATIC_ASSERT_ISO_SUBSPACE_SHARABLE(JSTestExceptionPrototype, JSTestExceptionPrototype::Base);

using JSTestExceptionDOMConstructor = JSDOMConstructorNotConstructable<JSTestException>;

template<> const ClassInfo JSTestExceptionDOMConstructor::s_info = { "TestException"_s, &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestExceptionDOMConstructor) };

template<> JSValue JSTestExceptionDOMConstructor::prototypeForStructure(JSC::VM& vm, const JSDOMGlobalObject& globalObject)
{
    UNUSED_PARAM(vm);
    return globalObject.functionPrototype();
}

template<> void JSTestExceptionDOMConstructor::initializeProperties(VM& vm, JSDOMGlobalObject& globalObject)
{
    putDirect(vm, vm.propertyNames->length, jsNumber(0), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    JSString* nameString = jsNontrivialString(vm, "TestException"_s);
    m_originalName.set(vm, this, nameString);
    putDirect(vm, vm.propertyNames->name, nameString, JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    putDirect(vm, vm.propertyNames->prototype, JSTestException::prototype(vm, globalObject), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum | JSC::PropertyAttribute::DontDelete);
}

/* Hash table for prototype */

static const HashTableValue JSTestExceptionPrototypeTableValues[] =
{
    { "constructor"_s, static_cast<unsigned>(PropertyAttribute::DontEnum), NoIntrinsic, { HashTableValue::GetterSetterType, jsTestExceptionConstructor, 0 } },
    { "name"_s, JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::CustomAccessor | JSC::PropertyAttribute::DOMAttribute, NoIntrinsic, { HashTableValue::GetterSetterType, jsTestException_name, 0 } },
};

const ClassInfo JSTestExceptionPrototype::s_info = { "TestException"_s, &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestExceptionPrototype) };

void JSTestExceptionPrototype::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    reifyStaticProperties(vm, JSTestException::info(), JSTestExceptionPrototypeTableValues, *this);
    JSC_TO_STRING_TAG_WITHOUT_TRANSITION();
}

const ClassInfo JSTestException::s_info = { "TestException"_s, &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestException) };

JSTestException::JSTestException(Structure* structure, JSDOMGlobalObject& globalObject, Ref<TestException>&& impl)
    : JSDOMWrapper<TestException>(structure, globalObject, WTFMove(impl))
{
}

static_assert(!std::is_base_of<ActiveDOMObject, TestException>::value, "Interface is not marked as [ActiveDOMObject] even though implementation class subclasses ActiveDOMObject.");

JSObject* JSTestException::createPrototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    auto* structure = JSTestExceptionPrototype::createStructure(vm, &globalObject, globalObject.errorPrototype());
    structure->setMayBePrototype(true);
    return JSTestExceptionPrototype::create(vm, &globalObject, structure);
}

JSObject* JSTestException::prototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return getDOMPrototype<JSTestException>(vm, globalObject);
}

JSValue JSTestException::getConstructor(VM& vm, const JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSTestExceptionDOMConstructor, DOMConstructorID::TestException>(vm, *jsCast<const JSDOMGlobalObject*>(globalObject));
}

void JSTestException::destroy(JSC::JSCell* cell)
{
    JSTestException* thisObject = static_cast<JSTestException*>(cell);
    thisObject->JSTestException::~JSTestException();
}

JSC_DEFINE_CUSTOM_GETTER(jsTestExceptionConstructor, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName))
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* prototype = jsDynamicCast<JSTestExceptionPrototype*>(JSValue::decode(thisValue));
    if (UNLIKELY(!prototype))
        return throwVMTypeError(lexicalGlobalObject, throwScope);
    return JSValue::encode(JSTestException::getConstructor(vm, prototype->globalObject()));
}

static inline JSValue jsTestException_nameGetter(JSGlobalObject& lexicalGlobalObject, JSTestException& thisObject)
{
    auto& vm = JSC::getVM(&lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto& impl = thisObject.wrapped();
    RELEASE_AND_RETURN(throwScope, (toJS<IDLDOMString>(lexicalGlobalObject, throwScope, impl.name())));
}

JSC_DEFINE_CUSTOM_GETTER(jsTestException_name, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<JSTestException>::get<jsTestException_nameGetter, CastedThisErrorBehavior::Assert>(*lexicalGlobalObject, thisValue, attributeName);
}

JSC::GCClient::IsoSubspace* JSTestException::subspaceForImpl(JSC::VM& vm)
{
    return WebCore::subspaceForImpl<JSTestException, UseCustomHeapCellType::No>(vm,
        [] (auto& spaces) { return spaces.m_clientSubspaceForTestException.get(); },
        [] (auto& spaces, auto&& space) { spaces.m_clientSubspaceForTestException = std::forward<decltype(space)>(space); },
        [] (auto& spaces) { return spaces.m_subspaceForTestException.get(); },
        [] (auto& spaces, auto&& space) { spaces.m_subspaceForTestException = std::forward<decltype(space)>(space); }
    );
}

void JSTestException::analyzeHeap(JSCell* cell, HeapAnalyzer& analyzer)
{
    auto* thisObject = jsCast<JSTestException*>(cell);
    analyzer.setWrappedObjectForCell(cell, &thisObject->wrapped());
    if (thisObject->scriptExecutionContext())
        analyzer.setLabelForCell(cell, "url "_s + thisObject->scriptExecutionContext()->url().string());
    Base::analyzeHeap(cell, analyzer);
}

bool JSTestExceptionOwner::isReachableFromOpaqueRoots(JSC::Handle<JSC::Unknown> handle, void*, AbstractSlotVisitor& visitor, ASCIILiteral* reason)
{
    UNUSED_PARAM(handle);
    UNUSED_PARAM(visitor);
    UNUSED_PARAM(reason);
    return false;
}

void JSTestExceptionOwner::finalize(JSC::Handle<JSC::Unknown> handle, void* context)
{
    auto* jsTestException = static_cast<JSTestException*>(handle.slot()->asCell());
    auto& world = *static_cast<DOMWrapperWorld*>(context);
    uncacheWrapper(world, jsTestException->protectedWrapped().ptr(), jsTestException);
}

#if ENABLE(BINDING_INTEGRITY)
#if PLATFORM(WIN)
#pragma warning(disable: 4483)
extern "C" { extern void (*const __identifier("??_7TestException@WebCore@@6B@")[])(); }
#else
extern "C" { extern void* _ZTVN7WebCore13TestExceptionE[]; }
#endif
template<typename T, typename = std::enable_if_t<std::is_same_v<T, TestException>, void>> static inline void verifyVTable(TestException* ptr) {
    if constexpr (std::is_polymorphic_v<T>) {
        const void* actualVTablePointer = getVTablePointer<T>(ptr);
#if PLATFORM(WIN)
        void* expectedVTablePointer = __identifier("??_7TestException@WebCore@@6B@");
#else
        void* expectedVTablePointer = &_ZTVN7WebCore13TestExceptionE[2];
#endif

        // If you hit this assertion you either have a use after free bug, or
        // TestException has subclasses. If TestException has subclasses that get passed
        // to toJS() we currently require TestException you to opt out of binding hardening
        // by adding the SkipVTableValidation attribute to the interface IDL definition
        RELEASE_ASSERT(actualVTablePointer == expectedVTablePointer);
    }
}
#endif
JSC::JSValue toJSNewlyCreated(JSC::JSGlobalObject*, JSDOMGlobalObject* globalObject, Ref<TestException>&& impl)
{
#if ENABLE(BINDING_INTEGRITY)
    verifyVTable<TestException>(impl.ptr());
#endif
    return createWrapper<TestException>(globalObject, WTFMove(impl));
}

JSC::JSValue toJS(JSC::JSGlobalObject* lexicalGlobalObject, JSDOMGlobalObject* globalObject, TestException& impl)
{
    return wrap(lexicalGlobalObject, globalObject, impl);
}

TestException* JSTestException::toWrapped(JSC::VM&, JSC::JSValue value)
{
    if (auto* wrapper = jsDynamicCast<JSTestException*>(value))
        return &wrapper->wrapped();
    return nullptr;
}

}

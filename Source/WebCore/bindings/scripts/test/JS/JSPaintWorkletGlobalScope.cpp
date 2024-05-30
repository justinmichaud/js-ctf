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
#include "JSPaintWorkletGlobalScope.h"

#include "ActiveDOMObject.h"
#include "ExtendedDOMClientIsoSubspaces.h"
#include "ExtendedDOMIsoSubspaces.h"
#include "JSDOMAttribute.h"
#include "JSDOMBinding.h"
#include "JSDOMConstructorNotConstructable.h"
#include "JSDOMExceptionHandling.h"
#include "JSDOMGlobalObjectInlines.h"
#include "JSDOMWrapperCache.h"
#include "JSExposedStar.h"
#include "JSPaintWorkletGlobalScope.h"
#include "PaintWorkletGlobalScope.h"
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

// Attributes

static JSC_DECLARE_CUSTOM_GETTER(jsPaintWorkletGlobalScopeConstructor);
static JSC_DECLARE_CUSTOM_GETTER(jsPaintWorkletGlobalScope_ExposedStarConstructor);
static JSC_DECLARE_CUSTOM_GETTER(jsPaintWorkletGlobalScope_PaintWorkletGlobalScopeConstructor);

using JSPaintWorkletGlobalScopeDOMConstructor = JSDOMConstructorNotConstructable<JSPaintWorkletGlobalScope>;

/* Hash table */

static const struct CompactHashIndex JSPaintWorkletGlobalScopeTableIndex[4] = {
    { -1, -1 },
    { 1, -1 },
    { -1, -1 },
    { 0, -1 },
};


static const HashTableValue JSPaintWorkletGlobalScopeTableValues[] =
{
    { "ExposedStar"_s, static_cast<unsigned>(JSC::PropertyAttribute::DontEnum), NoIntrinsic, { HashTableValue::GetterSetterType, jsPaintWorkletGlobalScope_ExposedStarConstructor, 0 } },
    { "PaintWorkletGlobalScope"_s, static_cast<unsigned>(JSC::PropertyAttribute::DontEnum), NoIntrinsic, { HashTableValue::GetterSetterType, jsPaintWorkletGlobalScope_PaintWorkletGlobalScopeConstructor, 0 } },
};

static const HashTable JSPaintWorkletGlobalScopeTable = { 2, 3, static_cast<uint8_t>(static_cast<unsigned>(JSC::PropertyAttribute::DontEnum)), JSPaintWorkletGlobalScope::info(), JSPaintWorkletGlobalScopeTableValues, JSPaintWorkletGlobalScopeTableIndex };
template<> const ClassInfo JSPaintWorkletGlobalScopeDOMConstructor::s_info = { "PaintWorkletGlobalScope"_s, &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSPaintWorkletGlobalScopeDOMConstructor) };

template<> JSValue JSPaintWorkletGlobalScopeDOMConstructor::prototypeForStructure(JSC::VM& vm, const JSDOMGlobalObject& globalObject)
{
    return JSWorkletGlobalScope::getConstructor(vm, &globalObject);
}

template<> void JSPaintWorkletGlobalScopeDOMConstructor::initializeProperties(VM& vm, JSDOMGlobalObject& globalObject)
{
    putDirect(vm, vm.propertyNames->length, jsNumber(0), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    JSString* nameString = jsNontrivialString(vm, "PaintWorkletGlobalScope"_s);
    m_originalName.set(vm, this, nameString);
    putDirect(vm, vm.propertyNames->name, nameString, JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    putDirect(vm, vm.propertyNames->prototype, globalObject.getPrototypeDirect(), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum | JSC::PropertyAttribute::DontDelete);
}

/* Hash table for prototype */

static const struct CompactHashIndex JSPaintWorkletGlobalScopePrototypeTableIndex[2] = {
    { -1, -1 },
    { 0, -1 },
};


static const HashTableValue JSPaintWorkletGlobalScopePrototypeTableValues[] =
{
    { "constructor"_s, static_cast<unsigned>(PropertyAttribute::DontEnum), NoIntrinsic, { HashTableValue::GetterSetterType, jsPaintWorkletGlobalScopeConstructor, 0 } },
};

static const HashTable JSPaintWorkletGlobalScopePrototypeTable = { 1, 1, static_cast<uint8_t>(static_cast<unsigned>(PropertyAttribute::DontEnum)), JSPaintWorkletGlobalScope::info(), JSPaintWorkletGlobalScopePrototypeTableValues, JSPaintWorkletGlobalScopePrototypeTableIndex };
const ClassInfo JSPaintWorkletGlobalScopePrototype::s_info = { "PaintWorkletGlobalScope"_s, &Base::s_info, &JSPaintWorkletGlobalScopePrototypeTable, nullptr, CREATE_METHOD_TABLE(JSPaintWorkletGlobalScopePrototype) };

void JSPaintWorkletGlobalScopePrototype::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    reifyStaticProperties(vm, JSPaintWorkletGlobalScope::info(), JSPaintWorkletGlobalScopePrototypeTableValues, *this);
    JSC_TO_STRING_TAG_WITHOUT_TRANSITION();
}

const ClassInfo JSPaintWorkletGlobalScope::s_info = { "PaintWorkletGlobalScope"_s, &Base::s_info, &JSPaintWorkletGlobalScopeTable, nullptr, CREATE_METHOD_TABLE(JSPaintWorkletGlobalScope) };

JSPaintWorkletGlobalScope::JSPaintWorkletGlobalScope(VM& vm, Structure* structure, Ref<PaintWorkletGlobalScope>&& impl)
    : JSWorkletGlobalScope(vm, structure, WTFMove(impl))
{
}

Ref<PaintWorkletGlobalScope> JSPaintWorkletGlobalScope::protectedWrapped() const
{
    return wrapped();
}

static_assert(!std::is_base_of<ActiveDOMObject, PaintWorkletGlobalScope>::value, "Interface is not marked as [ActiveDOMObject] even though implementation class subclasses ActiveDOMObject.");

#if ASSERT_ENABLED
void JSPaintWorkletGlobalScope::finishCreation(VM& vm, JSGlobalProxy* proxy)
{
    Base::finishCreation(vm, proxy);

}
#endif

JSValue JSPaintWorkletGlobalScope::getConstructor(VM& vm, const JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSPaintWorkletGlobalScopeDOMConstructor, DOMConstructorID::PaintWorkletGlobalScope>(vm, *jsCast<const JSDOMGlobalObject*>(globalObject));
}

JSC_DEFINE_CUSTOM_GETTER(jsPaintWorkletGlobalScopeConstructor, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName))
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* prototype = jsDynamicCast<JSPaintWorkletGlobalScopePrototype*>(JSValue::decode(thisValue));
    if (UNLIKELY(!prototype))
        return throwVMTypeError(lexicalGlobalObject, throwScope);
    return JSValue::encode(JSPaintWorkletGlobalScope::getConstructor(vm, prototype->globalObject()));
}

static inline JSValue jsPaintWorkletGlobalScope_ExposedStarConstructorGetter(JSGlobalObject& lexicalGlobalObject, JSPaintWorkletGlobalScope& thisObject)
{
    UNUSED_PARAM(lexicalGlobalObject);
    return JSExposedStar::getConstructor(JSC::getVM(&lexicalGlobalObject), &thisObject);
}

JSC_DEFINE_CUSTOM_GETTER(jsPaintWorkletGlobalScope_ExposedStarConstructor, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<JSPaintWorkletGlobalScope>::get<jsPaintWorkletGlobalScope_ExposedStarConstructorGetter>(*lexicalGlobalObject, thisValue, attributeName);
}

static inline JSValue jsPaintWorkletGlobalScope_PaintWorkletGlobalScopeConstructorGetter(JSGlobalObject& lexicalGlobalObject, JSPaintWorkletGlobalScope& thisObject)
{
    UNUSED_PARAM(lexicalGlobalObject);
    return JSPaintWorkletGlobalScope::getConstructor(JSC::getVM(&lexicalGlobalObject), &thisObject);
}

JSC_DEFINE_CUSTOM_GETTER(jsPaintWorkletGlobalScope_PaintWorkletGlobalScopeConstructor, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<JSPaintWorkletGlobalScope>::get<jsPaintWorkletGlobalScope_PaintWorkletGlobalScopeConstructorGetter>(*lexicalGlobalObject, thisValue, attributeName);
}

JSC::GCClient::IsoSubspace* JSPaintWorkletGlobalScope::subspaceForImpl(JSC::VM& vm)
{
    return WebCore::subspaceForImpl<JSPaintWorkletGlobalScope, UseCustomHeapCellType::Yes>(vm,
        [] (auto& spaces) { return spaces.m_clientSubspaceForPaintWorkletGlobalScope.get(); },
        [] (auto& spaces, auto&& space) { spaces.m_clientSubspaceForPaintWorkletGlobalScope = std::forward<decltype(space)>(space); },
        [] (auto& spaces) { return spaces.m_subspaceForPaintWorkletGlobalScope.get(); },
        [] (auto& spaces, auto&& space) { spaces.m_subspaceForPaintWorkletGlobalScope = std::forward<decltype(space)>(space); },
        [] (auto& server) -> JSC::HeapCellType& { return server.m_heapCellTypeForJSPaintWorkletGlobalScope; }
    );
}

void JSPaintWorkletGlobalScope::analyzeHeap(JSCell* cell, HeapAnalyzer& analyzer)
{
    auto* thisObject = jsCast<JSPaintWorkletGlobalScope*>(cell);
    analyzer.setWrappedObjectForCell(cell, &thisObject->wrapped());
    if (thisObject->scriptExecutionContext())
        analyzer.setLabelForCell(cell, "url "_s + thisObject->scriptExecutionContext()->url().string());
    Base::analyzeHeap(cell, analyzer);
}


}

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

#if ENABLE(CONDITION)

#include "JSTestStandaloneEnumeration.h"

#include <JavaScriptCore/JSCInlines.h>
#include <JavaScriptCore/JSString.h>
#include <wtf/NeverDestroyed.h>
#include <wtf/SortedArrayMap.h>


namespace WebCore {
using namespace JSC;

String convertEnumerationToString(TestStandaloneEnumeration enumerationValue)
{
    static const NeverDestroyed<String> values[] = {
        MAKE_STATIC_STRING_IMPL("enumValue1"),
        MAKE_STATIC_STRING_IMPL("enumValue2"),
    };
    static_assert(static_cast<size_t>(TestStandaloneEnumeration::EnumValue1) == 0, "TestStandaloneEnumeration::EnumValue1 is not 0 as expected");
    static_assert(static_cast<size_t>(TestStandaloneEnumeration::EnumValue2) == 1, "TestStandaloneEnumeration::EnumValue2 is not 1 as expected");
    ASSERT(static_cast<size_t>(enumerationValue) < std::size(values));
    return values[static_cast<size_t>(enumerationValue)];
}

template<> JSString* convertEnumerationToJS(VM& vm, TestStandaloneEnumeration enumerationValue)
{
    return jsStringWithCache(vm, convertEnumerationToString(enumerationValue));
}

template<> std::optional<TestStandaloneEnumeration> parseEnumerationFromString<TestStandaloneEnumeration>(const String& stringValue)
{
    static constexpr std::pair<ComparableASCIILiteral, TestStandaloneEnumeration> mappings[] = {
        { "enumValue1", TestStandaloneEnumeration::EnumValue1 },
        { "enumValue2", TestStandaloneEnumeration::EnumValue2 },
    };
    static constexpr SortedArrayMap enumerationMapping { mappings };
    if (auto* enumerationValue = enumerationMapping.tryGet(stringValue); LIKELY(enumerationValue))
        return *enumerationValue;
    return std::nullopt;
}

template<> std::optional<TestStandaloneEnumeration> parseEnumeration<TestStandaloneEnumeration>(JSGlobalObject& lexicalGlobalObject, JSValue value)
{
    return parseEnumerationFromString<TestStandaloneEnumeration>(value.toWTFString(&lexicalGlobalObject));
}

template<> ASCIILiteral expectedEnumerationValues<TestStandaloneEnumeration>()
{
    return "\"enumValue1\", \"enumValue2\""_s;
}

} // namespace WebCore

#endif // ENABLE(CONDITION)

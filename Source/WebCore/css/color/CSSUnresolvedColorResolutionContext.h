/*
 * Copyright (C) 2023 Apple Inc. All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include "Color.h"
#include "StyleColor.h"
#include <wtf/Forward.h>
#include <wtf/OptionSet.h>

namespace WebCore {

namespace Style {
enum class ForVisitedLink : bool;
}

enum class CSSUnresolvedLightDarkAppearance : bool;

struct CSSUnresolvedColorResolutionContext {
    CSSUnresolvedColorResolutionContext();
    ~CSSUnresolvedColorResolutionContext();

    Style::ForVisitedLink forVisitedLink;

    // Colors to use that usually get resolved dynamically using Document & RenderStyle.
    Color currentColor;              // For CSSValueCurrentcolor
    Color internalDocumentTextColor; // For CSSValueInternalDocumentTextColor
    Color webkitLink;                // For CSSValueWebkitLink [Style::ForVisitedLink::No]
    Color webkitLinkVisited;         // For CSSValueWebkitLink [Style::ForVisitedLink::Yes]
    Color webkitActiveLink;          // For CSSValueWebkitActivelink
    Color webkitFocusRingColor;      // For CSSValueWebkitFocusRingColor

    // Options to pass when resolving any other keyword with StyleColor::colorFromKeyword()
    OptionSet<StyleColorOptions> keywordOptions;

    // Appearance used to select from a light-dark() color function.
    // If unset, light-dark() colors will return the invalid Color.
    std::optional<CSSUnresolvedLightDarkAppearance> appearance;
};

} // namespace WebCore

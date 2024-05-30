/*
 * Copyright (C) 2020 Sony Interactive Entertainment Inc.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "WebProcessMain.h"

#include <dlfcn.h>
#include <process-initialization/nk-webprocess.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void loadLibraryOrExit(const char* name)
{
    if (!dlopen(name, RTLD_NOW)) {
        fprintf(stderr, "Failed to load %s.\n", name);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        fprintf(stderr, "Unexpected argument count %d\n", argc);
        exit(EXIT_FAILURE);
    }

    loadLibraryOrExit(ICU_LOAD_AT);
    loadLibraryOrExit(PNG_LOAD_AT);
#if defined(LCMS2_LOAD_AT)
    loadLibraryOrExit(LCMS2_LOAD_AT);
#endif
#if defined(JPEG_LOAD_AT)
    loadLibraryOrExit(JPEG_LOAD_AT);
#endif 
#if defined(WebP_LOAD_AT)
    loadLibraryOrExit(WebP_LOAD_AT);
#endif
#if defined(Brotli_LOAD_AT)
    loadLibraryOrExit(Brotli_LOAD_AT);
#endif
#if defined(JPEGXL_LOAD_AT)
    loadLibraryOrExit(JPEGXL_LOAD_AT);
#endif
    loadLibraryOrExit(Freetype_LOAD_AT);
    loadLibraryOrExit(Fontconfig_LOAD_AT);
    loadLibraryOrExit(HarfBuzz_LOAD_AT);
#if USE(CAIRO) && defined(Cairo_LOAD_AT)
    loadLibraryOrExit(Cairo_LOAD_AT);
#endif
#if defined(LibPSL_LOAD_AT)
    loadLibraryOrExit(LibPSL_LOAD_AT);
#endif
#if defined(LibXml2_LOAD_AT)
    loadLibraryOrExit(LibXml2_LOAD_AT);
#endif
    loadLibraryOrExit(WebKitRequirements_LOAD_AT);
#if defined(WPE_LOAD_AT)
    loadLibraryOrExit(WPE_LOAD_AT);
#endif
#if !ENABLE(STATIC_JSC)
    loadLibraryOrExit("libJavaScriptCore");
#endif
    loadLibraryOrExit("libWebKit");

    char* coreProcessIdentifier = argv[1];

    char connectionIdentifier[16];
    snprintf(connectionIdentifier, sizeof(connectionIdentifier), "%d", PlayStation::getConnectionIdentifier());

    char program[] = "dummy";
    char* internalArgv[] = {
        program,
        coreProcessIdentifier,
        connectionIdentifier,
        0
    };
    return WebKit::WebProcessMain(sizeof(internalArgv) / sizeof(char*), internalArgv);
}

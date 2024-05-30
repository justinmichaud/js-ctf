// GENERATED FILE - DO NOT EDIT.
// Generated by generate_loader.py using data from egl.xml and egl_angle_ext.xml.
//
// Copyright 2018 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// egl_loader_autogen.cpp:
//   Simple EGL function loader.

#include "egl_loader_autogen.h"

extern "C" {
ANGLE_UTIL_EXPORT PFNEGLCHOOSECONFIGPROC l_eglChooseConfig;
ANGLE_UTIL_EXPORT PFNEGLCOPYBUFFERSPROC l_eglCopyBuffers;
ANGLE_UTIL_EXPORT PFNEGLCREATECONTEXTPROC l_eglCreateContext;
ANGLE_UTIL_EXPORT PFNEGLCREATEPBUFFERSURFACEPROC l_eglCreatePbufferSurface;
ANGLE_UTIL_EXPORT PFNEGLCREATEPIXMAPSURFACEPROC l_eglCreatePixmapSurface;
ANGLE_UTIL_EXPORT PFNEGLCREATEWINDOWSURFACEPROC l_eglCreateWindowSurface;
ANGLE_UTIL_EXPORT PFNEGLDESTROYCONTEXTPROC l_eglDestroyContext;
ANGLE_UTIL_EXPORT PFNEGLDESTROYSURFACEPROC l_eglDestroySurface;
ANGLE_UTIL_EXPORT PFNEGLGETCONFIGATTRIBPROC l_eglGetConfigAttrib;
ANGLE_UTIL_EXPORT PFNEGLGETCONFIGSPROC l_eglGetConfigs;
ANGLE_UTIL_EXPORT PFNEGLGETCURRENTDISPLAYPROC l_eglGetCurrentDisplay;
ANGLE_UTIL_EXPORT PFNEGLGETCURRENTSURFACEPROC l_eglGetCurrentSurface;
ANGLE_UTIL_EXPORT PFNEGLGETDISPLAYPROC l_eglGetDisplay;
ANGLE_UTIL_EXPORT PFNEGLGETERRORPROC l_eglGetError;
ANGLE_UTIL_EXPORT PFNEGLGETPROCADDRESSPROC l_eglGetProcAddress;
ANGLE_UTIL_EXPORT PFNEGLINITIALIZEPROC l_eglInitialize;
ANGLE_UTIL_EXPORT PFNEGLMAKECURRENTPROC l_eglMakeCurrent;
ANGLE_UTIL_EXPORT PFNEGLQUERYCONTEXTPROC l_eglQueryContext;
ANGLE_UTIL_EXPORT PFNEGLQUERYSTRINGPROC l_eglQueryString;
ANGLE_UTIL_EXPORT PFNEGLQUERYSURFACEPROC l_eglQuerySurface;
ANGLE_UTIL_EXPORT PFNEGLSWAPBUFFERSPROC l_eglSwapBuffers;
ANGLE_UTIL_EXPORT PFNEGLTERMINATEPROC l_eglTerminate;
ANGLE_UTIL_EXPORT PFNEGLWAITGLPROC l_eglWaitGL;
ANGLE_UTIL_EXPORT PFNEGLWAITNATIVEPROC l_eglWaitNative;
ANGLE_UTIL_EXPORT PFNEGLBINDTEXIMAGEPROC l_eglBindTexImage;
ANGLE_UTIL_EXPORT PFNEGLRELEASETEXIMAGEPROC l_eglReleaseTexImage;
ANGLE_UTIL_EXPORT PFNEGLSURFACEATTRIBPROC l_eglSurfaceAttrib;
ANGLE_UTIL_EXPORT PFNEGLSWAPINTERVALPROC l_eglSwapInterval;
ANGLE_UTIL_EXPORT PFNEGLBINDAPIPROC l_eglBindAPI;
ANGLE_UTIL_EXPORT PFNEGLQUERYAPIPROC l_eglQueryAPI;
ANGLE_UTIL_EXPORT PFNEGLCREATEPBUFFERFROMCLIENTBUFFERPROC l_eglCreatePbufferFromClientBuffer;
ANGLE_UTIL_EXPORT PFNEGLRELEASETHREADPROC l_eglReleaseThread;
ANGLE_UTIL_EXPORT PFNEGLWAITCLIENTPROC l_eglWaitClient;
ANGLE_UTIL_EXPORT PFNEGLGETCURRENTCONTEXTPROC l_eglGetCurrentContext;
ANGLE_UTIL_EXPORT PFNEGLCREATESYNCPROC l_eglCreateSync;
ANGLE_UTIL_EXPORT PFNEGLDESTROYSYNCPROC l_eglDestroySync;
ANGLE_UTIL_EXPORT PFNEGLCLIENTWAITSYNCPROC l_eglClientWaitSync;
ANGLE_UTIL_EXPORT PFNEGLGETSYNCATTRIBPROC l_eglGetSyncAttrib;
ANGLE_UTIL_EXPORT PFNEGLCREATEIMAGEPROC l_eglCreateImage;
ANGLE_UTIL_EXPORT PFNEGLDESTROYIMAGEPROC l_eglDestroyImage;
ANGLE_UTIL_EXPORT PFNEGLGETPLATFORMDISPLAYPROC l_eglGetPlatformDisplay;
ANGLE_UTIL_EXPORT PFNEGLCREATEPLATFORMWINDOWSURFACEPROC l_eglCreatePlatformWindowSurface;
ANGLE_UTIL_EXPORT PFNEGLCREATEPLATFORMPIXMAPSURFACEPROC l_eglCreatePlatformPixmapSurface;
ANGLE_UTIL_EXPORT PFNEGLWAITSYNCPROC l_eglWaitSync;
ANGLE_UTIL_EXPORT PFNEGLSETBLOBCACHEFUNCSANDROIDPROC l_eglSetBlobCacheFuncsANDROID;
ANGLE_UTIL_EXPORT PFNEGLCREATENATIVECLIENTBUFFERANDROIDPROC l_eglCreateNativeClientBufferANDROID;
ANGLE_UTIL_EXPORT PFNEGLGETCOMPOSITORTIMINGANDROIDPROC l_eglGetCompositorTimingANDROID;
ANGLE_UTIL_EXPORT PFNEGLGETCOMPOSITORTIMINGSUPPORTEDANDROIDPROC
    l_eglGetCompositorTimingSupportedANDROID;
ANGLE_UTIL_EXPORT PFNEGLGETFRAMETIMESTAMPSUPPORTEDANDROIDPROC
    l_eglGetFrameTimestampSupportedANDROID;
ANGLE_UTIL_EXPORT PFNEGLGETFRAMETIMESTAMPSANDROIDPROC l_eglGetFrameTimestampsANDROID;
ANGLE_UTIL_EXPORT PFNEGLGETNEXTFRAMEIDANDROIDPROC l_eglGetNextFrameIdANDROID;
ANGLE_UTIL_EXPORT PFNEGLGETNATIVECLIENTBUFFERANDROIDPROC l_eglGetNativeClientBufferANDROID;
ANGLE_UTIL_EXPORT PFNEGLDUPNATIVEFENCEFDANDROIDPROC l_eglDupNativeFenceFDANDROID;
ANGLE_UTIL_EXPORT PFNEGLPRESENTATIONTIMEANDROIDPROC l_eglPresentationTimeANDROID;
ANGLE_UTIL_EXPORT PFNEGLCREATEDEVICEANGLEPROC l_eglCreateDeviceANGLE;
ANGLE_UTIL_EXPORT PFNEGLRELEASEDEVICEANGLEPROC l_eglReleaseDeviceANGLE;
ANGLE_UTIL_EXPORT PFNEGLACQUIREEXTERNALCONTEXTANGLEPROC l_eglAcquireExternalContextANGLE;
ANGLE_UTIL_EXPORT PFNEGLRELEASEEXTERNALCONTEXTANGLEPROC l_eglReleaseExternalContextANGLE;
ANGLE_UTIL_EXPORT PFNEGLQUERYDISPLAYATTRIBANGLEPROC l_eglQueryDisplayAttribANGLE;
ANGLE_UTIL_EXPORT PFNEGLQUERYSTRINGIANGLEPROC l_eglQueryStringiANGLE;
ANGLE_UTIL_EXPORT PFNEGLCOPYMETALSHAREDEVENTANGLEPROC l_eglCopyMetalSharedEventANGLE;
ANGLE_UTIL_EXPORT PFNEGLSETVALIDATIONENABLEDANGLEPROC l_eglSetValidationEnabledANGLE;
ANGLE_UTIL_EXPORT PFNEGLFORCEGPUSWITCHANGLEPROC l_eglForceGPUSwitchANGLE;
ANGLE_UTIL_EXPORT PFNEGLHANDLEGPUSWITCHANGLEPROC l_eglHandleGPUSwitchANGLE;
ANGLE_UTIL_EXPORT PFNEGLREACQUIREHIGHPOWERGPUANGLEPROC l_eglReacquireHighPowerGPUANGLE;
ANGLE_UTIL_EXPORT PFNEGLRELEASEHIGHPOWERGPUANGLEPROC l_eglReleaseHighPowerGPUANGLE;
ANGLE_UTIL_EXPORT PFNEGLPREPARESWAPBUFFERSANGLEPROC l_eglPrepareSwapBuffersANGLE;
ANGLE_UTIL_EXPORT PFNEGLPROGRAMCACHEGETATTRIBANGLEPROC l_eglProgramCacheGetAttribANGLE;
ANGLE_UTIL_EXPORT PFNEGLPROGRAMCACHEPOPULATEANGLEPROC l_eglProgramCachePopulateANGLE;
ANGLE_UTIL_EXPORT PFNEGLPROGRAMCACHEQUERYANGLEPROC l_eglProgramCacheQueryANGLE;
ANGLE_UTIL_EXPORT PFNEGLPROGRAMCACHERESIZEANGLEPROC l_eglProgramCacheResizeANGLE;
ANGLE_UTIL_EXPORT PFNEGLQUERYSURFACEPOINTERANGLEPROC l_eglQuerySurfacePointerANGLE;
ANGLE_UTIL_EXPORT PFNEGLCREATESTREAMPRODUCERD3DTEXTUREANGLEPROC
    l_eglCreateStreamProducerD3DTextureANGLE;
ANGLE_UTIL_EXPORT PFNEGLSTREAMPOSTD3DTEXTUREANGLEPROC l_eglStreamPostD3DTextureANGLE;
ANGLE_UTIL_EXPORT PFNEGLSWAPBUFFERSWITHFRAMETOKENANGLEPROC l_eglSwapBuffersWithFrameTokenANGLE;
ANGLE_UTIL_EXPORT PFNEGLGETMSCRATEANGLEPROC l_eglGetMscRateANGLE;
ANGLE_UTIL_EXPORT PFNEGLEXPORTVKIMAGEANGLEPROC l_eglExportVkImageANGLE;
ANGLE_UTIL_EXPORT PFNEGLWAITUNTILWORKSCHEDULEDANGLEPROC l_eglWaitUntilWorkScheduledANGLE;
ANGLE_UTIL_EXPORT PFNEGLGETSYNCVALUESCHROMIUMPROC l_eglGetSyncValuesCHROMIUM;
ANGLE_UTIL_EXPORT PFNEGLQUERYDEVICEATTRIBEXTPROC l_eglQueryDeviceAttribEXT;
ANGLE_UTIL_EXPORT PFNEGLQUERYDEVICESTRINGEXTPROC l_eglQueryDeviceStringEXT;
ANGLE_UTIL_EXPORT PFNEGLQUERYDISPLAYATTRIBEXTPROC l_eglQueryDisplayAttribEXT;
ANGLE_UTIL_EXPORT PFNEGLQUERYDMABUFFORMATSEXTPROC l_eglQueryDmaBufFormatsEXT;
ANGLE_UTIL_EXPORT PFNEGLQUERYDMABUFMODIFIERSEXTPROC l_eglQueryDmaBufModifiersEXT;
ANGLE_UTIL_EXPORT PFNEGLCREATEPLATFORMPIXMAPSURFACEEXTPROC l_eglCreatePlatformPixmapSurfaceEXT;
ANGLE_UTIL_EXPORT PFNEGLCREATEPLATFORMWINDOWSURFACEEXTPROC l_eglCreatePlatformWindowSurfaceEXT;
ANGLE_UTIL_EXPORT PFNEGLGETPLATFORMDISPLAYEXTPROC l_eglGetPlatformDisplayEXT;
ANGLE_UTIL_EXPORT PFNEGLDEBUGMESSAGECONTROLKHRPROC l_eglDebugMessageControlKHR;
ANGLE_UTIL_EXPORT PFNEGLLABELOBJECTKHRPROC l_eglLabelObjectKHR;
ANGLE_UTIL_EXPORT PFNEGLQUERYDEBUGKHRPROC l_eglQueryDebugKHR;
ANGLE_UTIL_EXPORT PFNEGLCLIENTWAITSYNCKHRPROC l_eglClientWaitSyncKHR;
ANGLE_UTIL_EXPORT PFNEGLCREATESYNCKHRPROC l_eglCreateSyncKHR;
ANGLE_UTIL_EXPORT PFNEGLDESTROYSYNCKHRPROC l_eglDestroySyncKHR;
ANGLE_UTIL_EXPORT PFNEGLGETSYNCATTRIBKHRPROC l_eglGetSyncAttribKHR;
ANGLE_UTIL_EXPORT PFNEGLCREATEIMAGEKHRPROC l_eglCreateImageKHR;
ANGLE_UTIL_EXPORT PFNEGLDESTROYIMAGEKHRPROC l_eglDestroyImageKHR;
ANGLE_UTIL_EXPORT PFNEGLLOCKSURFACEKHRPROC l_eglLockSurfaceKHR;
ANGLE_UTIL_EXPORT PFNEGLQUERYSURFACE64KHRPROC l_eglQuerySurface64KHR;
ANGLE_UTIL_EXPORT PFNEGLUNLOCKSURFACEKHRPROC l_eglUnlockSurfaceKHR;
ANGLE_UTIL_EXPORT PFNEGLSETDAMAGEREGIONKHRPROC l_eglSetDamageRegionKHR;
ANGLE_UTIL_EXPORT PFNEGLSIGNALSYNCKHRPROC l_eglSignalSyncKHR;
ANGLE_UTIL_EXPORT PFNEGLCREATESTREAMKHRPROC l_eglCreateStreamKHR;
ANGLE_UTIL_EXPORT PFNEGLDESTROYSTREAMKHRPROC l_eglDestroyStreamKHR;
ANGLE_UTIL_EXPORT PFNEGLQUERYSTREAMKHRPROC l_eglQueryStreamKHR;
ANGLE_UTIL_EXPORT PFNEGLQUERYSTREAMU64KHRPROC l_eglQueryStreamu64KHR;
ANGLE_UTIL_EXPORT PFNEGLSTREAMATTRIBKHRPROC l_eglStreamAttribKHR;
ANGLE_UTIL_EXPORT PFNEGLSTREAMCONSUMERACQUIREKHRPROC l_eglStreamConsumerAcquireKHR;
ANGLE_UTIL_EXPORT PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALKHRPROC
    l_eglStreamConsumerGLTextureExternalKHR;
ANGLE_UTIL_EXPORT PFNEGLSTREAMCONSUMERRELEASEKHRPROC l_eglStreamConsumerReleaseKHR;
ANGLE_UTIL_EXPORT PFNEGLSWAPBUFFERSWITHDAMAGEKHRPROC l_eglSwapBuffersWithDamageKHR;
ANGLE_UTIL_EXPORT PFNEGLWAITSYNCKHRPROC l_eglWaitSyncKHR;
ANGLE_UTIL_EXPORT PFNEGLPOSTSUBBUFFERNVPROC l_eglPostSubBufferNV;
ANGLE_UTIL_EXPORT PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALATTRIBSNVPROC
    l_eglStreamConsumerGLTextureExternalAttribsNV;

void LoadUtilEGL(LoadProc loadProc)
{
    l_eglChooseConfig  = reinterpret_cast<PFNEGLCHOOSECONFIGPROC>(loadProc("eglChooseConfig"));
    l_eglCopyBuffers   = reinterpret_cast<PFNEGLCOPYBUFFERSPROC>(loadProc("eglCopyBuffers"));
    l_eglCreateContext = reinterpret_cast<PFNEGLCREATECONTEXTPROC>(loadProc("eglCreateContext"));
    l_eglCreatePbufferSurface =
        reinterpret_cast<PFNEGLCREATEPBUFFERSURFACEPROC>(loadProc("eglCreatePbufferSurface"));
    l_eglCreatePixmapSurface =
        reinterpret_cast<PFNEGLCREATEPIXMAPSURFACEPROC>(loadProc("eglCreatePixmapSurface"));
    l_eglCreateWindowSurface =
        reinterpret_cast<PFNEGLCREATEWINDOWSURFACEPROC>(loadProc("eglCreateWindowSurface"));
    l_eglDestroyContext = reinterpret_cast<PFNEGLDESTROYCONTEXTPROC>(loadProc("eglDestroyContext"));
    l_eglDestroySurface = reinterpret_cast<PFNEGLDESTROYSURFACEPROC>(loadProc("eglDestroySurface"));
    l_eglGetConfigAttrib =
        reinterpret_cast<PFNEGLGETCONFIGATTRIBPROC>(loadProc("eglGetConfigAttrib"));
    l_eglGetConfigs = reinterpret_cast<PFNEGLGETCONFIGSPROC>(loadProc("eglGetConfigs"));
    l_eglGetCurrentDisplay =
        reinterpret_cast<PFNEGLGETCURRENTDISPLAYPROC>(loadProc("eglGetCurrentDisplay"));
    l_eglGetCurrentSurface =
        reinterpret_cast<PFNEGLGETCURRENTSURFACEPROC>(loadProc("eglGetCurrentSurface"));
    l_eglGetDisplay     = reinterpret_cast<PFNEGLGETDISPLAYPROC>(loadProc("eglGetDisplay"));
    l_eglGetError       = reinterpret_cast<PFNEGLGETERRORPROC>(loadProc("eglGetError"));
    l_eglGetProcAddress = reinterpret_cast<PFNEGLGETPROCADDRESSPROC>(loadProc("eglGetProcAddress"));
    l_eglInitialize     = reinterpret_cast<PFNEGLINITIALIZEPROC>(loadProc("eglInitialize"));
    l_eglMakeCurrent    = reinterpret_cast<PFNEGLMAKECURRENTPROC>(loadProc("eglMakeCurrent"));
    l_eglQueryContext   = reinterpret_cast<PFNEGLQUERYCONTEXTPROC>(loadProc("eglQueryContext"));
    l_eglQueryString    = reinterpret_cast<PFNEGLQUERYSTRINGPROC>(loadProc("eglQueryString"));
    l_eglQuerySurface   = reinterpret_cast<PFNEGLQUERYSURFACEPROC>(loadProc("eglQuerySurface"));
    l_eglSwapBuffers    = reinterpret_cast<PFNEGLSWAPBUFFERSPROC>(loadProc("eglSwapBuffers"));
    l_eglTerminate      = reinterpret_cast<PFNEGLTERMINATEPROC>(loadProc("eglTerminate"));
    l_eglWaitGL         = reinterpret_cast<PFNEGLWAITGLPROC>(loadProc("eglWaitGL"));
    l_eglWaitNative     = reinterpret_cast<PFNEGLWAITNATIVEPROC>(loadProc("eglWaitNative"));
    l_eglBindTexImage   = reinterpret_cast<PFNEGLBINDTEXIMAGEPROC>(loadProc("eglBindTexImage"));
    l_eglReleaseTexImage =
        reinterpret_cast<PFNEGLRELEASETEXIMAGEPROC>(loadProc("eglReleaseTexImage"));
    l_eglSurfaceAttrib = reinterpret_cast<PFNEGLSURFACEATTRIBPROC>(loadProc("eglSurfaceAttrib"));
    l_eglSwapInterval  = reinterpret_cast<PFNEGLSWAPINTERVALPROC>(loadProc("eglSwapInterval"));
    l_eglBindAPI       = reinterpret_cast<PFNEGLBINDAPIPROC>(loadProc("eglBindAPI"));
    l_eglQueryAPI      = reinterpret_cast<PFNEGLQUERYAPIPROC>(loadProc("eglQueryAPI"));
    l_eglCreatePbufferFromClientBuffer = reinterpret_cast<PFNEGLCREATEPBUFFERFROMCLIENTBUFFERPROC>(
        loadProc("eglCreatePbufferFromClientBuffer"));
    l_eglReleaseThread = reinterpret_cast<PFNEGLRELEASETHREADPROC>(loadProc("eglReleaseThread"));
    l_eglWaitClient    = reinterpret_cast<PFNEGLWAITCLIENTPROC>(loadProc("eglWaitClient"));
    l_eglGetCurrentContext =
        reinterpret_cast<PFNEGLGETCURRENTCONTEXTPROC>(loadProc("eglGetCurrentContext"));
    l_eglCreateSync     = reinterpret_cast<PFNEGLCREATESYNCPROC>(loadProc("eglCreateSync"));
    l_eglDestroySync    = reinterpret_cast<PFNEGLDESTROYSYNCPROC>(loadProc("eglDestroySync"));
    l_eglClientWaitSync = reinterpret_cast<PFNEGLCLIENTWAITSYNCPROC>(loadProc("eglClientWaitSync"));
    l_eglGetSyncAttrib  = reinterpret_cast<PFNEGLGETSYNCATTRIBPROC>(loadProc("eglGetSyncAttrib"));
    l_eglCreateImage    = reinterpret_cast<PFNEGLCREATEIMAGEPROC>(loadProc("eglCreateImage"));
    l_eglDestroyImage   = reinterpret_cast<PFNEGLDESTROYIMAGEPROC>(loadProc("eglDestroyImage"));
    l_eglGetPlatformDisplay =
        reinterpret_cast<PFNEGLGETPLATFORMDISPLAYPROC>(loadProc("eglGetPlatformDisplay"));
    l_eglCreatePlatformWindowSurface = reinterpret_cast<PFNEGLCREATEPLATFORMWINDOWSURFACEPROC>(
        loadProc("eglCreatePlatformWindowSurface"));
    l_eglCreatePlatformPixmapSurface = reinterpret_cast<PFNEGLCREATEPLATFORMPIXMAPSURFACEPROC>(
        loadProc("eglCreatePlatformPixmapSurface"));
    l_eglWaitSync                 = reinterpret_cast<PFNEGLWAITSYNCPROC>(loadProc("eglWaitSync"));
    l_eglSetBlobCacheFuncsANDROID = reinterpret_cast<PFNEGLSETBLOBCACHEFUNCSANDROIDPROC>(
        loadProc("eglSetBlobCacheFuncsANDROID"));
    l_eglCreateNativeClientBufferANDROID =
        reinterpret_cast<PFNEGLCREATENATIVECLIENTBUFFERANDROIDPROC>(
            loadProc("eglCreateNativeClientBufferANDROID"));
    l_eglGetCompositorTimingANDROID = reinterpret_cast<PFNEGLGETCOMPOSITORTIMINGANDROIDPROC>(
        loadProc("eglGetCompositorTimingANDROID"));
    l_eglGetCompositorTimingSupportedANDROID =
        reinterpret_cast<PFNEGLGETCOMPOSITORTIMINGSUPPORTEDANDROIDPROC>(
            loadProc("eglGetCompositorTimingSupportedANDROID"));
    l_eglGetFrameTimestampSupportedANDROID =
        reinterpret_cast<PFNEGLGETFRAMETIMESTAMPSUPPORTEDANDROIDPROC>(
            loadProc("eglGetFrameTimestampSupportedANDROID"));
    l_eglGetFrameTimestampsANDROID = reinterpret_cast<PFNEGLGETFRAMETIMESTAMPSANDROIDPROC>(
        loadProc("eglGetFrameTimestampsANDROID"));
    l_eglGetNextFrameIdANDROID =
        reinterpret_cast<PFNEGLGETNEXTFRAMEIDANDROIDPROC>(loadProc("eglGetNextFrameIdANDROID"));
    l_eglGetNativeClientBufferANDROID = reinterpret_cast<PFNEGLGETNATIVECLIENTBUFFERANDROIDPROC>(
        loadProc("eglGetNativeClientBufferANDROID"));
    l_eglDupNativeFenceFDANDROID =
        reinterpret_cast<PFNEGLDUPNATIVEFENCEFDANDROIDPROC>(loadProc("eglDupNativeFenceFDANDROID"));
    l_eglPresentationTimeANDROID =
        reinterpret_cast<PFNEGLPRESENTATIONTIMEANDROIDPROC>(loadProc("eglPresentationTimeANDROID"));
    l_eglCreateDeviceANGLE =
        reinterpret_cast<PFNEGLCREATEDEVICEANGLEPROC>(loadProc("eglCreateDeviceANGLE"));
    l_eglReleaseDeviceANGLE =
        reinterpret_cast<PFNEGLRELEASEDEVICEANGLEPROC>(loadProc("eglReleaseDeviceANGLE"));
    l_eglAcquireExternalContextANGLE = reinterpret_cast<PFNEGLACQUIREEXTERNALCONTEXTANGLEPROC>(
        loadProc("eglAcquireExternalContextANGLE"));
    l_eglReleaseExternalContextANGLE = reinterpret_cast<PFNEGLRELEASEEXTERNALCONTEXTANGLEPROC>(
        loadProc("eglReleaseExternalContextANGLE"));
    l_eglQueryDisplayAttribANGLE =
        reinterpret_cast<PFNEGLQUERYDISPLAYATTRIBANGLEPROC>(loadProc("eglQueryDisplayAttribANGLE"));
    l_eglQueryStringiANGLE =
        reinterpret_cast<PFNEGLQUERYSTRINGIANGLEPROC>(loadProc("eglQueryStringiANGLE"));
    l_eglCopyMetalSharedEventANGLE = reinterpret_cast<PFNEGLCOPYMETALSHAREDEVENTANGLEPROC>(
        loadProc("eglCopyMetalSharedEventANGLE"));
    l_eglSetValidationEnabledANGLE = reinterpret_cast<PFNEGLSETVALIDATIONENABLEDANGLEPROC>(
        loadProc("eglSetValidationEnabledANGLE"));
    l_eglForceGPUSwitchANGLE =
        reinterpret_cast<PFNEGLFORCEGPUSWITCHANGLEPROC>(loadProc("eglForceGPUSwitchANGLE"));
    l_eglHandleGPUSwitchANGLE =
        reinterpret_cast<PFNEGLHANDLEGPUSWITCHANGLEPROC>(loadProc("eglHandleGPUSwitchANGLE"));
    l_eglReacquireHighPowerGPUANGLE = reinterpret_cast<PFNEGLREACQUIREHIGHPOWERGPUANGLEPROC>(
        loadProc("eglReacquireHighPowerGPUANGLE"));
    l_eglReleaseHighPowerGPUANGLE = reinterpret_cast<PFNEGLRELEASEHIGHPOWERGPUANGLEPROC>(
        loadProc("eglReleaseHighPowerGPUANGLE"));
    l_eglPrepareSwapBuffersANGLE =
        reinterpret_cast<PFNEGLPREPARESWAPBUFFERSANGLEPROC>(loadProc("eglPrepareSwapBuffersANGLE"));
    l_eglProgramCacheGetAttribANGLE = reinterpret_cast<PFNEGLPROGRAMCACHEGETATTRIBANGLEPROC>(
        loadProc("eglProgramCacheGetAttribANGLE"));
    l_eglProgramCachePopulateANGLE = reinterpret_cast<PFNEGLPROGRAMCACHEPOPULATEANGLEPROC>(
        loadProc("eglProgramCachePopulateANGLE"));
    l_eglProgramCacheQueryANGLE =
        reinterpret_cast<PFNEGLPROGRAMCACHEQUERYANGLEPROC>(loadProc("eglProgramCacheQueryANGLE"));
    l_eglProgramCacheResizeANGLE =
        reinterpret_cast<PFNEGLPROGRAMCACHERESIZEANGLEPROC>(loadProc("eglProgramCacheResizeANGLE"));
    l_eglQuerySurfacePointerANGLE = reinterpret_cast<PFNEGLQUERYSURFACEPOINTERANGLEPROC>(
        loadProc("eglQuerySurfacePointerANGLE"));
    l_eglCreateStreamProducerD3DTextureANGLE =
        reinterpret_cast<PFNEGLCREATESTREAMPRODUCERD3DTEXTUREANGLEPROC>(
            loadProc("eglCreateStreamProducerD3DTextureANGLE"));
    l_eglStreamPostD3DTextureANGLE = reinterpret_cast<PFNEGLSTREAMPOSTD3DTEXTUREANGLEPROC>(
        loadProc("eglStreamPostD3DTextureANGLE"));
    l_eglSwapBuffersWithFrameTokenANGLE =
        reinterpret_cast<PFNEGLSWAPBUFFERSWITHFRAMETOKENANGLEPROC>(
            loadProc("eglSwapBuffersWithFrameTokenANGLE"));
    l_eglGetMscRateANGLE =
        reinterpret_cast<PFNEGLGETMSCRATEANGLEPROC>(loadProc("eglGetMscRateANGLE"));
    l_eglExportVkImageANGLE =
        reinterpret_cast<PFNEGLEXPORTVKIMAGEANGLEPROC>(loadProc("eglExportVkImageANGLE"));
    l_eglWaitUntilWorkScheduledANGLE = reinterpret_cast<PFNEGLWAITUNTILWORKSCHEDULEDANGLEPROC>(
        loadProc("eglWaitUntilWorkScheduledANGLE"));
    l_eglGetSyncValuesCHROMIUM =
        reinterpret_cast<PFNEGLGETSYNCVALUESCHROMIUMPROC>(loadProc("eglGetSyncValuesCHROMIUM"));
    l_eglQueryDeviceAttribEXT =
        reinterpret_cast<PFNEGLQUERYDEVICEATTRIBEXTPROC>(loadProc("eglQueryDeviceAttribEXT"));
    l_eglQueryDeviceStringEXT =
        reinterpret_cast<PFNEGLQUERYDEVICESTRINGEXTPROC>(loadProc("eglQueryDeviceStringEXT"));
    l_eglQueryDisplayAttribEXT =
        reinterpret_cast<PFNEGLQUERYDISPLAYATTRIBEXTPROC>(loadProc("eglQueryDisplayAttribEXT"));
    l_eglQueryDmaBufFormatsEXT =
        reinterpret_cast<PFNEGLQUERYDMABUFFORMATSEXTPROC>(loadProc("eglQueryDmaBufFormatsEXT"));
    l_eglQueryDmaBufModifiersEXT =
        reinterpret_cast<PFNEGLQUERYDMABUFMODIFIERSEXTPROC>(loadProc("eglQueryDmaBufModifiersEXT"));
    l_eglCreatePlatformPixmapSurfaceEXT =
        reinterpret_cast<PFNEGLCREATEPLATFORMPIXMAPSURFACEEXTPROC>(
            loadProc("eglCreatePlatformPixmapSurfaceEXT"));
    l_eglCreatePlatformWindowSurfaceEXT =
        reinterpret_cast<PFNEGLCREATEPLATFORMWINDOWSURFACEEXTPROC>(
            loadProc("eglCreatePlatformWindowSurfaceEXT"));
    l_eglGetPlatformDisplayEXT =
        reinterpret_cast<PFNEGLGETPLATFORMDISPLAYEXTPROC>(loadProc("eglGetPlatformDisplayEXT"));
    l_eglDebugMessageControlKHR =
        reinterpret_cast<PFNEGLDEBUGMESSAGECONTROLKHRPROC>(loadProc("eglDebugMessageControlKHR"));
    l_eglLabelObjectKHR = reinterpret_cast<PFNEGLLABELOBJECTKHRPROC>(loadProc("eglLabelObjectKHR"));
    l_eglQueryDebugKHR  = reinterpret_cast<PFNEGLQUERYDEBUGKHRPROC>(loadProc("eglQueryDebugKHR"));
    l_eglClientWaitSyncKHR =
        reinterpret_cast<PFNEGLCLIENTWAITSYNCKHRPROC>(loadProc("eglClientWaitSyncKHR"));
    l_eglCreateSyncKHR  = reinterpret_cast<PFNEGLCREATESYNCKHRPROC>(loadProc("eglCreateSyncKHR"));
    l_eglDestroySyncKHR = reinterpret_cast<PFNEGLDESTROYSYNCKHRPROC>(loadProc("eglDestroySyncKHR"));
    l_eglGetSyncAttribKHR =
        reinterpret_cast<PFNEGLGETSYNCATTRIBKHRPROC>(loadProc("eglGetSyncAttribKHR"));
    l_eglCreateImageKHR = reinterpret_cast<PFNEGLCREATEIMAGEKHRPROC>(loadProc("eglCreateImageKHR"));
    l_eglDestroyImageKHR =
        reinterpret_cast<PFNEGLDESTROYIMAGEKHRPROC>(loadProc("eglDestroyImageKHR"));
    l_eglLockSurfaceKHR = reinterpret_cast<PFNEGLLOCKSURFACEKHRPROC>(loadProc("eglLockSurfaceKHR"));
    l_eglQuerySurface64KHR =
        reinterpret_cast<PFNEGLQUERYSURFACE64KHRPROC>(loadProc("eglQuerySurface64KHR"));
    l_eglUnlockSurfaceKHR =
        reinterpret_cast<PFNEGLUNLOCKSURFACEKHRPROC>(loadProc("eglUnlockSurfaceKHR"));
    l_eglSetDamageRegionKHR =
        reinterpret_cast<PFNEGLSETDAMAGEREGIONKHRPROC>(loadProc("eglSetDamageRegionKHR"));
    l_eglSignalSyncKHR = reinterpret_cast<PFNEGLSIGNALSYNCKHRPROC>(loadProc("eglSignalSyncKHR"));
    l_eglCreateStreamKHR =
        reinterpret_cast<PFNEGLCREATESTREAMKHRPROC>(loadProc("eglCreateStreamKHR"));
    l_eglDestroyStreamKHR =
        reinterpret_cast<PFNEGLDESTROYSTREAMKHRPROC>(loadProc("eglDestroyStreamKHR"));
    l_eglQueryStreamKHR = reinterpret_cast<PFNEGLQUERYSTREAMKHRPROC>(loadProc("eglQueryStreamKHR"));
    l_eglQueryStreamu64KHR =
        reinterpret_cast<PFNEGLQUERYSTREAMU64KHRPROC>(loadProc("eglQueryStreamu64KHR"));
    l_eglStreamAttribKHR =
        reinterpret_cast<PFNEGLSTREAMATTRIBKHRPROC>(loadProc("eglStreamAttribKHR"));
    l_eglStreamConsumerAcquireKHR = reinterpret_cast<PFNEGLSTREAMCONSUMERACQUIREKHRPROC>(
        loadProc("eglStreamConsumerAcquireKHR"));
    l_eglStreamConsumerGLTextureExternalKHR =
        reinterpret_cast<PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALKHRPROC>(
            loadProc("eglStreamConsumerGLTextureExternalKHR"));
    l_eglStreamConsumerReleaseKHR = reinterpret_cast<PFNEGLSTREAMCONSUMERRELEASEKHRPROC>(
        loadProc("eglStreamConsumerReleaseKHR"));
    l_eglSwapBuffersWithDamageKHR = reinterpret_cast<PFNEGLSWAPBUFFERSWITHDAMAGEKHRPROC>(
        loadProc("eglSwapBuffersWithDamageKHR"));
    l_eglWaitSyncKHR = reinterpret_cast<PFNEGLWAITSYNCKHRPROC>(loadProc("eglWaitSyncKHR"));
    l_eglPostSubBufferNV =
        reinterpret_cast<PFNEGLPOSTSUBBUFFERNVPROC>(loadProc("eglPostSubBufferNV"));
    l_eglStreamConsumerGLTextureExternalAttribsNV =
        reinterpret_cast<PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALATTRIBSNVPROC>(
            loadProc("eglStreamConsumerGLTextureExternalAttribsNV"));
}
}  // extern "C"

/*
 * Copyright (C) 2018 Metrological Group B.V.
 * Copyright (C) 2020 Igalia S.L.
 * Author: Thibault Saunier <tsaunier@igalia.com>
 * Author: Alejandro G. Castro  <alex@igalia.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * aint with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#pragma once

#if ENABLE(MEDIA_STREAM) && USE(GSTREAMER)
#include "CaptureDevice.h"
#include "GStreamerVideoCapturer.h"
#include "RealtimeVideoCaptureSource.h"
#include "VideoFrameGStreamer.h"

namespace WebCore {

using NodeAndFD = GStreamerVideoCapturer::NodeAndFD;

class GStreamerVideoCaptureSource : public RealtimeVideoCaptureSource, GStreamerCapturerObserver {
public:
    static CaptureSourceOrError create(String&& deviceID, MediaDeviceHashSalts&&, const MediaConstraints*);
    static CaptureSourceOrError createPipewireSource(String&& deviceID, const NodeAndFD&, MediaDeviceHashSalts&&, const MediaConstraints*, CaptureDevice::DeviceType);

    WEBCORE_EXPORT static VideoCaptureFactory& factory();

    WEBCORE_EXPORT static DisplayCaptureFactory& displayFactory();

    const RealtimeMediaSourceCapabilities& capabilities() override;
    const RealtimeMediaSourceSettings& settings() override;
    GstElement* pipeline() { return m_capturer->pipeline(); }
    GStreamerCapturer* capturer() { return m_capturer.get(); }

    // GStreamerCapturerObserver
    void sourceCapsChanged(const GstCaps*) final;
    void captureEnded() final;

protected:
    GStreamerVideoCaptureSource(String&& deviceID, AtomString&& name, MediaDeviceHashSalts&&, const gchar* source_factory, CaptureDevice::DeviceType, const NodeAndFD&);
    GStreamerVideoCaptureSource(GStreamerCaptureDevice&&, MediaDeviceHashSalts&&);
    virtual ~GStreamerVideoCaptureSource();
    void startProducingData() override;
    void stopProducingData() override;
    bool canResizeVideoFrames() const final { return true; }
    void generatePresets() override;
    void setSizeFrameRateAndZoom(std::optional<int>, std::optional<int>, std::optional<double>, std::optional<double>) override;

    mutable std::optional<RealtimeMediaSourceCapabilities> m_capabilities;
    mutable std::optional<RealtimeMediaSourceSettings> m_currentSettings;
    CaptureDevice::DeviceType deviceType() const override { return m_deviceType; }

private:
    bool isCaptureSource() const final { return true; }
    void settingsDidChange(OptionSet<RealtimeMediaSourceSettings::Flag>) final;

    RefPtr<GStreamerVideoCapturer> m_capturer;
    CaptureDevice::DeviceType m_deviceType;
};

} // namespace WebCore

#endif // ENABLE(MEDIA_STREAM) && USE(GSTREAMER)

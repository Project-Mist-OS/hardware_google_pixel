/*
 * Copyright (C) 2021 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef HARDWARE_GOOGLE_PIXEL_PIXELSTATS_STATSHELPER_H
#define HARDWARE_GOOGLE_PIXEL_PIXELSTATS_STATSHELPER_H

#include <aidl/android/frameworks/stats/IStats.h>
#include <hardware/google/pixel/pixelstats/pixelatoms.pb.h>

namespace android {
namespace hardware {
namespace google {
namespace pixel {

using aidl::android::frameworks::stats::IStats;

bool fileExists(const std::string &path);
std::shared_ptr<IStats> getStatsService();

enum ReportEventType {
  EvtFGAbnormalEvent   = 0x4142, /* AB */
  EvtFGLearningHistory = 0x4C48, /* LH */
  EvtGMSR              = 0xFFFF, /* GMSR */
  EvtModelLoading      = 0x4D4C, /* ML */
  EvtHistoryValidation = 0x4856, /* HV */
  EvtFGRegularMonitor  = 0x524D, /* RM */
};

enum ReportEventFormat {
  FormatAddrWithVal,
  FormatIgnoreAddr,
  FormatNoAddr,
};

void reportSpeakerImpedance(const std::shared_ptr<IStats> &stats_client,
                            const PixelAtoms::VendorSpeakerImpedance &speakerImpedance);

void reportSlowIo(const std::shared_ptr<IStats> &stats_client,
                  const PixelAtoms::VendorSlowIo &slowIo);

void reportChargeCycles(const std::shared_ptr<IStats> &stats_client,
                        const std::vector<int32_t> &chargeCycles);

void reportHardwareFailed(const std::shared_ptr<IStats> &stats_client,
                          const PixelAtoms::VendorHardwareFailed &failure);

void reportSpeechDspStat(const std::shared_ptr<IStats> &stats_client,
                         const PixelAtoms::VendorSpeechDspStat &dsp_stats);

void reportUsbPortOverheat(const std::shared_ptr<IStats> &stats_client,
                           const PixelAtoms::VendorUsbPortOverheat &overheat_info);

void reportSpeakerHealthStat(const std::shared_ptr<IStats> &stats_client,
                             const PixelAtoms::VendorSpeakerStatsReported &speakerHealthStat);

void reportUsbDataSessionEvent(const std::shared_ptr<IStats> &stats_client,
                               const PixelAtoms::VendorUsbDataSessionEvent &usb_session);
void readLogbuffer(const std::string &buf_path, int num_fields, uint16_t code,
                   enum ReportEventFormat format, unsigned int last_check_time,
                   std::vector<std::vector<uint16_t>> &events);

void readLogbuffer(const std::string &buf_path, int num_fields, const char *code,
                   enum ReportEventFormat format, unsigned int last_check_time,
                   std::vector<std::vector<uint16_t>> &events);
}  // namespace pixel
}  // namespace google
}  // namespace hardware
}  // namespace android

#endif  // HARDWARE_GOOGLE_PIXEL_PIXELSTATS_STATSHELPER_H

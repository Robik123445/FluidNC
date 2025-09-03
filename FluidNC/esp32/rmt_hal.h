#pragma once

#include "hal_target.h"

// Define human-readable target name
#if HAL_TARGET_ESP32S3
#define RMT_TARGET_STRING "ESP32-S3"
#else
#define RMT_TARGET_STRING "ESP32"
#endif

#ifdef __cplusplus
// Maximum number of RMT TX channels for the active target
constexpr int kMaxRmtTx = HAL_RMT_TX_MAX;
#else
#define kMaxRmtTx HAL_RMT_TX_MAX
#endif

#ifdef __cplusplus
#include <string>
#include <sstream>

// Return human readable description for excessive axis configuration
// Vráti text s informáciou o maximálnom počte kanálov pre daný čip
inline std::string RmtAxisLimitMsg(int configured) {
    std::ostringstream oss;
    oss << RMT_TARGET_STRING " supports " << kMaxRmtTx
        << " RMT TX channels; configured=" << configured;
    return oss.str();
}
#endif

#ifdef __cplusplus
extern "C" {
#endif
// Start RMT transmission on given channel
void hal_rmt_start_tx(int pin, int level);
#ifdef __cplusplus
}
#endif

#pragma once

#ifdef CONFIG_IDF_TARGET_ESP32S3
#define RMT_TARGET_STRING "ESP32-S3"
#ifdef __cplusplus
// Maximum number of RMT TX channels for ESP32-S3
constexpr int kMaxRmtTx = 4;
#else
#define kMaxRmtTx 4
#endif
#else
#define RMT_TARGET_STRING "ESP32"
#ifdef __cplusplus
// Maximum number of RMT TX channels for other ESP32 targets
constexpr int kMaxRmtTx = 8;
#else
#define kMaxRmtTx 8
#endif
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


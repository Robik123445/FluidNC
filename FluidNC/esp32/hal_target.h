#pragma once

// Hardware abstraction for ESP32 variants.
// Provides macros describing peripheral availability.

#if defined(HAL_TARGET_ESP32S3) || defined(CONFIG_IDF_TARGET_ESP32S3)
#define HAL_TARGET_ESP32S3 1
#define HAL_TARGET_ESP32 0
#define HAL_HAS_DAC 0       // ESP32-S3 nemá interný DAC
#define HAL_HAS_APLL 0      // ESP32-S3 nepodporuje APLL
#define HAL_RMT_TX_MAX 4    // ESP32-S3 má 4 RMT TX kanály
#else
#define HAL_TARGET_ESP32S3 0
#define HAL_TARGET_ESP32 1
#define HAL_HAS_DAC 1       // ESP32 obsahuje DAC
#define HAL_HAS_APLL 1      // ESP32 podporuje APLL
#define HAL_RMT_TX_MAX 8    // ESP32 má 8 RMT TX kanálov
#endif


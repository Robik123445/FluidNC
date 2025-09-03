# ESP32 HAL helpers

This directory contains low level helpers for ESP32 targets.  
`hal_target.h` defines compile-time macros describing chip features:

- `HAL_HAS_DAC` – on chips without DAC the value is `0`.
- `HAL_HAS_APLL` – indicates availability of the Audio PLL.
- `HAL_RMT_TX_MAX` – maximum number of RMT TX channels.

Use these macros instead of raw `CONFIG_IDF_TARGET_*` checks to keep
drivers portable between ESP32 variants.

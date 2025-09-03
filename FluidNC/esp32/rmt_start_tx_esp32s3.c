// RMT start for ESP32-S3
// Štart prenosu pre ESP32-S3

#include "hal_target.h"
#if HAL_TARGET_ESP32S3
#include <driver/rmt.h>

// Trigger RMT transmission on configured channel
// Spustí prenos na kanáli nakonfigurovanom v RMT
void hal_rmt_start_tx(int pin, int level) {
    (void)level; // Level not used, waveform already prepared
    RMT.chnconf0[pin].mem_rd_rst_n = 1;
    RMT.chnconf0[pin].mem_rd_rst_n = 0;
    RMT.chnconf0[pin].tx_start_n   = 1;
}
#endif

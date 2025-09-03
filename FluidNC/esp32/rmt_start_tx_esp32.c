// RMT start for classic ESP32
// Štart prenosu pre klasické ESP32

#include "hal_target.h"
#if HAL_TARGET_ESP32
#include <driver/rmt.h>

// Trigger RMT transmission on configured channel
// Spustí prenos na kanáli nakonfigurovanom v RMT
void hal_rmt_start_tx(int pin, int level) {
    (void)level; // Level not used, waveform already prepared
    RMT.conf_ch[pin].conf1.mem_rd_rst = 1;
    RMT.conf_ch[pin].conf1.mem_rd_rst = 0;
    RMT.conf_ch[pin].conf1.tx_start   = 1;
}
#endif

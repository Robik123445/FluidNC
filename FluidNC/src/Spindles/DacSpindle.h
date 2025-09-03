// Copyright (c) 2020 -	Bart Dring
// Use of this source code is governed by a GPLv3 license that can be found in the LICENSE file.

#pragma once

/*
        DacSpindle.h

        Analog spindle driver that can use the ESP32 built‑in DAC, an external
        MCP4822 SPI DAC or a PWM pin followed by an RC filter to generate the
        analogue control voltage. Configuration determines which backend is
        used.
*/

#include "OnOffSpindle.h"

#include <cstdint>

namespace Spindles {
    // Drives an analogue spindle output using a selectable backend.
    class Dac : public OnOff {
    public:
        Dac(const char* name) : OnOff(name) {}

        Dac(const Dac&)            = delete;
        Dac(Dac&&)                 = delete;
        Dac& operator=(const Dac&) = delete;
        Dac& operator=(Dac&&)      = delete;

        void init() override;
        void config_message() override;
        void setSpeedfromISR(uint32_t dev_speed) override;

        // Configuration handlers:
        void group(Configuration::HandlerBase& handler) override;

        ~Dac() {}

        // Operating modes for the DAC backend
        enum Mode { Internal = 0, MCP4822 = 1, PWM = 2 };

    private:
        bool     _gpio_ok;  // true when selected backend initialised correctly
        int      _mode      = Internal;
        uint32_t _pwm_freq  = 5000;  // PWM frequency when using PWM backend
        Pin      _cs_pin;            // Chip select for MCP4822
        int      _mcp_channel = 0;   // Channel 0 or 1 for MCP4822

    protected:
        void set_output(uint32_t duty);  // write value to selected backend
    };

    extern const EnumItem dacModeItems[];
}

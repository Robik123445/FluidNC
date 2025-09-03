#pragma once

/*
    LedcSpindle.h

    Spindle driver using ESP32 LEDC PWM to approximate an analogue output.
    Useful for targets without built-in DAC such as ESP32-S3.
*/

#include "OnOffSpindle.h"
#include <cstdint>

namespace Spindles {
    // Provides analogue spindle control via LEDC PWM generator.
    class Ledc : public OnOff {
    public:
        // Construct LEDC spindle with optional name.
        Ledc(const char* name) : OnOff(name) {}

        Ledc(const Ledc&)            = delete;
        Ledc(Ledc&&)                 = delete;
        Ledc& operator=(const Ledc&) = delete;
        Ledc& operator=(Ledc&&)      = delete;

        // Initialise pins and LEDC channel.
        void init() override;
        // Report configuration details to log.
        void config_message() override;
        // Update PWM duty from interrupt context.
        void setSpeedfromISR(uint32_t dev_speed) override;

        // Configuration handlers.
        void group(Configuration::HandlerBase& handler) override;

        ~Ledc() {}

    private:
        // Write duty value to LEDC hardware.
        void IRAM_ATTR set_output(uint32_t duty);

        // LEDC configuration
        uint32_t _pwm_freq = 5000;      // PWM frequency in Hz
        uint8_t  _channel  = 0;         // LEDC channel
        uint8_t  _resolution = 13;      // Resolution bits
        bool     _inited   = false;     // True when LEDC configured
    };
}

// Copyright (c) 2024
// Use of this source code is governed by a GPLv3 license that can be found in the LICENSE file.

/*
    LedcSpindle.cpp

    Implements an analogue spindle using the ESP32 LEDC PWM peripheral. The
    duty cycle is scaled to match the requested spindle speed.
*/

#include "LedcSpindle.h"

#include <Arduino.h>
#include <sdkconfig.h>

namespace Spindles {
    // =========================== Ledc ============================
    // Initialise pins and LEDC configuration
    void Ledc::init() {
        _inited = false;

        if (_output_pin.undefined()) {
            log_error("LEDC spindle output_pin not defined");
            return;
        }
        if (!_output_pin.capabilities().has(Pin::Capabilities::PWM)) {
            log_error(name() << " output pin " << _output_pin.name().c_str() << " cannot do PWM");
            return;
        }

        auto outputNative = _output_pin.getNative(Pin::Capabilities::PWM);
        ledcSetup(_channel, _pwm_freq, _resolution);
        ledcAttachPin(outputNative, _channel);
        setupSpeeds((1u << _resolution) - 1u);
        _inited = true;

        _enable_pin.setAttr(Pin::Attr::Output);
        _direction_pin.setAttr(Pin::Attr::Output);
        is_reversable = _direction_pin.defined();

        if (_speeds.size() == 0) {
            linearSpeeds(10000, 100.0f);
        }

        init_atc();
        config_message();
    }

    // Log startup configuration
    void Ledc::config_message() {
        log_info(name() << " Spindle Ena:" << _enable_pin.name() << " Out:" << _output_pin.name() << " Dir:" << _direction_pin.name()
                        << " Freq:" << _pwm_freq << "Hz Chan:" << unsigned(_channel) << " Res:" << unsigned(_resolution)
                        << atc_info());
    }

    // Update LEDC duty from interrupt context
    void IRAM_ATTR Ledc::setSpeedfromISR(uint32_t dev_speed) {
        set_output(dev_speed);
    }

    // Write duty value to LEDC hardware
    void IRAM_ATTR Ledc::set_output(uint32_t duty) {
        if (!_inited) {
            return;
        }
        ledcWrite(_channel, duty);
    }

    // Handle configuration options
    void Ledc::group(Configuration::HandlerBase& handler) {
        handler.item("pwm_hz", _pwm_freq, 1, 20000000);
        handler.item("channel", _channel, 0, 7);
        handler.item("resolution_bits", _resolution, 1, 20);
        OnOff::group(handler);
    }

    // Configuration registration
    namespace {
    #ifdef CONFIG_IDF_TARGET_ESP32S3
        SpindleFactory::InstanceBuilder<Ledc> registration("DAC");
    #endif
    }
}

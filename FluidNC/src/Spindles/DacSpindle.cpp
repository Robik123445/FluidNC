// Copyright (c) 2020 - Bart Dring
// Use of this source code is governed by a GPLv3 license that can be found in the LICENSE file.

/*
    DacSpindle.cpp

    Implements an analogue spindle output capable of driving either the
    ESP32 internal DAC, an external MCP4822 SPI DAC or a PWM pin with an RC
    filter. The output voltage is proportional to the requested spindle speed.
*/
#include "DacSpindle.h"

#include <cstdint>

extern void dacWrite(uint8_t pin, uint8_t value);

#include <SPI.h>

namespace Spindles {
    // ======================================== Dac ======================================
    void Dac::init() {
        _gpio_ok = false;

        switch (_mode) {
            case Internal:
                if (_output_pin.undefined()) {
                    return;
                }
                if (_output_pin.capabilities().has(Pin::Capabilities::DAC)) {
                    _gpio_ok = true;
                    setupSpeeds(255);
                } else {
                    log_error("DAC spindle pin invalid " << _output_pin.name().c_str() << " (pin 25 or 26 only)");
                }
                break;
            case PWM:
                if (_output_pin.undefined()) {
                    log_error("DAC spindle output_pin not defined");
                    return;
                }
                if (_output_pin.capabilities().has(Pin::Capabilities::PWM)) {
                    _output_pin.setAttr(Pin::Attr::PWM, _pwm_freq);
                    _gpio_ok = true;
                    setupSpeeds(_output_pin.maxDuty());
                } else {
                    log_error(name() << " output pin " << _output_pin.name().c_str() << " cannot do PWM");
                }
                break;
            case MCP4822:
                if (_cs_pin.undefined()) {
                    log_error("DAC spindle cs_pin not defined");
                    return;
                }
                _cs_pin.setAttr(Pin::Attr::Output);
                SPI.begin();
                _gpio_ok = true;
                setupSpeeds(4095);
                break;
        }

        _enable_pin.setAttr(Pin::Attr::Output);
        _direction_pin.setAttr(Pin::Attr::Output);

        is_reversable = _direction_pin.defined();

        if (_speeds.size() == 0) {
            linearSpeeds(10000, 100.0f);
        }

        init_atc();
        config_message();
    }

    void Dac::config_message() {
        log_info(name() << " Spindle Ena:" << _enable_pin.name() << " Out:" << _output_pin.name() << " Dir:" << _direction_pin.name()
                        << " Mode:" << (_mode == Internal ? "internal" : (_mode == PWM ? "pwm" : "mcp4822")) << atc_info());
    }

    void IRAM_ATTR Dac::setSpeedfromISR(uint32_t speed) {
        set_output(speed);
    };
    void IRAM_ATTR Dac::set_output(uint32_t duty) {
        if (!_gpio_ok) {
            return;
        }

        switch (_mode) {
            case Internal: {
                auto outputNative = _output_pin.getNative(Pin::Capabilities::DAC);
                dacWrite(outputNative, static_cast<uint8_t>(duty));
                break;
            }
            case PWM:
                _output_pin.setDuty(duty);
                break;
            case MCP4822: {
                uint16_t value = 0x3000 | (_mcp_channel ? 0x8000 : 0) | (duty & 0x0FFF);
                _cs_pin.off();
                SPI.transfer16(value);
                _cs_pin.on();
                break;
            }
        }
    }

    const EnumItem dacModeItems[] = {
        { Dac::Internal, "internal" },
        { Dac::MCP4822, "mcp4822" },
        { Dac::PWM, "pwm" },
        EnumItem(Dac::Internal)
    };

    void Dac::group(Configuration::HandlerBase& handler) {
        handler.item("mode", _mode, dacModeItems);
        if (_mode == PWM) {
            handler.item("pwm_hz", _pwm_freq, 1, 20000000);
        } else if (_mode == MCP4822) {
            handler.item("cs_pin", _cs_pin);
            handler.item("mcp_channel", _mcp_channel, 0, 1);
        }
        OnOff::group(handler);
    }

    // Configuration registration
    namespace {
        SpindleFactory::InstanceBuilder<Dac> registration("DAC");
    }
}

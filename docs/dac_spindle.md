# DAC Spindle

Provides analogue spindle speed control using one of three backends:

> Note: On ESP32-S3 the DAC is not available; use `spindle_driver: ledc` to emulate analogue output via LEDC PWM.

- **internal** – uses ESP32 built-in DAC on pins 25 or 26.
- **mcp4822** – drives an external MCP4822 12‑bit SPI DAC.
- **pwm** – outputs PWM that can be filtered by an RC network to obtain a voltage.

## Configuration

```yaml
spindle:
  name: DAC
  type: DAC
  enable_pin: gpio.2
  output_pin: gpio.25    # unused when mode=mcp4822
  mode: internal         # internal, mcp4822 or pwm
  pwm_hz: 5000           # only for pwm mode
  cs_pin: gpio.5         # only for mcp4822 mode
  mcp_channel: 0         # 0 or 1 for mcp4822 mode
```

The speed map determines how G-code `S` values map to output voltage. When
unspecified it defaults to a linear 0–10000 rpm map.

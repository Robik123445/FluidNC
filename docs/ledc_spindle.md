# LEDC Spindle

Drives analogue spindle control using the ESP32 LEDC PWM peripheral. This is
the default analogue driver on **ESP32-S3** where no internal DAC exists.

## Configuration

```yaml
spindle:
  name: LEDC
  type: DAC          # reuses DAC type, but implemented with LEDC on ESP32-S3
  spindle_driver: ledc
  enable_pin: gpio.15
  output_pin: gpio.14
  pwm_hz: 5000
  channel: 0
  resolution_bits: 13
```

Speed mapping defaults to linear 0–10000 rpm → 0–100% duty cycle.

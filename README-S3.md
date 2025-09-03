# ESP32-S3 Quickstart

## Flashing

1. Connect the ESP32-S3 via USB.
2. Build and upload the firmware:
   ```bash
   pio run -e esp32s3-devkitc-1-n16r8 -t upload
   ```
3. After upload completes, reset the board.

## USB-CDC Console

Access the serial console over the native USB-CDC interface:
```bash
pio device monitor -p usb -b 115200
```

## PWM Spindle Verification

1. Enable PWM spindle output in your configuration.
2. Send a spindle command and measure the output pin with a multimeter or scope:
   ```gcode
   M3 S1000
   ```
3. Use `M5` to stop the spindle.

## RMT Channel Limits

ESP32-S3 offers **four** RMT channels. Each PWM, step generator, or other RMT-based feature consumes one channel. Plan pin assignments so the total RMT usage does not exceed four channels.

## Quick Test

### Compile Only
```bash
pio run -e esp32s3-devkitc-1-n16r8
```

### Minimal G-code Exercise
Use the USB-CDC console or Web UI to send:
```gcode
G0 X10 Y10
M3 S5000
G1 X0 Y0 F1000
M5
```
This moves the machine in a square and toggles the spindle.

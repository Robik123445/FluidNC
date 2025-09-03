<img src="https://github.com/bdring/FluidNC/wiki/images/logos/FluidNC.svg" width="600">

## Introduction

**FluidNC** is a CNC firmware optimized for the ESP32 controller. It is the next generation of firmware from the creators of Grbl_ESP32. It includes a web based UI and the flexibility to operate a wide variety of machine types. This includes the ability to control machines with multiple tool types such as laser plus spindle or a tool changer.  

## Firmware Architecture

- Object-Oriented hierarchical design
- Hardware abstraction for machine features like spindles, motors, and stepper drivers
- Extensible - Adding new features is much easier for the firmware as well as gcode senders.

## Machine Definition Method

There is no need to compile the firmware. You use an installation script to upload the latest release of the firmware and then create [config file](http://wiki.fluidnc.com/en/config/overview) text file that describes your machine.  That file is uploaded to the FLASH on the ESP32 using the USB/Serial port or WIFI.

You can have multiple config files stored on the ESP32. The default is config.yaml, but you can change that with [**$Config/Filename=<myOtherConfig.yaml>**](http://wiki.fluidnc.com/en/features/commands_and_settings#config_filename)

## ESP32-S3 Support

FluidNC supports the ESP32‑S3 module. Build firmware with [PlatformIO](https://platformio.org/) using one of:

- `platformio run -e wifi_s3` – WiFi enabled
- `platformio run -e bt_s3` – Bluetooth enabled
- `platformio run -e noradio_s3` – no wireless features

### wifi_s3 and noradio_s3 environments

Both S3 environments require the `xtensa-esp32s3` toolchain, which PlatformIO installs automatically.

**Common libraries**

- [TMCStepper](https://github.com/teemuatlut/TMCStepper)
- [ESP8266 and ESP32 OLED driver for SSD1306 displays](https://github.com/ThingPulse/esp8266-oled-ssd1306)

**Additional WiFi dependencies**

- [arduinoWebSockets](https://github.com/MitchBradley/arduinoWebSockets)
- [WiFi](https://github.com/MitchBradley/WiFi)

#### Build

```bash
platformio run -e wifi_s3
platformio run -e noradio_s3
```

#### Flash

```bash
platformio run -e wifi_s3 -t upload
platformio run -e noradio_s3 -t upload
```

#### Monitor

Use PlatformIO's USB monitor to watch the USB‑CDC console:

```bash
pio device monitor -p usb -b 115200
```

ESP32‑S3 boards must provide 16 MB flash and 8 MB PSRAM. The S3 offers only four RMT channels and lacks an internal DAC, so analog spindle output requires an external device.

An [ESP32‑S3 example configuration](https://github.com/bdring/fluidnc-config-files/blob/main/official/esp32-s3-example.yaml) is available for reference.

See [README-S3](README-S3.md) for flashing, USB-CDC usage, and quick test steps.

The DevKitC‑1 board exposes an on‑board status LED on **GPIO38**. The firmware uses the `S3_BOARD_LED_PIN` macro (default 38) to configure this LED at start-up; override it via a build flag if your design uses a different pin. Pins **GPIO35–GPIO37** are unavailable on ESP32‑S3 modules and should be avoided in configurations.

## Basic Grbl Compatibility

The intent is to maintain as much Grbl compatibility as possible. It is 100% compatible with the day to day operations of running gcode with a sender, so there is no change to the Grbl gcode send/response protocol, and all Grbl gcode are supported. Most of the $ settings have been replaced with easily readable items in the config file.


## WebUI

FluidNC includes a built-in browser-based Web UI (Esp32_WebUI) so you control the machine from a PC, phone, or tablet on the same Wifi network.

## Wiki

[Check out the wiki](http://wiki.fluidnc.com) if you want the learn more about the feature or how to use it.

## Credits

The original [Grbl](https://github.com/gnea/grbl) is an awesome project by Sungeon (Sonny) Jeon. I have known him for many years and he is always very helpful. I have used Grbl on many projects.

The Wifi and WebUI is based on [this project.](https://github.com/luc-github/ESP3D-WEBUI)  

## Discussion

<img src="http://wiki.fluidnc.com/discord-logo_trans.png" width="180">

We have a Discord server for the development this project. Ask for an invite


## Donations

This project requires a lot of work and often expensive items for testing. Please consider a safe, secure and highly appreciated donation via the PayPal link below or via the GitHub sponsor link at the top of the page.

[![](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/donate/?hosted_button_id=8DYLB6ZYYDG7Y)

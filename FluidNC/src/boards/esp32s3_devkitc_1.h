#pragma once

// Pin definitions for ESP32-S3 DevKitC-1 board.
// GPIO35, GPIO36 and GPIO37 are absent on this module and must not be used.

// Axis X pins
#define X_STEP_PIN        2
#define X_DIRECTION_PIN   3
#define X_DISABLE_PIN     4
#define X_LIMIT_NEG_PIN   16

// Axis Y pins
#define Y_STEP_PIN        5
#define Y_DIRECTION_PIN   6
#define Y_DISABLE_PIN     7
#define Y_LIMIT_NEG_PIN   17
// Second motor on Y (Y2)
#define Y2_STEP_PIN       8
#define Y2_DIRECTION_PIN  9
#define Y2_DISABLE_PIN    10

// Axis Z pins
#define Z_STEP_PIN        11
#define Z_DIRECTION_PIN   12
#define Z_DISABLE_PIN     13
#define Z_LIMIT_NEG_PIN   18

// Probe and toolsetter
#define PROBE_PIN         21
#define TOOLSETTER_PIN    33

// Spindle control
#define SPINDLE_PWM_PIN   14
#define SPINDLE_ENABLE_PIN 15

// Coolant control
#define COOLANT_MIST_PIN  22
#define COOLANT_FLOOD_PIN 23

// Default on-board LED pin. Can be overridden at build time with -DS3_BOARD_LED_PIN=<gpio>.
#ifndef S3_BOARD_LED_PIN
#    define S3_BOARD_LED_PIN 38
#endif

#include <Arduino.h>
#include "../Logging.h"

// Initialize board-specific hardware like the status LED.
// Nastavenie vstavaného LED pinu ako výstup a vypnutie LED.
inline void s3_board_setup() {
    pinMode(S3_BOARD_LED_PIN, OUTPUT);     // nastav LED pin ako výstup
    digitalWrite(S3_BOARD_LED_PIN, LOW);   // vypni LED pri štarte
    log_info("S3 board LED on GPIO" << S3_BOARD_LED_PIN);
}


#pragma once

#include <Arduino.h>
#include <Servo.h>
#include "main_settings.h"

// UNO PARAMETERS
const int ANALOG_PIN_COUNT_UNO = 6;
const int PWM_PIN_COUNT_UNO = 6;

const int ANALOG_PINS_UNO[ANALOG_PIN_COUNT_UNO] = { A0, A1, A2, A3, A4, A5 };
const int PWM_PINS_UNO[PWM_PIN_COUNT_UNO] = { 3, 5, 6, 9, 10, 11 };

// FUNCTION PROTOTYPES
void test_verifySettings();
void test_startingPosition();
void test_calibrateRange();
void test_calibrateInterval();
void test_calibration();


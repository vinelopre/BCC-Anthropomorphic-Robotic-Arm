#pragma once

#include <Arduino.h>
#include <Servo.h>

// SERVO AND ASSEMBLY INITIALIZATION
const int ASSEMBLY_COUNT = 5;

// TEST PARAMETERS
const int MIN_ANGLE = 0;
const int MID_ANGLE = 90;
const int MAX_ANGLE = 180;

const int TEST_ANGLE_COUNT = 7;
const int TEST_ANGLE[TEST_ANGLE_COUNT] = { 0, 30, 60, 90, 120, 150, 180 };

const int OUTPUT_BUFFER_SIZE = 100;
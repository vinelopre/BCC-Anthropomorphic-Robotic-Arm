// DESCRIPTION
/*
This program is designed to test the conversion of input values into degrees for a servo.

It will take the input range from an analog pin and then map them to a degree range from 0 to 180.

A potentiometer (variable resistor) will be used to direct input values into the analog pin, which is converted to a degree according to the mapped range.

This degree will then be sent to a servo to control its rotation position.

This process will repeat for as long as the test conditions and program are active.
*/


// INPUT
// analog value


// PROCESS
/*
1. Set up a potentiometer to control analog input.
2. Map analog input values to a degree range from 0 to 180.
3. Transmit converted degree values to servo control.
4. Run tests for servo control:
  a. Calibration test
*/


// OUTPUT
// servo movement


//**************** TEST START ****************


// HEADER FILE/PREPROCESSOR LIBRARY INITIALIZATION
#include <Arduino.h>
#include <Servo.h>
#include <unity.h>

// FUNCTION PROTOTYPES
void test_calibration();

// TEST SETUP
void setUp(void)
{
  
}

  
// TEST TEARDOWN
void tearDown(void)
{

}

// PROGRAM SETTINGS
const int SERVO_COUNT = 1;

const int PWM_CONTROL_PIN[SERVO_COUNT] = { 3 };

const int POTENTIOMETER_COUNT = 1;
const int ANALOG_CONTROL_PIN[POTENTIOMETER_COUNT] = { A0 };

const int MIN_ANGLE = 0;
const int MID_ANGLE = 90;
const int MAX_ANGLE = 180;

const int TEST_ANGLE_COUNT = 7;
const int TEST_ANGLE[TEST_ANGLE_COUNT] = { 0, 30, 60, 90, 120, 150, 180 };

int testCount = 0;
int adjustedTestCount = testCount + 1;

const int BUFFER_SIZE = 100;
char outputBuffer[BUFFER_SIZE] = {};

// DECLARATIONS
int angle;
int analogInput;

// SERVO INITIALIZATION
Servo servo1;

Servo servoArray[SERVO_COUNT] = { servo1 };

// SETUP FUNCTION INITIALIZATION
void setup() {

  // MONITOR DELAY
  delay(2000);

	// MONITOR SPEED
	Serial.begin(115200);

	// DECLARATION
  // N/A

  // OUTPUT PIN SETUP
  for (int index = 0; index < SERVO_COUNT; index++)
  {
    pinMode(PWM_CONTROL_PIN[index], OUTPUT);
  }

  // INPUT
  // SET INPUT
  analogInput = analogRead(ANALOG_CONTROL_PIN[0]);

	// SERVO SETUP
  for (int index = 0; index < SERVO_COUNT; index++)
  {
    // ATTACH SERVO
    servoArray[index].attach(PWM_CONTROL_PIN[index]);

    // STARTING POSITION
    servoArray[index].write(MID_ANGLE);
  }

  delay(2000);

  // INITIAL TEST
  sprintf(outputBuffer, "TEST %d: MOVE TO %d DEGREES", adjustedTestCount ,TEST_ANGLE[testCount]);
  Serial.println(outputBuffer);


	// TEST BEGIN
	UNITY_BEGIN();

}

// LOOP FUNCTION INITIALIZATION
void loop() {

	// PROCESS
  RUN_TEST(test_calibration);

	// OUTPUT
  // N/A

	// TEST END
  UNITY_END();

}

//**************** TEST END ****************

// FUNCTION DEFINITIONS
void test_calibration()
{

  while (testCount < TEST_ANGLE_COUNT)
  {
    // DEGREE CONVERSION
    analogInput = analogRead(ANALOG_CONTROL_PIN[0]);
    angle = map(analogInput, 0, 1023, 0, 180);
    
    for (int index = 0; index < SERVO_COUNT; index++)
      servoArray[index].write(angle);

    if (angle == TEST_ANGLE[testCount] && testCount < TEST_ANGLE_COUNT)
    {
      TEST_ASSERT_EQUAL_INT_MESSAGE(TEST_ANGLE[testCount], angle, "SUCCESS");
      Serial.println();

      adjustedTestCount++;
      testCount++;

      sprintf(outputBuffer, "TEST %d: MOVE TO %d DEGREES", adjustedTestCount ,TEST_ANGLE[testCount]);
      Serial.println(outputBuffer);
      

    }
  }
}


// PRIMARY CONCEPTS
/*
1. Analog values will be converted to digital values.
2. Analog input pins are required for potentiometer.
3. Digital PWM pins (marked with a ~) are required for servo control. 
4. Analog range: 0-1023 (10-bit or 2^10)
*/

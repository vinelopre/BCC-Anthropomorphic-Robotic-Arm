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
  b. Manual control test
*/


// OUTPUT
// servo movement


//**************** TEST START ****************

// HEADER FILE/PREPROCESSOR LIBRARY INITIALIZATION
#include <Arduino.h>
#include <Servo.h>
#include <unity.h>

// UNO PARAMETERS
const int ANALOG_PIN_COUNT_UNO = 6;
const int PWM_PIN_COUNT_UNO = 6;

const int ANALOG_PINS_UNO[ANALOG_PIN_COUNT_UNO] = { A0, A1, A2, A3, A4, A5 };
const int PWM_PINS_UNO[PWM_PIN_COUNT_UNO] = { 3, 5, 6, 9, 10, 11 };

// SERVO AND ASSEMBLY INITIALIZATION
const int ASSEMBLY_COUNT = 2;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

Servo servoArray[ASSEMBLY_COUNT] = { servo1, servo2 };

// TEST PARAMETERS
const int MIN_ANGLE = 0;
const int MID_ANGLE = 90;
const int MAX_ANGLE = 180;

const int TEST_ANGLE_COUNT = 7;
const int TEST_ANGLE[TEST_ANGLE_COUNT] = { 0, 30, 60, 90, 120, 150, 180 };

// DECLARATIONS
int analogInput[ASSEMBLY_COUNT] = {};

const int OUTPUT_BUFFER_SIZE = 100;
char outputBuffer[OUTPUT_BUFFER_SIZE] = {};



// FUNCTION PROTOTYPES
void test_verifySettings();
void test_startingPosition();
void test_calibrateRange();
void test_calibrateInterval();
void test_calibration();
void test_manualControl();

// TEST SETUP
void setUp(void)
{


}

  
// TEST TEARDOWN
void tearDown(void)
{

}


// SETUP FUNCTION INITIALIZATION
void setup() {

	// MONITOR DELAY
	delay(2000);

	// MONITOR SPEED
	Serial.begin(115200);

	// TEST BEGIN
	UNITY_BEGIN();

	// OUTPUT PIN SETUP
	for (int index = 0; index < ASSEMBLY_COUNT; index++)
		pinMode(PWM_PINS_UNO[index], OUTPUT);

	// INITIAL INPUT AND POSITION SETUP
	for (int index = 0; index < ASSEMBLY_COUNT; index++)
	{
		analogInput[index] = analogRead(ANALOG_PINS_UNO[index]);
		servoArray[index].attach(PWM_PINS_UNO[index]);

	}

	RUN_TEST(test_verifySettings);

	RUN_TEST(test_calibration);

}

// LOOP FUNCTION INITIALIZATION
void loop() {


	// PROCESS
	RUN_TEST(test_manualControl);

	delay(2000);

	RUN_TEST(test_startingPosition);

	// OUTPUT
	// N/A

	// TEST END
	UNITY_END();

}

//**************** TEST END ****************

// FUNCTION DEFINITIONS
void test_verifySettings()
{
	int elementCount1;
	int elementCount2;
	int elementCount3;

	elementCount1 = sizeof(ANALOG_PINS_UNO) / sizeof(ANALOG_PINS_UNO[0]);
	elementCount2 = sizeof(PWM_PINS_UNO) / sizeof(PWM_PINS_UNO[0]);
	elementCount3 = sizeof(servoArray) / sizeof(servoArray[0]);

	TEST_ASSERT_EQUAL_INT(elementCount1, elementCount2);
	TEST_ASSERT_EQUAL_INT(elementCount2, elementCount1);

	TEST_ASSERT_EQUAL_INT(elementCount3, ASSEMBLY_COUNT);
}

void test_calibration()
{
	RUN_TEST(test_startingPosition);

	delay(2000);

	RUN_TEST(test_calibrateRange);

	delay(2000);

	RUN_TEST(test_calibrateInterval);

	delay(2000);

	RUN_TEST(test_startingPosition);
}

void test_startingPosition()
{
	for (int index = 0; index < ASSEMBLY_COUNT; index++)
	{
		servoArray[index].write(MID_ANGLE);
		TEST_ASSERT_EQUAL_INT(MID_ANGLE, servoArray[index].read());
	}
}

void test_calibrateRange()
{
	const int ROTATIONS = 3;

	for (int count = 0; count < ROTATIONS; count++)
	{
		for (int index = 0; index < ASSEMBLY_COUNT; index++)
		{
			servoArray[index].write(MAX_ANGLE);
			TEST_ASSERT_EQUAL_INT(MAX_ANGLE, servoArray[index].read());
		}

		
		delay(1000);

		for (int index = 0; index < ASSEMBLY_COUNT; index++)
		{
			servoArray[index].write(MIN_ANGLE);
			TEST_ASSERT_EQUAL_INT(MIN_ANGLE, servoArray[index].read());
		}


		delay(1000);

		for (int index = 0; index < ASSEMBLY_COUNT; index++)
		{
			servoArray[index].write(MID_ANGLE);
			TEST_ASSERT_EQUAL_INT(MID_ANGLE, servoArray[index].read());
		}
	}
}

void test_calibrateInterval()
{
  for (int count = 0; count < (TEST_ANGLE_COUNT); count++)
  {
    for (int index = 0; index < ASSEMBLY_COUNT; index++)
    {
      servoArray[index].write(TEST_ANGLE[count]);
      TEST_ASSERT_EQUAL_INT(TEST_ANGLE[count], servoArray[index].read());
    }

    delay(1000);
  }

  for (int count = TEST_ANGLE_COUNT - 1; count > (-1); count--)
  {
    for (int index = 0; index < ASSEMBLY_COUNT; index++)
    {
      servoArray[index].write(TEST_ANGLE[count]);
      TEST_ASSERT_EQUAL_INT(TEST_ANGLE[count], servoArray[index].read());
    }

    delay(1000);
  }
    
  for (int index = 0; index < ASSEMBLY_COUNT; index++)
  {
    servoArray[index].write(MIN_ANGLE);
	TEST_ASSERT_EQUAL_INT(MIN_ANGLE, servoArray[index].read());
  }

}

void test_manualControl()
{
	int testCount = 0;
	int testCountControl = TEST_ANGLE_COUNT - 1;
	int printCount = testCount + 1;

	int lowerInterval;
	int upperInterval;
	const int INTERVAL_SIZE = 10;

	bool servosAligned = 1;

	bool justPrinted[ASSEMBLY_COUNT] = {};

	sprintf(outputBuffer, "TEST %d OF %d: ROTATE TO %d DEGREES", printCount, TEST_ANGLE_COUNT, TEST_ANGLE[testCount]);
	Serial.println(outputBuffer);

	while(testCount < TEST_ANGLE_COUNT)
	{
		for (int index = 0; index < ASSEMBLY_COUNT; index++)
		{
			analogInput[index] = map(analogRead(ANALOG_PINS_UNO[index]), 0, 1023, 0, 180);
			servoArray[index].write(analogInput[index]);

			lowerInterval = TEST_ANGLE[testCount] - INTERVAL_SIZE;
			upperInterval = TEST_ANGLE[testCount] + INTERVAL_SIZE;

			if ((servoArray[index].read() <= upperInterval) && (servoArray[index].read() >= lowerInterval) && (justPrinted[index] == 0))
			{
				sprintf(outputBuffer, "SERVO %d: ALIGNED TO %d WITH DELTA %d, PRINT %d and %d", index, TEST_ANGLE[testCount], INTERVAL_SIZE, justPrinted[0], justPrinted[1]);
				Serial.println(outputBuffer);

				// TODO: TROUBLESHOOT PRINT FLAGS
				justPrinted[index] = 1;
			}
			else if (((servoArray[index].read() > upperInterval) || (servoArray[index].read() < lowerInterval)) && justPrinted[index] == 1)
			{
				justPrinted[index] = 0;
			}

			servosAligned = 1;

			for (int count = 0; count < ASSEMBLY_COUNT; count++)
			{
				if ((servoArray[count].read() > upperInterval) || (servoArray[count].read() < lowerInterval))
				{
					servosAligned = 0;
				}
			}

			if (servosAligned)
			{
				TEST_ASSERT_INT_WITHIN(INTERVAL_SIZE, TEST_ANGLE[testCount], servoArray[index].read());

				sprintf(outputBuffer, "SUCCESS");
				Serial.println(outputBuffer);

					testCount++;
					printCount++;

				if (testCount <= testCountControl)
				{
					sprintf(outputBuffer, "TEST %d OF %d: ROTATE TO %d DEGREES", printCount, TEST_ANGLE_COUNT, TEST_ANGLE[testCount]);
					Serial.println(outputBuffer);
				}
			}
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

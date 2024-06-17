#include <Arduino.h>
#include <Servo.h>
#include "calibrations.h"
#include "main_settings.h"
#include "potcontrol.h"

extern Servo servoArray[];

// FUNCTION DEFINITIONS
void test_calibration()
{
	test_startingPosition();

	delay(2000);

	test_calibrateRange();

	delay(2000);

	test_calibrateInterval();

	delay(2000);

	test_startingPosition();

    delay(1000);
}

void test_startingPosition()
{
	// Write to default position.
	for (int index = 0; index < ASSEMBLY_COUNT; index++)
	{
		servoArray[index].write(MID_ANGLE);
	}
}

void test_calibrateRange()
{
	const int ROTATIONS = 3;

	for (int count = 0; count < ROTATIONS; count++)
	{
		// Set servos to maximum angle.
		for (int index = 0; index < ASSEMBLY_COUNT; index++)
		{
			servoArray[index].write(MAX_ANGLE);
		}

		delay(1000);

		// Set servos to minimum angle.
		for (int index = 0; index < ASSEMBLY_COUNT; index++)
		{
			servoArray[index].write(MIN_ANGLE);
		}

		delay(1000);
	}
}

void test_calibrateInterval()
{
	// Write ascending positions.
	for (int count = 0; count < (TEST_ANGLE_COUNT); count++)
	{
		for (int index = 0; index < ASSEMBLY_COUNT; index++)
		{
			servoArray[index].write(TEST_ANGLE[count]);
		}
		delay(1000);
	}

	// Write descending positions.
	for (int count = TEST_ANGLE_COUNT - 1; count > (-1); count--)
	{
		for (int index = 0; index < ASSEMBLY_COUNT; index++)
		{
			servoArray[index].write(TEST_ANGLE[count]);
		}
		delay(1000);
	}

	// Reset to minimum angle.
	for (int index = 0; index < ASSEMBLY_COUNT; index++)
	{
		servoArray[index].write(MIN_ANGLE);
	}

}
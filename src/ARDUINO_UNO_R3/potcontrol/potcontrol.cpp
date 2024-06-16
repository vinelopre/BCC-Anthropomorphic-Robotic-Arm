#include <Arduino.h>
#include <Servo.h>
#include "potcontrol.h"
#include "main_settings.h"
#include "calibrations.h"

// FUNCTION DEFINITIONS

void test_manualControl()
{
    extern manualControl master;

	master.initializeUserControl();
}

void manualControl::attachPins()
{
	// OUTPUT PIN SETUP
	for (int index = 0; index < ASSEMBLY_COUNT; index++)
		pinMode(PWM_PINS_UNO[index], OUTPUT);

	// INITIAL INPUT AND POSITION SETUP
	for (int index = 0; index < ASSEMBLY_COUNT; index++)
	{
		analogInput[index] = analogRead(ANALOG_PINS_UNO[index]);
		servoArray[index].attach(PWM_PINS_UNO[index]);
	}
}

void manualControl::initializeUserControl()
{
	// Initial prompt.
	userPrompt();

	while(testCount < TEST_ANGLE_COUNT)
	{

		initializeControlValues();
		initializePrintClock();

		writeServos();

		printAlignment();

		confirmTotalAlignment();

	}
}

void manualControl::writeServos()
{
	for (int index = 0; index < ASSEMBLY_COUNT; index++)
	{
		analogInput[index] = map(analogRead(ANALOG_PINS_UNO[index]), 0, 1023, 0, 180);
		servoArray[index].write(analogInput[index]);
	}
}

void manualControl::userPrompt()
{
	if (testCount == 0)
	{
		sprintf(outputBuffer, "TEST %d OF %d: ROTATE TO %d DEGREES", displayCount, TEST_ANGLE_COUNT, TEST_ANGLE[testCount]);
		Serial.println(outputBuffer);
		setPrintCounts();
	}
	else if (testCount <= testCountControl && testCount != 0)
	{
		sprintf(outputBuffer, "TEST %d OF %d: ROTATE TO %d DEGREES", displayCount, TEST_ANGLE_COUNT, TEST_ANGLE[testCount]);
		Serial.println(outputBuffer);
		setPrintCounts();
	}
	else if (testCount > testCountControl)
	{
		sprintf(outputBuffer, "TEST COMPLETE. RESTORING TO DEFAULT POSITIONS...");
		Serial.println(outputBuffer);
	}
}

void manualControl::printAlignment()
{
	for (int index = 0; index < ASSEMBLY_COUNT; index++)
	{
		if (checkPrintConditions(index))
		{
			sprintf(outputBuffer, "SERVO %d: ALIGNED TO %d WITH DELTA %d", index, TEST_ANGLE[testCount], INTERVAL_SIZE);
			Serial.println(outputBuffer);

			timestampPrint(index);
		}
	}
}

void manualControl::confirmTotalAlignment()
{
	if (checkTotalAlignment())
	{

		sprintf(outputBuffer, "SUCCESS");
		Serial.println(outputBuffer);

		testCount++;
		displayCount++;

		userPrompt();
	}
}

bool manualControl::checkTotalAlignment()
{
	bool allServosAligned = 1;

	for (int index = 0; index < ASSEMBLY_COUNT; index++)
	{
		if(checkAlignmentConditions(index) != 1)
			allServosAligned = 0;
	}

	return allServosAligned;
}

bool manualControl::checkAlignmentConditions(int index)
{
	bool validAlignment = 1;

	if (servoArray[index].read() >= upperInterval)
		validAlignment = 0;

	if (servoArray[index].read() <= lowerInterval)
		validAlignment = 0;

	return validAlignment;
}

bool manualControl::checkPrintConditions(int index)
{
	bool validPrint = 1;

	if (!checkAlignmentConditions(index))
		validPrint = 0;

	if (!checkPrintInterval(index))
		validPrint = 0;
		
	return validPrint;
}

void manualControl::initializeControlValues()
{
	lowerInterval = TEST_ANGLE[testCount] - INTERVAL_SIZE;
	upperInterval = TEST_ANGLE[testCount] + INTERVAL_SIZE;
}                                                         

void manualControl::initializePrintClock()
{
	timeInterval = millis();
}

void manualControl::timestampPrint(int index)
{
	printCount[index]++;
	lastPrintTime[index] = millis();
    timeBuffer[index] = timeInterval - lastPrintTime[index];

    bufferRefreshCheck(index);
}

void manualControl::bufferRefreshCheck(int index)
{
    if (timeBuffer[index] > DELAY_THRESHOLD)
	{
		maxPrints = 1;
		printCount[index] = 0;
	}
	else
	{
		maxPrints = 0;
	}	
}

void manualControl::setPrintCounts()
{
	for (int index = 0; index < ASSEMBLY_COUNT; index++)
	{
		printCount[index] = 0;
	}
}

bool manualControl::checkPrintInterval(int index)
{
	bool validPrintTime = 1;

	timeBuffer[index] = timeInterval - lastPrintTime[index];

	if (printCount[index] >= maxPrints)
		validPrintTime = 0;

	if (timeBuffer[index] < DELAY_THRESHOLD)
		validPrintTime = 0;
	else
		printCount[index] = 0;

	return validPrintTime;
}
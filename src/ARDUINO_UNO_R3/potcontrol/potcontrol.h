#pragma once
#include <Arduino.h>
#include <Servo.h>
#include "calibrations.h"
#include "main_settings.h"


// EXTERNAL DECLARATION
extern Servo servoArray[];

// DECLARATIONS
// N/A

// STRUCT DEFINITIONS
struct manualControl
{
	int analogInput[ASSEMBLY_COUNT] = {};

	char outputBuffer[OUTPUT_BUFFER_SIZE] = {};

	int testCount = 0;
	int testCountControl = TEST_ANGLE_COUNT - 1;
	int displayCount = testCount + 1;

	int lowerInterval;
	int upperInterval;
	const int INTERVAL_SIZE = 10;

	int maxPrints = 1;
	int printCount[ASSEMBLY_COUNT] = {};

	const unsigned long int DELAY_THRESHOLD = 2000;
    unsigned long int timeBuffer[ASSEMBLY_COUNT];

	unsigned long int timeInterval;
	unsigned long int lastPrintTime[ASSEMBLY_COUNT] = {};


    void attachPins();
	void initializeUserControl();
	void userPrompt();
	void writeServos();
	bool checkPrintConditions(int);
	bool checkAlignmentConditions(int);
	void printAlignment();
	bool checkPrintInterval(int);
	bool checkTotalAlignment();
	void confirmTotalAlignment();
	void initializeControlValues();
	void initializePrintClock();
	void timestampPrint(int);
    void bufferRefreshCheck(int);
	void setPrintCounts();
};

void test_manualControl();


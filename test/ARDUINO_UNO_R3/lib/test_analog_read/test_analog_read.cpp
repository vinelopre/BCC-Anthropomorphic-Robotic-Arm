// DESCRIPTION
/*
This program is designed to test for the output on an analog pin to see if there is electrical noise.

It will read a value from an analog pin.

It will then print this value to the serial monitor.
*/


// INPUT
// analog pin


// PROCESS
/*
1. Assign analog pin to be read.
2. Read value from analog pin.
3. Print value from analog pin to serial monitor.
4. Run until test ends.
*/


// OUTPUT
// pin value


//**************** TEST START ****************


// HEADER FILE/PREPROCESSOR LIBRARY INITIALIZATION
#include <Arduino.h>
#include <unity.h>

// TEST SETUP
void setUp(void)
{

}

  
// TEST TEARDOWN
void tearDown(void)
{

}

// GLOBAL SETUP

// CONSTANT INITIALIZATION
const int ANALOG_PIN = A0;

const int BUFFER_SIZE = 100;

// DECLARATION
int pinValue;

char outputBuffer[BUFFER_SIZE] = {};

// SETUP FUNCTION INITIALIZATION
void setup() {

    // START DELAY
    delay(2000);

	// MONITOR SPEED
	Serial.begin(115200);

	// INPUT
    // N/A

	// TEST BEGIN
	UNITY_BEGIN();

}

// LOOP FUNCTION INITIALIZATION
void loop() {


	// PROCESS
    pinValue = analogRead(ANALOG_PIN);
    sprintf(outputBuffer, "%d", pinValue);

	// OUTPUT
    Serial.println(outputBuffer);

	delay(250);
	// TEST END
    // UNITY_END();

}

//**************** TEST END ****************


// PRIMARY CONCEPTS
/*
1. Only analog pins are to be used for reading.


*/
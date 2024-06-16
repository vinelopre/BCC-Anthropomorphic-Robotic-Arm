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
#include "potcontrol/potcontrol.h"

// SERVO INITIALIZATIONS
Servo servo1;
Servo servo2;
Servo servo3;

Servo servoArray[ASSEMBLY_COUNT] = { servo1, servo2, servo3 };

// STRUCT INITIALIZATION
manualControl master;

// FUNCTION PROTOTYPES

void setup() 
{
	// MONITOR DELAY
	delay(2000);

	// MONITOR SPEED
	Serial.begin(115200);

	// PIN SETUP
	master.attachPins();

	// INITIAL CALIBRATION
  	test_calibration();

	// MANUAL CONTROL PROGRAM
  	test_manualControl();

 	 delay(2000);

	// RESET TO DEFAULT POSITION
  	test_startingPosition();
}

void loop()
{

}

//**************** TEST END ****************


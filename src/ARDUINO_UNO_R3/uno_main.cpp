//**************** MAIN START ****************

// HEADER FILE/PREPROCESSOR LIBRARY INITIALIZATION
#include <Arduino.h>
#include <Servo.h>
#include "potcontrol/potcontrol.h"

// SERVO INITIALIZATIONS
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

Servo servoArray[ASSEMBLY_COUNT] = { servo1, servo2, servo3, servo4, servo5 };

// STRUCT INITIALIZATION
manualControl master;

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

//**************** MAIN END ****************

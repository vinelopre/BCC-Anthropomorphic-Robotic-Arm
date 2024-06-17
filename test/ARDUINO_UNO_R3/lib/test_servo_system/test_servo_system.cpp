// DESCRIPTION
/*
This program is designed to test the data input and output of one or more servos in a series.

It will take a number of servos and then initialize them in an array of class Servo.

It will then run a series of tests on every servo at the same time.

The test results and movement of the servo will help determine whether an issue is electrical, mechanical, or software-related.
*/


// INPUT
// number of servos 


// PROCESS
/*
1. Initialize a constant variable to represent the number of servos.
2. Initialize an array of class Servo based on the number of servos.
3. Run tests on every servo using a minimum of 0 and a maximum of 180 for angle input:
  a. Range test
  b. Interval test
  c. Precision test
4. Observe the motion of the servos.
5. Record observations.
*/


// OUTPUT
// servo motion


//**************** TEST START ****************


// HEADER FILE/PREPROCESSOR LIBRARY INITIALIZATION
#include <Arduino.h>
#include <Servo.h>
#include <unity.h>

// FUNCTION PROTOTYPES
void test_settings();
void test_pinSetup();

void test_range();
void test_interval();
void test_precision();

// TEST SETUP
void setUp(void)
{
  
}

  
// TEST TEARDOWN
void tearDown(void)
{

}

// PROGRAM SETTINGS
const int SERVO_COUNT = 5;

const int CONTROL_PIN[SERVO_COUNT] = { 2, 3, 4, 5, 6 };

const int MIN_ANGLE = 0;
const int MAX_ANGLE = 180;
const int ROTATIONS_COUNT = 3;

const int TEST_ANGLE_COUNT = 7;
const int TEST_ANGLE[TEST_ANGLE_COUNT] = { 0, 30, 60, 90, 120, 150, 180 };

// DECLARATIONS
int angle;

// SERVO INITIALIZATION
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

Servo servoArray[SERVO_COUNT] = { servo1, servo2, servo3, servo4, servo5 };

// SETUP FUNCTION INITIALIZATION
void setup() {

	// MONITOR SPEED
	Serial.begin(115200);

	// SERVO SETUP
  for (int index = 0; index < SERVO_COUNT; index++)
  {
    // ATTACH SERVO
    servoArray[index].attach(CONTROL_PIN[index]);

    // STARTING POSITION
    servoArray[index].write(MIN_ANGLE);
  }

	// DECLARATION
  // N/A

	// INPUT
  // N/A

	// TEST BEGIN
	UNITY_BEGIN();

}

// LOOP FUNCTION INITIALIZATION
void loop() {


	// PROCESS
  RUN_TEST(test_pinSetup);
  RUN_TEST(test_range);
  RUN_TEST(test_interval);
  RUN_TEST(test_precision);
  RUN_TEST(test_range);

	// OUTPUT
  // N/A

	// TEST END
  UNITY_END();

}

//**************** TEST END ****************

/// FUNCTION DEFINITIONS

void test_settings()
{
  // TODO: WRITE TEST TO CONFIRM SETTINGS
}

void test_pinSetup()
{
  for (int index = 0; index < SERVO_COUNT; index++)
  {
    digitalWrite(CONTROL_PIN[index], HIGH);
    TEST_ASSERT_EQUAL(HIGH, digitalRead(CONTROL_PIN[index]));

    delay(1000);

    digitalWrite(CONTROL_PIN[index], LOW);
    TEST_ASSERT_EQUAL(LOW, digitalRead(CONTROL_PIN[index]));
  }
}

void test_range()
{

  for (int count = 0; count < ROTATIONS_COUNT; count++)
  {
    for (int index = 0; index < SERVO_COUNT; index++)
    {
      servoArray[index].write(MIN_ANGLE);
      TEST_ASSERT_EQUAL_INT(MIN_ANGLE, servoArray[index].read());
    }

    delay(2000);

    for (int index = 0; index < SERVO_COUNT; index++)
    {
      servoArray[index].write(MAX_ANGLE);
      TEST_ASSERT_EQUAL_INT(MAX_ANGLE, servoArray[index].read());
    }

    delay(2000);
  }

  for (int index = 0; index < SERVO_COUNT; index++)
    servoArray[index].write(MIN_ANGLE);
}

void test_interval()
{
  for (int count = 0; count < (TEST_ANGLE_COUNT); count++)
  {
    for (int index = 0; index < SERVO_COUNT; index++)
    {
      servoArray[index].write(TEST_ANGLE[count]);
      TEST_ASSERT_EQUAL_INT(TEST_ANGLE[count], servoArray[index].read());
    }

    delay(1000);
  }

  for (int count = TEST_ANGLE_COUNT - 1; count > (-1); count--)
  {
    for (int index = 0; index < SERVO_COUNT; index++)
    {
      servoArray[index].write(TEST_ANGLE[count]);
      TEST_ASSERT_EQUAL_INT(TEST_ANGLE[count], servoArray[index].read());
    }

    delay(1000);
  }
    
  for (int index = 0; index < SERVO_COUNT; index++)
    servoArray[index].write(MIN_ANGLE);
}

void test_precision()
{
  int angleIndex = 0;

  for (angle = MIN_ANGLE; angle < MAX_ANGLE; angle++)
  {

    for (int index = 0; index < SERVO_COUNT; index++)
      servoArray[index].write(angle);

    while (angle == TEST_ANGLE[angleIndex])
    {
      for (int index = 0; index < SERVO_COUNT; index++)
        TEST_ASSERT_EQUAL_INT(angle, servoArray[index].read());
      angleIndex++;
      break;
    }

    delay(100);

  }

  for (angle = MAX_ANGLE; angle > MIN_ANGLE; angle--)
  {
    for (int index = 0; index < SERVO_COUNT; index++)
      servoArray[index].write(angle);

    while (angle == TEST_ANGLE[angleIndex])
    {
      for (int index = 0; index < SERVO_COUNT; index++)
        TEST_ASSERT_EQUAL_INT(angle, servoArray[index].read());
      angleIndex++;
      break;
    }
    delay(100);
  }

  for (int index = 0; index < SERVO_COUNT; index++)
    servoArray[index].write(MIN_ANGLE);
}

// PRIMARY CONCEPTS
/*
1. Digital pins are required for outputting instructions to servos.


*/

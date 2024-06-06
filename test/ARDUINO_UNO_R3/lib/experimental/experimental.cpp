// DESCRIPTION
/*
This program is designed to test the range of motion on a 180 degree servo.

It will set up a servo, and then increment an angle value from 0 to 180.

For each increment, the program will write the angle value to the servo.

Once the angle value reaches 180 degrees, the servo position will be set back to 0 degrees.
*/


// INPUT
// digital pin, angle value


// PROCESS
/*
1. Initialize a pin and an angle value.
2. Create a loop starting at an angle value of 0:
  a. Write the value of the angle to the pin.
  b. Increment the angle value.
  c. Break once the loop reaches 180.
3. Write an angle value of 0 to the pin.
*/


// OUTPUT
// servo movement


//**************** TEST START ****************


// HEADER FILE/PREPROCESSOR LIBRARY INITIALIZATION
#include <Arduino.h>
#include <Servo.h>
#include <unity.h>

// FUNCTION PROTOTYPES
int getUserInput();

void test_pinSetup();
void test_precision();
void test_range();
void test_interval();

// TEST SETUP
void setUp(void)
{

}

  
// TEST TEARDOWN
void tearDown(void)
{

}

// CONSTANT PIN INITIALIZATION
// N/A;

// GLOBAL SERVO INITIALIZATION
Servo servo;

// CONSTANT VALUES INITIALIZATION
const int MIN_ANGLE = 0;
const int MAX_ANGLE = 180;


// ARRAY INITIALIZATION
int testAngle[] = { 0, 30, 60, 90, 120, 150, 180 };
int testAngleElementCount = sizeof(testAngle)/sizeof(testAngle[0]);
int index = 0;


// TEST CONSTANTS
const int rotations = 3;


// DECLARATION
int setupComplete;

int angle;

int servoCount;

int digitalPin;
int pinToAttach;

int initialInput = 0;


// SETUP FUNCTION INITIALIZATION
void setup() {

  // BOARD STARTUP DELAY (MINIMUM 2000)
  delay(2000);

	// MONITOR SPEED
	Serial.begin(115200);

	// INPUT
  Serial.println("SERVO TESTING PROGRAM (UNO)");
  Serial.println("How many servos are you testing?");

  servoCount = getUserInput();

  initialInput = 1;

  // TODO: VERIFY INTEGER

  // SERVO INITIALIZATION
  Servo testServo[servoCount];
  int servoPin[servoCount];

  digitalPin = servoPin[servoCount];
  servo = testServo[servoCount];

  for (int count = 1; count <= servoCount; count++)
  {
    Serial.print("SERVO: ");
    Serial.print(count);

    Serial.println();
    Serial.println();

    Serial.print("Which DIGITAL pin is this servo connected to?");
    pinToAttach = getUserInput();
    servoPin[count] = pinToAttach;

    testServo[count].attach(pinToAttach);

    Serial.println();
    Serial.println();

   // TODO: VERIFY INTEGER
  }

  // STARTING POSITION
  for (int count = 0; count < servoCount; count++)
    testServo[count].write(MIN_ANGLE);

	// TEST BEGIN
	UNITY_BEGIN();

  for (int servoIndex = 0; servoIndex < servoCount; servoIndex++)
  {
    servo = testServo[servoIndex];

    RUN_TEST(test_pinSetup);
    RUN_TEST(test_range);
    RUN_TEST(test_interval);
    RUN_TEST(test_precision);
    RUN_TEST(test_range);
  }

}

// LOOP FUNCTION INITIALIZATION
void loop()
{
  // TEST END
  UNITY_END();
}

//**************** TEST END ****************

// FUNCTION DEFINITIONS

int getUserInput()
{

  const int STRING_SIZE = 32;

  char consoleString[STRING_SIZE];
  int stringIndex = 0;

  bool inputComplete = 0;
  char charRead;

  int intInput;

  while (!inputComplete && Serial.available() > 0)
  {
    charRead = Serial.read();

    if (charRead != '\n')
    {

      consoleString[stringIndex] = charRead;
      stringIndex++;

      if (stringIndex >= STRING_SIZE)
        stringIndex = STRING_SIZE - 1;
    }

    else
    {
      inputComplete = 1;
      consoleString[stringIndex] = '\0';
    }
  }

  intInput = atoi(consoleString);

  return intInput;
  
}

void test_servoAttached()
{
  for (int count = 0; count < servoCount; count++)
  {
  
    Servo attachedServo;
    attachedServo = servo;

    TEST_ASSERT(attachedServo.attached());
  }
}


void test_pinSetup()
{
  digitalWrite(digitalPin, HIGH);
  TEST_ASSERT_EQUAL(HIGH, digitalRead(digitalPin));

  delay(1000);

  digitalWrite(digitalPin, LOW);
  TEST_ASSERT_EQUAL(LOW, digitalRead(digitalPin));
}


void test_precision()
{
  for (angle = MIN_ANGLE; angle < MAX_ANGLE; angle++)
  {
    servo.write(angle);

    while (angle == testAngle[index])
    {
      TEST_ASSERT_EQUAL_INT(angle, servo.read());
      index++;
      break;
    }

    delay(100);

  }

  for (angle = MAX_ANGLE; angle > MIN_ANGLE; angle--)
  {
    servo.write(angle);

    while (angle == testAngle[index])
    {
      TEST_ASSERT_EQUAL_INT(angle, servo.read());
      index++;
      break;
    }
    delay(100);
  }
  servo.write(MIN_ANGLE);
}

void test_range()
{
  for (int count = 0; count < rotations; count++)
  {
    servo.write(MIN_ANGLE);
    TEST_ASSERT_EQUAL_INT(MIN_ANGLE, servo.read());

    delay(2000);

    servo.write(MAX_ANGLE);
    TEST_ASSERT_EQUAL_INT(MAX_ANGLE, servo.read());
    
    delay(2000);
  }

  servo.write(MIN_ANGLE);

}

  

void test_interval()
{
  for (int count = 0; count < (testAngleElementCount); count++)
  {

    servo.write(testAngle[count]);

    TEST_ASSERT_EQUAL_INT(testAngle[count], servo.read());

    delay(1000);
  }

  for (int count = testAngleElementCount - 1; count > (-1); count--)
  {

  servo.write(testAngle[count]);

  TEST_ASSERT_EQUAL_INT(testAngle[count], servo.read());

  delay(1000);
  }

  servo.write(MIN_ANGLE);
}

// PRIMARY CONCEPTS
/*
1. Digital pins are required to manipulate servos.
*/
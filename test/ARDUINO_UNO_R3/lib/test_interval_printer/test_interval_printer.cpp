// DESCRIPTION
/*
This program is designed to test a printing interval without having to interrupt all program functions using delay().

It will initialize a value using the millis() function which will return the number of milliseconds elapsed since the program began.

It will then compare this value against a designated interval.

If the modulus of the time elapsed and the interval value is 0, then the program will print a message to the serial monitor.
*/


// INPUT
// message, time interval


// PROCESS
/*
1. Initialize a set interval.
2. In the program loop:
    a. Get the number of milliseconds elapsed since the program began.
    b. Get the modulus of the milliseconds elapsed and the interval.
    c. If the modulus is equal to 0, print a message to the serial display.
*/


// OUTPUT
// message (based on interval)


//**************** TEST START ****************


// FUNCTION PROTOTYPES
void test_print();
bool checkConditions();

// CONSTANT INITIALIZATION
const int TIME_INTERVAL = 2000;

const int PRINT_LIMIT = 20;


	
// DECLARATIONS
int timeBuffer;
int timeModulus;

int serialOutputMax;
int serialOutputCount;
int totalPrintCount = 0;

const int BUFFER_SIZE = 100;
char outputBuffer [BUFFER_SIZE] = {};

const char EXAMPLE_MESSAGE[BUFFER_SIZE] = {"ONE SECOND HAS PASSED!"};

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


// SETUP FUNCTION INITIALIZATION
void setup() {

	// SETUP DELAY
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


	// OUTPUT
    RUN_TEST(test_print);

	// TEST END
	UNITY_END();

}

//**************** TEST END ****************

// FUNCTION DEFINITIONS
void test_print()
{
    while (totalPrintCount < PRINT_LIMIT)
    {
        timeBuffer = millis();
        timeModulus = timeBuffer % TIME_INTERVAL;

        if (checkConditions())
        {
            sprintf(outputBuffer, EXAMPLE_MESSAGE);
            TEST_ASSERT_EQUAL_STRING(EXAMPLE_MESSAGE, outputBuffer);
            Serial.println(outputBuffer);

            totalPrintCount++;
            serialOutputCount++;
        }
    }
}

bool checkConditions()
{
    int evaluation = 1;

    if (timeModulus != 0)
        evaluation = 0;

    if (timeModulus >= 0 && timeModulus <= 25)
    {
        serialOutputMax = 1;
    }
    else
    {
        serialOutputCount = 0;
        serialOutputMax = 0;
    }

    if (serialOutputCount >= serialOutputMax)
    {
        evaluation = 0;
    }

    return evaluation;
}

// PRIMARY CONCEPTS
/*



*/

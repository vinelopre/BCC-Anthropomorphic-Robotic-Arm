#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <unity.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

void test_chip_call (void){
    bool test = radio.begin();
    TEST_ASSERT_EQUAL(test, true);
}

void setup() {
    delay(2000);
    UNITY_BEGIN();
    RUN_TEST(test_chip_call);
}

void loop() {
}

#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <unity.h>
#include <binary.h>

RF24 radio(7, 8); // CE, CSN
const byte ADDRESS = B000001;
int TEST_DATA[10] = {0,1,2,3,4,5,6,7,8,9};

void test_chip_call (void){
    bool test = radio.begin();
    Serial.println(test);
    TEST_ASSERT_EQUAL(test, true);   
}

void test_byte_address(void){
    radio.openWritingPipe(ADDRESS);

    //switched from protected to public in RF24.h line 148 in order to use read_register.
    byte test = radio.read_register(RX_ADDR_P0);
    Serial.println(test);
    TEST_ASSERT_EQUAL_MEMORY(ADDRESS, test, sizeof(ADDRESS));

    test = radio.read_register(TX_ADDR);
    Serial.println(test);
    TEST_ASSERT_EQUAL_MEMORY(ADDRESS, test, sizeof(ADDRESS));
}

void test_write(void){
    radio.begin();
    radio.setPALevel(RF24_PA_MIN);
    radio.stopListening();
    radio.openWritingPipe(0xF0F0F0F0F0);

    int valueInPtr = 55;
    int *ptr;
    
    bool test;
    for(int i = 0; i <10; i++){
        ptr = &valueInPtr;;

        test = radio.write(ptr, sizeof(ptr));  
        Serial.println(test);
        TEST_ASSERT_EQUAL(test, true);
        TEST_ASSERT_EQUAL_INT(i, (RX_ADDR_P0 + i));
        TEST_ASSERT_EQUAL_INT(i, (TX_ADDR + i));  
    }
}

void setup() {
    delay(2000);
    Serial.begin(115200);
    UNITY_BEGIN();
    RUN_TEST(test_chip_call);
    RUN_TEST(test_byte_address);
    RUN_TEST(test_write);
    radio.setPALevel(RF24_PA_MIN);
}

void loop() {
    UNITY_END();
}


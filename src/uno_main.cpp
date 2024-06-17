#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

uint8_t analog1;
Servo servo1;

void setup() {
  radio.begin();
  radio.openReadingPipe(0,address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  analog1 = 0;
  servo1.attach(4);
}

void loop() {
    radio.read(&analog1, sizeof(analog1));
    servo1.write(analog1);
}
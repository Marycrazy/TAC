#include <Arduino.h>

void set_flag();

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), set_flag, RISING);
}

void loop() {}

void set_flag() {
  static int counter = 0;
  static unsigned long last_interrupt_time = 0;
  if (millis() - last_interrupt_time > 50) {
    Serial.println(++counter);
    last_interrupt_time = millis();
  }
}
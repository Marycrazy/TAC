#include <Arduino.h>
#include <TimerOne.h>

// prototype
void sensor();

void setup() {
  Serial.begin(9600);
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(sensor);
}

void loop() {}

void sensor() {
  float temperature = ((analogRead(A0) * 5.0 / 1024.0) - 0.01) * 100.0;
  Serial.print(temperature);
  Serial.println("°C");
}
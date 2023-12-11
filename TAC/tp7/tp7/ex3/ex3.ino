#include <Arduino.h>
#include <TimerOne.h>

// prototype
void sensor_print();

// global variables
  float min_temperature = 100;
  float max_temperature = 0;
  float sum_temperature = 0;

void setup() {
  Serial.begin(9600);
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(sensor_print);
}

void loop() {
  static unsigned long time = 0;
  if (millis() - time > 60000) {
    Serial.println("--------------------");
    Serial.print("min: ");
    Serial.print(min_temperature);
    Serial.println("°C");
    Serial.print("max: ");
    Serial.print(max_temperature);
    Serial.println("°C");
    Serial.print("avg: ");
    Serial.print(sum_temperature / 60);
    Serial.println("°C");
    Serial.println("--------------------");
    Serial.println();
    min_temperature = 100;
    max_temperature = 0;
    sum_temperature = 0;
    time = millis();
  }
}

void sensor_print() {
  float temperature = ((analogRead(A0) * 5.0 / 1024.0) - 0.5) * 100;
  if (temperature < min_temperature) {
    min_temperature = temperature;
  }
  if (temperature > max_temperature) {
    max_temperature = temperature;
  }
  sum_temperature += temperature;
}
#include <Servo.h>

Servo servo;

void setup() {
  servo.attach(9);
}

void loop() {
  int angle = map(analogRead(A0), 0, 1023, 0, 180);
  servo.write(angle);
}
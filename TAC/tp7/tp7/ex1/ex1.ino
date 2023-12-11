#include <TimerOne.h>

// prototype
void blink_timer();
void blink_millis();

void setup() {
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(blink_timer);
}

void loop() {
  blink_millis();
}

void blink_timer() {
  static bool is_on = false;
  digitalWrite(7, !is_on);
  is_on = !is_on;
}

void blink_millis() {
  static unsigned long time = 0;
  if (millis() - time > 300) {
    digitalWrite(8, !digitalRead(8));
    time = millis();
  }
}
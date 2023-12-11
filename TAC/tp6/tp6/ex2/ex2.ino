unsigned long time1 = millis();
unsigned long time2 = millis();

void blink1(int pin, unsigned long delayTime) {
  if (millis() - time1 < delayTime) {
    digitalWrite(pin, HIGH);
  } else if (millis() - time1 < delayTime * 2) {
    digitalWrite(pin, LOW);
  } else {
    time1 = millis();
  }
}

void blink2(int pin, unsigned long delayTime) {
  if (millis() - time2 < delayTime) {
    digitalWrite(pin, HIGH);
  } else if (millis() - time2 < delayTime * 2) {
    digitalWrite(pin, LOW);
  } else {
    time2 = millis();
  }
}

void setup() {
  for (int i = 7; i <= 8; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  blink1(7, 1000);
  blink2(8, 300);
}
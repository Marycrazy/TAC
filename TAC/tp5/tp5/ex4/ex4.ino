enum class LED_STATE {
  ON,
  OFF,
  FADEIN,
  FADEOUT
};

// prototypes
void state_machine();
LED_STATE check_on(unsigned long &time);
LED_STATE check_off(unsigned long time);
LED_STATE check_fadein(unsigned long time);
LED_STATE check_fadeout(unsigned long time);

void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
}

void loop() {
  state_machine();
}

LED_STATE check_on(unsigned long &time) {
  time = millis();
  digitalWrite(3, HIGH);
  return LED_STATE::OFF;
}

LED_STATE check_off(unsigned long time) {
  if (millis() - time > 2000) {
    digitalWrite(3, LOW);
    return LED_STATE::FADEIN;
  }
  return LED_STATE::OFF;
}

LED_STATE check_fadein(unsigned long time) {
  if (millis() - time > 4000) {
    for (int i = 0; i <= 255; i++) {
      analogWrite(3, i);
      delay(10);
    }
    return LED_STATE::FADEOUT;
  }
  return LED_STATE::FADEIN;
}

LED_STATE check_fadeout(unsigned long time) {
  for (int i = 255; i >= 0; i--) {
    analogWrite(3, i);
    delay(10);
  }
  return LED_STATE::ON;
}

void state_machine() {
  static unsigned long time = millis();
  static LED_STATE state = LED_STATE::ON;
  switch (state)
  {
  case LED_STATE::ON: state = check_on(time);
    break;
  case LED_STATE::OFF: state = check_off(time);
    break;
  case LED_STATE::FADEIN: state = check_fadein(time);
    break;
  case LED_STATE::FADEOUT: state = check_fadeout(time);
    break;
  default: Serial.println("ERROR: Invalid state");
    break;
  }
}
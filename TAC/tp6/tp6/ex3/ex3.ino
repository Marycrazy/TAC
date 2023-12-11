int sensor;
unsigned long time;
bool state = false;

void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT); // buzzer
  pinMode(7, INPUT); // pir sensor
}

void loop() {
  sensor = digitalRead(7);
  if (sensor == HIGH) {
    time = millis();
    if (state == false) {
      Serial.println("Motion detected!");
      state = true;
    }
    digitalWrite(3, HIGH);
  } else {
    if (state == true) {
      Serial.println("Motion stopped!");
      state = false;
    }
    if (millis() - time >= 10000) {
      digitalWrite(3, LOW);
    }
  }
}
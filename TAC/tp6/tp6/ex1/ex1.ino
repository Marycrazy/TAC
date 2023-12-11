unsigned writeTime = 0;
unsigned readTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(4, INPUT);
}

void loop() {
  unsigned long time = micros();
  digitalWrite(4, HIGH);
  writeTime = micros() - time;
  Serial.print("Write time: ");
  Serial.println(writeTime);
  time = micros();
  digitalRead(4);
  readTime = micros() - time;
  Serial.print("Read time: ");
  Serial.println(readTime);
  delay(1000);
}
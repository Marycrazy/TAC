// TAC (Tecnologias e Arquitetura de Computadores)
// Trabalho 4 - Exercício 2 - Grupo 5 - 30/03/2023
// António Dinis
// Francisco Figueiras
// Mariana Magalhães

void setup() {
  pinMode(7, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  if (sensorValue > 600) {
    digitalWrite(7, HIGH);
  } else {
    digitalWrite(7, LOW);
  }
  delay(100);
}
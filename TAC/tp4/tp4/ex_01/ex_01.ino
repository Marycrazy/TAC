// TAC (Tecnologias e Arquitetura de Computadores)
// Trabalho 4 - Exercício 1 - Grupo 5 - 30/03/2023
// António Dinis
// Francisco Figueiras
// Mariana Magalhães

void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  delay(100);
}
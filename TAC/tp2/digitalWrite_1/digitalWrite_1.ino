// TAC (Tecnologias e Arquitetura de Computadores)
// Trabalho 2 - Exercício 1 - Grupo 5 - 09/03/2023
// António Dinis
// Francisco Figueiras
// Mariana Magalhães

void setup() {
  for (int i = 2; i < 6; i++)
    pinMode(i, OUTPUT);
}

void loop() {
  for (int i = 2; i < 6; i++) {
    digitalWrite(i, HIGH);
    delay(500);
    digitalWrite(i, LOW);
  }
}
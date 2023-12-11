// TAC (Tecnologias e Arquitetura de Computadores)
// Trabalho 2 - Exercício 2 - Grupo 5 - 09/03/2023
// António Dinis
// Francisco Figueiras
// Mariana Magalhães

void setup() {
  for (int i = 2; i < 6; i++)
    pinMode(i, OUTPUT);
}

void loop() {
  for (int i = 0; i < 16; i++) {
      digitalWrite(2, i&1);
      digitalWrite(3, i&2);
      digitalWrite(4, i&4);
      digitalWrite(5, i&8);
    delay(1000);
  }
}
// TAC (Tecnologias e Arquitetura de Computadores)
// Trabalho 1 - Exercício 2 - Grupo 5 - 02/03/2023
// António Dinis
// Francisco Figueiras
// Mariana Magalhães

#define ledRed 13
#define ledBlue 12

void setup()
{
  pinMode(ledRed, OUTPUT);
  pinMode(ledBlue, OUTPUT);
}

void loop()
{
  digitalWrite(ledRed, HIGH);
  delay(10000); // Wait for 10s
  digitalWrite(ledRed, LOW);
  digitalWrite(ledBlue, HIGH);
  delay(10000); // Wait for 10s
  digitalWrite(ledBlue, LOW);
}
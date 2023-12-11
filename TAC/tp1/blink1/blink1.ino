// TAC (Tecnologias e Arquitetura de Computadores)
// Trabalho 1 - Exercício 1 - Grupo 5 - 02/03/2023
// António Dinis
// Francisco Figueiras
// Mariana Magalhães

#define ledRed 13

void setup()
{
  pinMode(ledRed, OUTPUT);
}

void loop()
{
  digitalWrite(ledRed, HIGH);
  delay(1000); // Wait for 1s
  digitalWrite(ledRed, LOW);
  delay(1000); // Wait for 1s
}
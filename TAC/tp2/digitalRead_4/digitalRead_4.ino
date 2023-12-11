// TAC (Tecnologias e Arquitetura de Computadores)
// Trabalho 2 - Exercício 4 - Grupo 5 - 09/03/2023
// António Dinis
// Francisco Figueiras
// Mariana Magalhães

int buttonState;
int counter = 0;

void setup() {
  for (int i = 8; i < 12; i++)
    pinMode(i, OUTPUT);
  pinMode(13, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {

  buttonState = digitalRead(13);
  Serial.println("...");
  
  if (buttonState == LOW) {
    counter++;
    delay(500);
  } else if (counter > 15) {
    counter = 0;
  }

  digitalWrite(8, counter&1);
  digitalWrite(9, counter&2);
  digitalWrite(10, counter&4);
  digitalWrite(11, counter&8);
  
  Serial.println(counter);
}
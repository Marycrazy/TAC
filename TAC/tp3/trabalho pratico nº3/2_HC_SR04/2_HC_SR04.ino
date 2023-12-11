// TAC (Tecnologias e Arquitetura de Computadores)
// Trabalho 3 - Exercício 2 - Grupo 5 - 23/03/2023
// António Dinis
// Francisco Figueiras
// Mariana Magalhães

void digital_delay(int i) {
  digitalWrite(6, LOW);
  digitalWrite(5, HIGH);
  noTone(2);
  delay(i);
  tone(2, 500);
}

void setup() {
  pinMode(6, OUTPUT); // more than 50
  pinMode(5, OUTPUT); // less than 50
  pinMode(4, OUTPUT);
  pinMode(3, INPUT);
  pinMode(2, OUTPUT);
  digitalWrite(6, HIGH);
  Serial.begin(9600); 
}

void loop() {
  digitalWrite(4, LOW);  
	delayMicroseconds(2);  
	digitalWrite(4, HIGH);  
	delayMicroseconds(10);  
	digitalWrite(4, LOW);  

  float duration = pulseIn(3, HIGH);
  float distance = duration * 0.034 / 2;

  if (distance < 10) {
  digitalWrite(6, LOW);
  digitalWrite(5, HIGH);
  tone(2, 500);
  } else if (distance < 25) {
    digital_delay(1000);
  } else if (distance < 50) {
    digital_delay(2000);
  } else {
    digitalWrite(6, HIGH);
    digitalWrite(5, LOW);
    noTone(2);
  }

  Serial.print("Distance: ");  
	Serial.println(distance);  
	delay(100);  
}
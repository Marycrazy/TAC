// TAC (Tecnologias e Arquitetura de Computadores)
// Trabalho 3 - Exercício 1 - Grupo 5 - 23/03/2023
// António Dinis
// Francisco Figueiras
// Mariana Magalhães

void digital_delay(int d) {
  noTone(2);
  delay(d);
  tone(2, 500);
}

void setup() {
  pinMode(4, OUTPUT);
  pinMode(3, INPUT);
  pinMode(2, OUTPUT);
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
    digitalWrite(2, HIGH);
  } else if (distance < 25) {
    digital_delay(1000);
  } else if (distance < 50) {
    digital_delay(2000);
  } else noTone(2);

  Serial.print("Distance: ");  
	Serial.println(distance);  
	delay(100);  
}
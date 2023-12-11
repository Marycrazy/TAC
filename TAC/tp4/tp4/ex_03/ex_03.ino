// TAC (Tecnologias e Arquitetura de Computadores)
// Trabalho 4 - Exercício 3 - Grupo 5 - 30/03/2023
// António Dinis
// Francisco Figueiras
// Mariana Magalhães

int sensorPin = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int reading = analogRead(sensorPin);
  float voltage = reading * 5.0;
  voltage /= 1024.0; 
  
  Serial.print("Voltage: ");
  Serial.println(voltage);

  float temperatureC = (voltage - 0.5) * 100 ;

  Serial.print(temperatureC);
  Serial.println(" degrees C");

  delay(1000);
}
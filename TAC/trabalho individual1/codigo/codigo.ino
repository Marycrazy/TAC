int estado=1;
unsigned long tempo; 
int sensor(){
  digitalWrite(9, LOW);
    delayMicroseconds(2);
    // Sets the trigPin  on HIGH state for 10 micro seconds
    digitalWrite(9, HIGH);
    delayMicroseconds(10);
    digitalWrite(9, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    float duration = pulseIn(10, HIGH);
        // Calculating the distance
    float distance = duration * 0.034 / 2;
  Serial.println(distance);
    // Prints the distance on the Serial Monitor
    return distance;
}
void inicial(){
  digitalWrite(2, HIGH);//vermelho para os peões
  digitalWrite(3, LOW);//verde para os peões
  digitalWrite(5, LOW);//amarelo veiculos
  digitalWrite(4, LOW);// vermelho veiculos
  digitalWrite(7, HIGH);//verde veiculos 
  digitalWrite(13, LOW);
}
int carros( unsigned long tempo) {
  Serial.print("entrou"); 
  if((millis()-tempo)>= 2000 && digitalRead(7)==HIGH){
    digitalWrite(5, HIGH);//amarelo veiculos
    digitalWrite(7, LOW);//verde veiculos
  }
  else
  if((millis()-tempo)>= 4000 && digitalRead(5)==HIGH){
  digitalWrite(5, LOW);//amarelo veiculos
  digitalWrite(4, HIGH);// vermelho 
  Serial.print("milli: ");
  Serial.println(tempo);
  Serial.print("tempo: ");
  Serial.println((millis()-tempo));
  return 3;
  } 
  return 2;
}
int peoes(unsigned long tempo){
  
 if((millis()-tempo)>= 6000 && digitalRead(4)==HIGH){
   led_intermitente();
    digitalWrite(3, HIGH);//verde peoes
    digitalWrite(2, LOW);//vermelho peoes
  }
  if((millis()-tempo)>= 16000 && digitalRead(4)==HIGH){
    inicial(); 
  Serial.print("peoes: ");
  Serial.println(millis());
  Serial.print("peoes: ");
  Serial.println((millis()-tempo));
  return 1;
  } 
  
  return 3;
} 

void led_intermitente(){
  unsigned long millisTarefa1 = millis();
  int sensorValue = analogRead(A0);
  
  Serial.print("luz: ");
  Serial.println(sensorValue);
  if (sensorValue >= 800) {
    if((millis() - millisTarefa1) < 6500){
    // Acende o led do pino 13
    digitalWrite(13, !digitalRead(13));

  }
  }
  else 
  digitalWrite(13,LOW);
  }
  
void setup() {
  pinMode(2,OUTPUT);//vermelho para os peões
  pinMode(3,OUTPUT);//verde para os peões
  pinMode(4, OUTPUT);// vermelho veiculos
  pinMode(5, OUTPUT);//amarelo veiculos
  pinMode(7, OUTPUT);//verde veiculos
  pinMode(9, OUTPUT); // Sets the trigPin  as an Output
  pinMode(10, INPUT); // Sets the echoPin as an Input
  pinMode(13, OUTPUT);
  inicial();
  Serial.begin(9600);
}

void loop() { 
switch (estado)
  {
  case 1:
  Serial.println("estado ");
  if(sensor() < 30){
    tempo=millis();
    Serial.println(estado);
    estado=2;
    Serial.println(estado);    
      }
    break;
  case 2:
    Serial.println("estado");
    estado = carros(tempo);        
    break;
  case 3:
    Serial.println("entr");
    estado = peoes(tempo); 
      
    break;
  }
}
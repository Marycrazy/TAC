#define temperaturePin A0    // Pino analógico para leitura da temperatura
#define yellowLed  5        // Pino para o LED amarelo
#define redLed 6
#define poten1  A1         //potenciometro 1
#define poten2 A2         //potenciometro 2
#define buzzer 4         //buzzer
#define switch1 2         // botao 1
#define switch2 3          //botao 2
#define displayPinA 7
#define displayPinB 8
#define displayPinC 9
#define displayPinD 10
#define displayPinE 11
#define displayPinF 12
#define displayPinG 13
float min_temperature = 100;
float max_temperature = 0;
float sum_temperature = 0;
bool reset =false;
int estado=1;
int temperatura(){
    static unsigned long time = 0;
    if (millis()-time>=15000)
    {
       float temperature = map(analogRead(A0), 0, 1023, -49, 448);
      	Serial.print(temperature);
		Serial.println("C");  
      if (temperature < min_temperature) {
            min_temperature = temperature;
        }
      else if (temperature > max_temperature) {
            max_temperature = temperature;
        }
           sum_temperature += temperature;
      time=millis();
      return temperature; 
    } 
    
}
void led_intermitente(){
    static unsigned long time = 0;
    int value = map(analogRead(poten1), 0, 1023, 1000, 10000);	
    if (millis() - time >= value) {
        Serial.println("entrou"); 
    digitalWrite(yellowLed, !digitalRead(yellowLed));
       time = millis();
    }
}

void setup() {
    for (int i = 4; i <= 13; i++){
        pinMode(i,OUTPUT);
    }
    for (int i = 2; i <= 3; i++)
        pinMode(i , INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(switch1), botao1, FALLING);
    Serial.begin(9600);
}
void botao1(){
    Serial.println("enu");
    digitalWrite(redLed,LOW);
}
void display(int conta){
static const byte NUMBERS[][7] = {
  {1,1,1,1,1,1,0}, // 0
  {0,1,1,0,0,0,0}, // 1 
  {1,1,0,1,1,0,1}, // 2 
  {1,1,1,1,0,0,1}, // 3  
  {0,1,1,0,0,1,1}, // 4  
  {1,0,1,1,0,1,1}, // 5 
  {1,0,1,1,1,1,1}, // 6 
  {1,1,1,0,0,0,0}, // 7   
  {1,1,1,1,1,1,1}, // 8  
  {1,1,1,1,0,1,1}  // 9  
  };
  for (int i = 0; i < 7; i++){
    digitalWrite(displayPinA + i, NUMBERS[conta][i]);
    
  } 
}
int avisos() {
    static int conta = 0;
    if (reset)
    {
        conta=0;
        display(conta);
        reset=false;
        return 1;
    }
    static unsigned long start = millis();
    int temp = map(analogRead(poten2), 0, 1023, 0, 50); // Armazena o valor da temperatura
    if (temperatura() >= temp) {
        
        digitalWrite(redLed, HIGH);
        tone(buzzer, 1000,5000);
        conta++;
        display(conta);
    }
    return 1;
}
void loop() {
   
switch (estado)
{
case 1:
    static unsigned long time = 0;
    led_intermitente();
    if (millis()-time>60000)
    {
        Serial.println("--------------------");
        Serial.print("min: ");
        Serial.print(min_temperature);
        Serial.println("C");
        Serial.print("max: ");
        Serial.print(max_temperature);
        Serial.println("C");
        Serial.print("avg: ");
        Serial.print(sum_temperature / 4);
        Serial.println("C");
        Serial.println("--------------------");
        Serial.println();
    time = millis();
    
    }
    estado =2;
    break;
case 2:
    if (!digitalRead(switch1) && !digitalRead(switch2))
        {
            reset=true;
        }
    estado =avisos();
    break;
}  
}
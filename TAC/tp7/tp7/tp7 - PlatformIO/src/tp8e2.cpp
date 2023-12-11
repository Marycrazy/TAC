#include <Arduino.h>
int c=0;
void setup()
{
 Serial.begin(9600);
 pinMode(2, INPUT_PULLUP);
 attachInterrupt(0,conta,FALLING );
}

void loop()
{
 
}
void conta(){
    c++;
    Serial.print(c);
}

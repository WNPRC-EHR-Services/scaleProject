#include <Arduino.h>

int led = 13;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    //Serial1.begin(9600);
    pinMode(led,OUTPUT);
}

void loop() {
    // put your main code here, to run repeatedly:
    int temp;
    //Serial1.println("waiting for command ");
    if(Serial.available())
      {
        temp=Serial.read();
          if(temp=='V'){
              digitalWrite(led,1-digitalRead(led));
              delay(1000);
            //  Serial.println("OK");
              Serial.println((char)temp);
            //  Serial.println(temp);
            }
          }
}

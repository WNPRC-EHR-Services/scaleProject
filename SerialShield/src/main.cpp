#include <Arduino.h>

const byte numChars = 24;
char receivedChars[numChars];

boolean newData = false;

int led = 13;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    Serial.println("Arduino Ready Shield");
    Serial1.begin(9600);
    pinMode(led,OUTPUT);
}


// void loop() {
//     // put your main code here, to run repeatedly:
//     int temp;
//     //Serial1.println("waiting for command ");
//     if(Serial.available())
//       {
//         temp=Serial.read();
//
//               digitalWrite(led,1-digitalRead(led));
//               delay(250);
//             //  Serial.println("OK");
//               Serial.println((char)temp);
//             //  Serial.println(temp);
//             }
//
// }



void recvWithEndMarker(){
  static byte ndx = 0;
  char endMarker = '\r';
  char newLine = '\n';

//buffer for end on transmission
  int temp1;
  //int temp2;

  while (Serial1.available() > 0 && newData == false){
    temp1 = Serial1.read();
    //Serial.print((char)temp1);
    //temp2 = Serial.read();
    //Serial.print((char)temp2);

    if (temp1 == newLine && receivedChars[ndx-1] == endMarker){
      receivedChars[ndx] = '\0';
      ndx = 0;
      newData = true;
      //Serial.println("test");

    }
    else {
      receivedChars[ndx]=temp1;
      //receivedChars[ndx++]=temp1;
      ndx++;
      if (ndx>=numChars){
        ndx = numChars - 1;
      }


    }

  }

}

void showNewData(){
  if (newData == true){
    //Serial.print("This just in");
    String wholeMessage = String (receivedChars);
    //Serial.println(wholeMessage);
    if (wholeMessage.indexOf("0.0000 kg") == -1){
      Serial.println(receivedChars);
      newData = false;
    }
    else {
      newData = false;
    }

  }
}

void loop(){
  recvWithEndMarker();
  showNewData();
}

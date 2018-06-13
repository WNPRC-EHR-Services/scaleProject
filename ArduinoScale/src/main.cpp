#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10,11);

const byte numChars = 32;
char receivedChars[numChars]; // an array to store the received data

boolean newData = false;

void setup() {
 Serial.begin(9600);
 Serial.println("<Arduino is ready>");
 mySerial.begin(9600);
}

void loop() {
 recvWithEndMarker();
 showNewData();
}

void recvWithEndMarker() {
   static byte ndx = 0;
   char endMarker = '1';
   char rc;

   // if (Serial.available() > 0) {
   while (mySerial.available() > 0 && newData == false) {
     rc = mySerial.read();

     if (rc != endMarker) {
         receivedChars[ndx] = rc;
         //Serial.println(rc, BIN);
         ndx++;
     if (ndx >= numChars) {
       ndx = numChars - 1;
     }
     }
     else {
     receivedChars[ndx] = '1'; // terminate the string
     ndx = 0;
     newData = true;
     }
   }
}

void showNewData() {
 if (newData == true) {
   Serial.print("This just in ... ");
   Serial.println(receivedChars);
   newData = false;
 }
}

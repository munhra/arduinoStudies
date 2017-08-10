#include <SoftwareSerial.h>

SoftwareSerial mySerial(0, 1); // RX, TX  
// Connect HM10      Arduino Uno
//     Pin 1/TXD          Pin 7
//     Pin 2/RXD          Pin 8

void setup() {  
  Serial.begin(115200);
  // If the baudrate of the HM-10 module has been updated,
  // you may need to change 9600 by another value
  // Once you have found the correct baudrate,
  // you can update it using AT+BAUDx command 
  // e.g. AT+BAUD0 for 9600 bauds
  Serial.println("Hail to Bluetooth !");
  mySerial.begin(115200);
}

void loop() {  
  delay(500);
  //mySerial.print("Hello From Bluetooth !");
  /*
  char c;
  if (Serial.available()) {
    Serial.println("Read Serial !");
    c = Serial.read();
    mySerial.print(c);
  }
  if (mySerial.available()) {
    c = mySerial.read();
    Serial.println("Write Serial !");
    Serial.print(c);    
  }*/
}

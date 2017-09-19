
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display //3F

int sumTest = 0;

//ADDRESS PINS

int ADDRESS_0 = 30;
int ADDRESS_1 = 31;
int ADDRESS_2 = 32;
int ADDRESS_3 = 33;
int ADDRESS_4 = 34;
int ADDRESS_5 = 35;
int ADDRESS_6 = 36;
int ADDRESS_7 = 37;
int ADDRESS_8 = 38;
int ADDRESS_9 = 39;
int ADDRESS_10 = 40;
int ADDRESS_11 = 41;
int ADDRESS_12 = 42;
int ADDRESS_13 = 43;
int ADDRESS_14 = 44;

int addressPins[] = {ADDRESS_0, ADDRESS_1, ADDRESS_2, ADDRESS_3, ADDRESS_4, ADDRESS_5, ADDRESS_6,
                     ADDRESS_7, ADDRESS_8, ADDRESS_9, ADDRESS_10, ADDRESS_11, ADDRESS_12, ADDRESS_13,
                     ADDRESS_14};

//DATA

int IO_1 = 51;
int IO_2 = 52;
int IO_3 = 53;
int IO_4 = 28;
int IO_5 = 26;
int IO_6 = 13;
int IO_7 = 12;
int IO_8 = 11;

int ioPins[] = {IO_1,IO_2,IO_3,IO_4,IO_5,IO_6,IO_7,IO_8};

//Control

int CS = 8; 
int OE = 9; 
int WE = 10;

int maxAddressNumber = 16; //32768;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  lcd.init();   
  delayMicroseconds(10);
  lcd.backlight();
  
  //writeTest();
  readTest();
  //writeAndCheck();
}

void loop() {
  // put your main code here, to run repeatedly:
  //lcd.setCursor(0,0);
  //lcd.print("TESTE");
  //lcd.setCursor(0,1);
  //lcd.print("TESTE 2");

  sumTest = sumTest + 1;

  
  lcd.setCursor(0,0);
  lcd.print("SUM = "+String(sumTest));
  lcd.setCursor(0,1);
  lcd.print("TESTE 2");

  //delay(100);
}

void writeAndCheck() {
  delay(2000);
  Serial.println("******** Write Test ... *********");
  pinMode(CS, OUTPUT);
  pinMode(WE, OUTPUT);
  
  for (int d = 0 ; d < 8 ; d++) {
    pinMode(ioPins[d], OUTPUT); 
  }

  
  
  //16384
  for (int j = 0 ; j < maxAddressNumber ; j++) {
    
    digitalWrite(CS,LOW);
    digitalWrite(WE,LOW);
  
    for (int ad = 0 ; ad < 13 ; ad++ ) {
      digitalWrite(addressPins[ad],LOW);
    }

    
    String binaryRepresentation = "";  
    int num = j;
    for (int i = 0 ; i < 14 ; i++) {
        //int num = j;
        if (num % 2) {
          binaryRepresentation = "1" + binaryRepresentation;  
          digitalWrite(addressPins[i],HIGH);
        }else{
          binaryRepresentation = "0" + binaryRepresentation;  
          digitalWrite(addressPins[i],LOW);
        }
        num = num / 2;
    }
    //delay(100);
    //delayMicroseconds(100);
    delayMicroseconds(10);
    //Write FF on IO
    for (int d = 0 ; d < 8 ; d++) {
      if (d < 4)
        digitalWrite(ioPins[d],LOW);
      else
        digitalWrite(ioPins[d],HIGH);
    }

    delayMicroseconds(10);
    //delay(100);
    digitalWrite(CS,HIGH);
    digitalWrite(WE,HIGH);
    delayMicroseconds(10);
    
    //Verify data
    digitalWrite(CS,LOW);
    digitalWrite(WE,HIGH);
    digitalWrite(OE,LOW);

    String readBinartRepresentation = "";

    for (int d = 0 ; d < 8 ; d++) {
      pinMode(ioPins[d], INPUT); //INPUT_PULLUP 
    }

    boolean readBit;
    
    for (int d = 0 ; d < 8 ; d++) {
      readBit = digitalRead(ioPins[d]);
      readBinartRepresentation = readBinartRepresentation + String(readBit);
    }
    
    //Serial.println("Number "+String(j)+" -> "+binaryRepresentation); 
    Serial.println("Number "+String(j)+" -> "+binaryRepresentation);
    Serial.println("Read Data "+String(j)+" -> "+readBinartRepresentation);
        
  }
}

void readTest() {

  delay(2000);
  Serial.println("********* Read Test ... ********");

  
  pinMode(CS, OUTPUT);
  pinMode(WE, OUTPUT);
  pinMode(OE, OUTPUT);
  
  digitalWrite(CS,LOW);
  digitalWrite(WE,HIGH);
  digitalWrite(OE,LOW);
  
  for (int d = 0 ; d < 8 ; d++) {
    pinMode(ioPins[d], INPUT); //INPUT_PULLUP 
  }

  //16384
  for (int j = 0 ; j < maxAddressNumber ; j++) {
    String binaryRepresentation = ""; 
    String readBinartRepresentation = "";
    int num = j;
    for (int i = 0 ; i < 14 ; i++) {
        //int num = j;
        if (num % 2) {
          binaryRepresentation = "1" + binaryRepresentation;  
          digitalWrite(addressPins[i],HIGH);
        }else{
          binaryRepresentation = "0" + binaryRepresentation;  
          digitalWrite(addressPins[i],LOW);
        }
        num = num / 2;
    }
    //delay(100);
    
    delayMicroseconds(10);
    //Write FF on IO
    
    boolean readBit;
    
    for (int d = 0 ; d < 8 ; d++) {
      readBit = digitalRead(ioPins[d]);
      readBinartRepresentation = readBinartRepresentation + String(readBit);
    }
    
    Serial.println("Number "+String(j)+" -> "+binaryRepresentation);
    Serial.println("Number "+String(j)+" -> "+readBinartRepresentation);      
  }
}

void writeTest() {
  delay(2000);
  Serial.println("******** Write Test ... *********");
  pinMode(CS, OUTPUT);
  pinMode(WE, OUTPUT);
  
  for (int d = 0 ; d < 8 ; d++) {
    pinMode(ioPins[d], OUTPUT); 
  }

  
  
  //16384
  for (int j = 0 ; j < maxAddressNumber ; j++) {
    
    digitalWrite(CS,LOW);
    digitalWrite(WE,LOW);
  
    for (int ad = 0 ; ad < 13 ; ad++ ) {
      digitalWrite(addressPins[ad],LOW);
    }

    
    String binaryRepresentation = "";  
    int num = j;
    for (int i = 0 ; i < 14 ; i++) {
        //int num = j;
        if (num % 2) {
          binaryRepresentation = "1" + binaryRepresentation;  
          digitalWrite(addressPins[i],HIGH);
        }else{
          binaryRepresentation = "0" + binaryRepresentation;  
          digitalWrite(addressPins[i],LOW);
        }
        num = num / 2;
    }
    //delay(100);
    //delayMicroseconds(100);
    delayMicroseconds(10);
    //Write FF on IO
    for (int d = 0 ; d < 8 ; d++) {
      if (d < 5)
        digitalWrite(ioPins[d],LOW);
      else
        digitalWrite(ioPins[d],LOW);
    }

    delayMicroseconds(10);
    //delay(100);
    digitalWrite(CS,HIGH);
    digitalWrite(WE,HIGH);
    
    //Serial.println("Number "+String(j)+" -> "+binaryRepresentation);    
      
  }
}


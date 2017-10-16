#include <LiquidCrystal_I2C.h>

//ADDRESS

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
int ADDRESS_15 = 45;
int ADDRESS_16 = 46;
int ADDRESS_17 = 47;
int ADDRESS_18 = 48;
int ADDRESS_19 = 49;

//SNES ADDRESS

int SNES_ADDRESS_0 = 30;
int SNES_ADDRESS_1 = 31;
int SNES_ADDRESS_2 = 32;
int SNES_ADDRESS_3 = 33;
int SNES_ADDRESS_4 = 34;
int SNES_ADDRESS_5 = 35;
int SNES_ADDRESS_6 = 36;
int SNES_ADDRESS_7 = 37;
int SNES_ADDRESS_8 = 38;
int SNES_ADDRESS_9 = 39;
int SNES_ADDRESS_10 = 40;
int SNES_ADDRESS_11 = 41;
int SNES_ADDRESS_12 = 42;
int SNES_ADDRESS_13 = 43;
int SNES_ADDRESS_14 = 44;
int SNES_ADDRESS_15 = 45;
int SNES_ADDRESS_16 = 52;  //change to ADDRESS_18 pin 48
int SNES_ADDRESS_17 = 49;  //chante to ADDRESS_19 pin 49
int SNES_ADDRESS_18 = 46;  //change to ADDRESS_OE pin 52
int SNES_ADDRESS_19 = 47;  //change to ADDRESS_17 pin 47


int addressPins[] = {ADDRESS_0, ADDRESS_1, ADDRESS_2, ADDRESS_3, ADDRESS_4, ADDRESS_5, ADDRESS_6,
                     ADDRESS_7, ADDRESS_8, ADDRESS_9, ADDRESS_10, ADDRESS_11, ADDRESS_12, ADDRESS_13,
                     ADDRESS_14, ADDRESS_15, ADDRESS_16, ADDRESS_17, ADDRESS_18, ADDRESS_19};


int SNES_addressPins[] = {SNES_ADDRESS_0, SNES_ADDRESS_1, SNES_ADDRESS_2, SNES_ADDRESS_3, SNES_ADDRESS_4, SNES_ADDRESS_5, SNES_ADDRESS_6,
                     SNES_ADDRESS_7, SNES_ADDRESS_8, SNES_ADDRESS_9, SNES_ADDRESS_10, SNES_ADDRESS_11, SNES_ADDRESS_12, SNES_ADDRESS_13,
                     SNES_ADDRESS_14, SNES_ADDRESS_15, SNES_ADDRESS_16, SNES_ADDRESS_17, SNES_ADDRESS_18, SNES_ADDRESS_19};

//DATA

int IO_0 = 22;
int IO_1 = 23;
int IO_2 = 24;
int IO_3 = 25;
int IO_4 = 26;
int IO_5 = 27;
int IO_6 = 28;
int IO_7 = 29;

int ioPins[] = {IO_0,IO_1,IO_2,IO_3,IO_4,IO_5,IO_6,IO_7};

int CE = 51; // Chip select E
int OE = 52; //Output Enable Program Supply G/VPP set to 

int SNES_CE = 51; 
int SNES_OE = 48; //change to ADDRESS_16 pin 48


//Program VCC 6.25 +- 0.25
//VPP = 12.75 +-

unsigned long maxAddressNumber = 1; //65536;

int j = 0; // Memory index address;
bool failed = false;

LiquidCrystal_I2C lcd(0x3F,16,2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //readTest();
  lcd.init();   
  delayMicroseconds(10);
  lcd.backlight();
  
  for (int i = 0 ; i < 19 ; i++) {
    pinMode(SNES_addressPins[i], OUTPUT);
  }

}

void loop() {
  
  //lcd.setCursor(0,0);
  //lcd.print("ADDR = ");
  //lcd.setCursor(7,0);
  //lcd.print(j);
  
  String hexData = readSNESInLoop();
  Serial.println(hexData);
  
  /*
  if ((j < maxAddressNumber) && (!failed)){
    String hexData = readSNESInLoop();

    
    if (hexData != "ff") {
      failed = true;
    }
    
    lcd.setCursor(0,1);
    lcd.print("DATA = ");
    lcd.setCursor(7,1);
    lcd.print(hexData);
    Serial.println(hexData);
    j++; //summ memory 

  }else{

    String hexData = readSNESInLoop();
    
    lcd.setCursor(0,1);
    lcd.print("DATA = ");
    lcd.setCursor(7,1);
    lcd.print(hexData);
    Serial.println(hexData);
    lcd.setCursor(11,1);
    lcd.print("END");
  
  }*/

  delay(1000);
}

void readOnlyOneAddress() {
  
}

String readSNESInLoop() {
  
  pinMode(SNES_CE, OUTPUT);
  pinMode(SNES_OE, OUTPUT);
   
  for (int d = 0 ; d < 8 ; d++) {
    pinMode(ioPins[d], INPUT_PULLUP); //INPUT
  }

  //digitalWrite(SNES_CE,HIGH);
  //digitalWrite(SNES_OE,HIGH);
  //delayMicroseconds(10000);
    
  String binaryRepresentation = ""; 
  String readBinartRepresentation = "";
  String readHEXRepresentation = "";

  /*
  int num = j;
  for (int i = 0 ; i < 18 ; i++) {
    if (num % 2) {
      binaryRepresentation = "1" + binaryRepresentation;  
      digitalWrite(SNES_addressPins[i],HIGH);
     }else{
      binaryRepresentation = "0" + binaryRepresentation;  
      digitalWrite(SNES_addressPins[i],LOW);
     }
     num = num / 2;
  }*/

  for (int i = 0 ; i < 19 ; i++) {
    delayMicroseconds(1000);


    if (i == 0) {
      digitalWrite(SNES_addressPins[i],HIGH);
    }else{
      digitalWrite(SNES_addressPins[i],LOW);  
    }
    
    
    delayMicroseconds(1000); 
  }

  //Serial.println("address => "+binaryRepresentation);
  
  //delayMicroseconds(1000);
  digitalWrite(SNES_CE,LOW);
  delayMicroseconds(1000);
  digitalWrite(SNES_OE,LOW);
  delayMicroseconds(10000); //was 100
    
  boolean readBit = false;
  byte readByte = 0;
    
  for (int d = 0 ; d < 8 ; d++) {
    delayMicroseconds(1000);
    readBit = digitalRead(ioPins[d]);
    readBinartRepresentation = readBinartRepresentation + String(readBit);
    bitWrite(readByte,d,readBit);
    readBit = false;
  }

  readHEXRepresentation = String(readByte,HEX); 

  /*
  if (readByte < 16) {
    readHEXRepresentation = readHEXRepresentation + "0";
  }*/
    
  //delayMicroseconds(100);
  //digitalWrite(SNES_CE,LOW);
  //digitalWrite(SNES_OE,LOW);
  //delayMicroseconds(100); //was 100
 
  return readHEXRepresentation;
}

String readTestInLoop() {

  pinMode(CE, OUTPUT);
  pinMode(OE, OUTPUT);
   
  for (int d = 0 ; d < 8 ; d++) {
    pinMode(ioPins[d], INPUT);
  }

  digitalWrite(CE,HIGH);
  digitalWrite(OE,HIGH);
  delayMicroseconds(1);
    
  String binaryRepresentation = ""; 
  String readBinartRepresentation = "";
  String readHEXRepresentation = "";
    
  int num = j;
  for (int i = 0 ; i < 18 ; i++) {
    if (num % 2) {
      binaryRepresentation = "1" + binaryRepresentation;  
      digitalWrite(addressPins[i],HIGH);
     }else{
      binaryRepresentation = "0" + binaryRepresentation;  
      digitalWrite(addressPins[i],LOW);
     }
     num = num / 2;
  }
   
  digitalWrite(CE,LOW);
  digitalWrite(OE,LOW);
  delayMicroseconds(1); //was 100
    
  boolean readBit;
  byte readByte;
    
  for (int d = 0 ; d < 8 ; d++) {
    readBit = digitalRead(ioPins[d]);
    readBinartRepresentation = readBinartRepresentation + String(readBit);
    bitWrite(readByte,d,readBit);
  }
    
  readHEXRepresentation = String(readByte,HEX);   
  return readHEXRepresentation;
  
}

void readTest() {
  Serial.println("********* Starting ... ********");
  delay(10000);
  Serial.println("********* Read Test ... ********");

  
  pinMode(CE, OUTPUT);
  pinMode(OE, OUTPUT);
  
  //digitalWrite(CE,HIGH);
  //digitalWrite(OE,HIGH);
  
  for (int d = 0 ; d < 8 ; d++) {
    pinMode(ioPins[d], INPUT); //INPUT_PULLUP 
  }

  //16384
  for (int j = 0 ; j < maxAddressNumber ; j++) {
    
    digitalWrite(CE,HIGH);
    digitalWrite(OE,HIGH);
    delayMicroseconds(100);
    
    String binaryRepresentation = ""; 
    String readBinartRepresentation = "";
    String readHEXRepresentation = "";
    
    int num = j;
    for (int i = 0 ; i < 15 ; i++) {
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
    digitalWrite(CE,LOW);
    digitalWrite(OE,LOW);
    delayMicroseconds(100); //was 100
    //Write FF on IO
    
    boolean readBit;
    byte readByte;
    
    for (int d = 0 ; d < 8 ; d++) {
      readBit = digitalRead(ioPins[d]);
      readBinartRepresentation = readBinartRepresentation + String(readBit);
      bitWrite(readByte,d,readBit);
      
    }
    readHEXRepresentation = String(readByte,HEX);
    Serial.println("Number "+String(j)+" -> "+binaryRepresentation);
    Serial.println("Number "+String(j)+" -> "+readBinartRepresentation);  
    Serial.println("Number "+String(j)+" -> "+readHEXRepresentation);    
  
    //return readHEXRepresentation;
  }
}

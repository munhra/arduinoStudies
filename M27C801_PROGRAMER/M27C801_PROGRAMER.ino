#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <SD.h>

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
int SNES_ADDRESS_16 = A14;  //change to ADDRESS_18 pin 48 changed to A14
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

int CE = A15; // Chip select E it was 51 due to SD incompatibility changed to A15
int OE = A14; //Output Enable Program Supply G/VPP set to changed to A14 due SD incompatibility

int SNES_CE = A15;  //change from 51 to 53 due SD incompatiblity and now to A15
int SNES_OE = 48; //change to ADDRESS_16 pin 48


//Program VCC 6.25 +- 0.25
//VPP = 12.75 +-

unsigned long maxAddressNumber = 1048575; //65536 //1048575 //491520 ; 
unsigned long StartTime = millis();

unsigned long j = 0; // Memory index address;
bool failed = false;
bool readSDCardOnce = true;

int timeSeconds = 0;
unsigned long ElapsedTime = 0;

int BUFFER_SIZE = 1024;

byte writeBuffer[1024];
byte readBuffer[1024];
byte readByteFromRom;
long readSDPosition = 0;
long bufferIndex = 0;

File dumpRomFile;
File myFile;

LiquidCrystal_I2C lcd(0x3F,16,2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000);
  
  //lcd.init();   
  //delayMicroseconds(10);
  //lcd.backlight();
  
  for (int i = 0 ; i < 19 ; i++) {
    pinMode(SNES_addressPins[i], OUTPUT);
  }

  /*
  for (int i = 0 ; i < 19 ; i++) {
    pinMode(addressPins[i], OUTPUT);
  }*/

  for (int d = 0 ; d < 8 ; d++) {
    pinMode(ioPins[d], INPUT); //INPUT
  }
  
  initializeSDCardDevice();
  Serial.println("Beginning read ...");
  delay(5000);
  readSDCardTest(0,1024);
  Serial.println("Control file read end ...");
}

void readSDCardTest(unsigned long startIndex, long bytesQtd) {
  myFile = SD.open("NHL.BIN");
  int readBufferIndex = 0;
  Serial.println("Control File Start Position => "+String(startIndex));
  myFile.seek(startIndex);
  myFile.read(readBuffer,bytesQtd);
  myFile.close();  
}

void initializeSDCardDevice() {
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
  }else{
    Serial.println("initialization success!");
    if (SD.exists("ROM.BIN")) {
      SD.remove("ROM.BIN");
    }
    dumpRomFile = SD.open("ROM.BIN",FILE_WRITE);
    if (SD.exists("ROM.BIN")) {
      Serial.println("File exists !!!");
    }else{
       Serial.println("File does not exists !!!");  
    }
  }
}

void readCompleteSNESRomLoop() {

   //if ((j < maxAddressNumber) && (ElapsedTime <= 30000)){
  if ((j < maxAddressNumber) && (!(failed))){
    
    readByteFromRom = readSNESInLoop();
    
    //Serial.println("Address => " + String(j)+" Data => "+hexData);
    //Serial.println("Address => "+String(j)+" Control Buffer => "+String(readBuffer[j],HEX)+" Write Buffer => "+String(writeBuffer[j],HEX));
    if ((readBuffer[bufferIndex] != readByteFromRom)) {
      //failed = true;
      //try again on the same address  
      Serial.println("Address => "+String(j)+" Control Buffer => "+String(readBuffer[bufferIndex],HEX)+" Write Buffer => "+String(readByteFromRom,HEX));
    }else{
      //DATA WAS CORRECT SAVE AND GO TO NEXT ADDRESS
      
      writeBuffer[bufferIndex] = readByteFromRom;
      
      if (bufferIndex + 1 == BUFFER_SIZE) {
        bufferIndex = 0;
        dumpRomFile.write(writeBuffer,BUFFER_SIZE);
        dumpRomFile.flush();
        readSDPosition++;
        readSDCardTest((1024 * readSDPosition),1024);
      }else{
        bufferIndex++;
      }
      
      j++;

      
    }
    calculateTime();
  }else{
    //Serial.println(j);
    if (readSDCardOnce) {
      
      if (failed) {
        Serial.println("Failed at address "+String(j));  
      }else{
        Serial.println("Success last address "+String(j)); 
      }
      
      
      dumpRomFile.close();
      //Serial.println("Reading file !");
      //readSDCardTest();
      readSDCardOnce = false;
    }
  }
  
}

void loop() {
  //readCompleteSNESRomLoop();
  //testEmptyEPROM();

  readCompleteSNESRomLoop();

/*
  byte readTest = testEmptyEPROM();
  if (255 != readTest) {
    Serial.println("Empty ROM failed !!! Wrong DATA => "+String(readTest,HEX));    
  }*/
}

float calculateTime() {
  unsigned long CurrentTime = millis();
  ElapsedTime = CurrentTime - StartTime;
  return ElapsedTime/1000;
}

void testEmptyEPROM() {

   //if ((j < maxAddressNumber) && (ElapsedTime <= 30000)){
  if ((j < maxAddressNumber) && (!(failed))){
    
    readByteFromRom = readEPROM();
    
    //Serial.println("Address => " + String(j)+" Data => "+hexData);
    //Serial.println("Address => "+String(j)+" Control Buffer => "+String(readBuffer[j],HEX)+" Write Buffer => "+String(writeBuffer[j],HEX));
    
    if (j % 1024 == 0) {
      Serial.println("Sucess read Address => "+String(j)+" Read Buffer => "+String(readByteFromRom,HEX));  
    }
    
    if ((255 != readByteFromRom)) {
      //failed = true;
      //try again on the same address  
      Serial.println("Address => "+String(j)+" Read Buffer => "+String(readByteFromRom,HEX));
    }else{
      //DATA WAS CORRECT SAVE AND GO TO NEXT ADDRESS
     
      j++;

      
    }
    calculateTime();
  }else{
    //Serial.println(j);
    if (readSDCardOnce) {
      
      if (failed) {
        Serial.println("Failed at address "+String(j));  
      }else{
        Serial.println("Success last address "+String(j)); 
      }
      
      
      
      //Serial.println("Reading file !");
      //readSDCardTest();
      readSDCardOnce = false;
    }
  }
  
}

byte readEPROM() {
  pinMode(CE, OUTPUT);
  pinMode(OE, OUTPUT);

  String binaryRepresentation = ""; 
  String readBinartRepresentation = "";
  String readHEXRepresentation = "";

  for (int d = 0 ; d < 8 ; d++) {
    pinMode(ioPins[d], INPUT_PULLUP); //INPUT
  }

  unsigned long num = j;
  for (int i = 0 ; i < 19 ; i++) {
    if (num % 2) {
      //binaryRepresentation = "1" + binaryRepresentation;  
      digitalWrite(addressPins[i],HIGH);
     }else{
      //binaryRepresentation = "0" + binaryRepresentation;  
      digitalWrite(addressPins[i],LOW);
     }
     num = num / 2;
  }
  
  //delayMicroseconds(100);
  digitalWrite(CE,LOW);
  //delayMicroseconds(100);
  digitalWrite(OE,LOW);
  //delayMicroseconds(100); //was 100
    
  boolean readBit = false;
  byte readByte = 0;
    
  for (int d = 0 ; d < 8 ; d++) {
    readBit = digitalRead(ioPins[d]);
    bitWrite(readByte,d,readBit);
    readBit = false;
  }

  return readByte;
}

byte readSNESInLoop() {
  
  pinMode(SNES_CE, OUTPUT);
  pinMode(SNES_OE, OUTPUT);

  String binaryRepresentation = ""; 
  String readBinartRepresentation = "";
  String readHEXRepresentation = "";

  for (int d = 0 ; d < 8 ; d++) {
    pinMode(ioPins[d], INPUT_PULLUP); //INPUT
  }

  unsigned long num = j;
  for (int i = 0 ; i < 19 ; i++) {
    if (num % 2) {
      //binaryRepresentation = "1" + binaryRepresentation;  
      digitalWrite(SNES_addressPins[i],HIGH);
     }else{
      //binaryRepresentation = "0" + binaryRepresentation;  
      digitalWrite(SNES_addressPins[i],LOW);
     }
     num = num / 2;
  }
  
  //delayMicroseconds(100);
  digitalWrite(SNES_CE,LOW);
  //delayMicroseconds(100);
  digitalWrite(SNES_OE,LOW);
  //delayMicroseconds(100); //was 100
    
  boolean readBit = false;
  byte readByte = 0;
    
  for (int d = 0 ; d < 8 ; d++) {
    readBit = digitalRead(ioPins[d]);
    bitWrite(readByte,d,readBit);
    readBit = false;
  }

  /*
  for (int d = 0 ; d < 8 ; d++) {
    pinMode(ioPins[d], OUTPUT); //OUTPUT
  }

  for (int d = 0 ; d < 8 ; d++) {
    digitalWrite(ioPins[d],LOW);
  }

  for (int i = 0 ; i < 19 ; i++) {
    digitalWrite(SNES_addressPins[i],LOW);  
  }*/

  //delayMicroseconds(1);
 
 /*
  writeBuffer[bufferIndex] = readByte;
  
  if (bufferIndex + 1 == BUFFER_SIZE) {
    bufferIndex = 0;
    dumpRomFile.write(writeBuffer,BUFFER_SIZE);
    readSDPosition++;
    readSDCardTest(readSDPosition,(1024 * readSDPosition) + 1);
  }else{
    bufferIndex++;
  }*/
    
  return readByte;
}

//old loop with LCD too slow

  //void loop() {
  
  //lcd.setCursor(0,0);
  //lcd.print("ADDR = ");
  //lcd.setCursor(7,0);
  //lcd.print(String(j,HEX));
  //lcd.print(j);
  
  //if ((j < maxAddressNumber) && (ElapsedTime <= 30000)){
  //if ((j < maxAddressNumber)){
  //  String hexData = readSNESInLoop();
    //String hexData = "ff";
    //lcd.setCursor(0,1);
    //lcd.print("DATA = ");
    //lcd.setCursor(7,1);
    //lcd.print(hexData);
  //  Serial.println(hexData);
  //  j++;
  
 //   String time = String(calculateTime(),2);
    //lcd.setCursor(12,1);
    //lcd.print(time); 
 // }else{
    //Serial.println(j);
    //dumpRomFile.close();
 // }

//old loop with LCD too slow

  //void loop() {
  
  //lcd.setCursor(0,0);
  //lcd.print("ADDR = ");
  //lcd.setCursor(7,0);
  //lcd.print(String(j,HEX));
  //lcd.print(j);
  
  //if ((j < maxAddressNumber) && (ElapsedTime <= 30000)){
  //if ((j < maxAddressNumber)){
  //  String hexData = readSNESInLoop();
    //String hexData = "ff";
    //lcd.setCursor(0,1);
    //lcd.print("DATA = ");
    //lcd.setCursor(7,1);
    //lcd.print(hexData);
  //  Serial.println(hexData);
  //  j++;
  
 //   String time = String(calculateTime(),2);
    //lcd.setCursor(12,1);
    //lcd.print(time); 
 // }else{
    //Serial.println(j);
    //dumpRomFile.close();
 // }

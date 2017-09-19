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

int addressPins[] = {ADDRESS_0, ADDRESS_1, ADDRESS_2, ADDRESS_3, ADDRESS_4, ADDRESS_5, ADDRESS_6,
                     ADDRESS_7, ADDRESS_8, ADDRESS_9, ADDRESS_10, ADDRESS_11, ADDRESS_12, ADDRESS_13,
                     ADDRESS_14, ADDRESS_15};

//DATA

int IO_1 = 22;
int IO_2 = 23;
int IO_3 = 24;
int IO_4 = 25;
int IO_5 = 26;
int IO_6 = 27;
int IO_7 = 28;
int IO_8 = 29;

int ioPins[] = {IO_1,IO_2,IO_3,IO_4,IO_5,IO_6,IO_7,IO_8};

int CE = 51; 
//int OE = 52; 

int maxAddressNumber = 64; //65536;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //readTest();
  //writeTest();
  simpleWrite();
}

void loop() {
  // put your main code here, to run repeatedly:
}

void simpleWrite() {

  
  Serial.println("******** Write Test ... *********");
  pinMode(CE, OUTPUT);
  
  //16384
  for (int j = 0 ; j < maxAddressNumber ; j++) {
 
    for (int ad = 0 ; ad < 15 ; ad++ ) {
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

    for (int d = 0 ; d < 8 ; d++) {
      pinMode(ioPins[d], OUTPUT); 
    }

    for (int d = 0 ; d < 8 ; d++) {
      if (d < 5)
        digitalWrite(ioPins[d],LOW);
      else
        digitalWrite(ioPins[d],HIGH);
    }
    
    delayMicroseconds(1);
    digitalWrite(CE,LOW);
    delayMicroseconds(98);
    digitalWrite(CE,HIGH);
    delayMicroseconds(1);
    
    Serial.println("Number "+String(j)+" -> "+binaryRepresentation);    
      
  }
}

void writeTest() {
  
  //delay(2000);
  Serial.println("******** Write Test ... *********");
  pinMode(CE, OUTPUT);
  //pinMode(OE, OUTPUT);
  
  //16384
  for (int j = 0 ; j < maxAddressNumber ; j++) {
 
    //digitalWrite(CE,HIGH);

    for (int ad = 0 ; ad < 15 ; ad++ ) {
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

   //Verification loop
    for (int n = 0 ; n < 100 ; n ++) {
      //digitalWrite(OE,LOW);
      //Change pins to output to send data
      for (int d = 0 ; d < 8 ; d++) {
         pinMode(ioPins[d], OUTPUT); 
      }
  
      // dummy data
      for (int d = 0 ; d < 8 ; d++) {
        if (d < 5)
          digitalWrite(ioPins[d],LOW);
        else
          digitalWrite(ioPins[d],HIGH);
      }

      byte readByte;
      digitalWrite(CE,HIGH);
      delayMicroseconds(200);
      digitalWrite(CE,LOW);  
      boolean readBit;

      // change pins to input to verify data
      for (int d = 0 ; d < 8 ; d++) {
        pinMode(ioPins[d], INPUT); 
      }
      //OE/VPP/G to VIL
      //digitalWrite(OE,HIGH);
      // read data for verification
      for (int d = 0 ; d < 8 ; d++) {
        readBit = digitalRead(ioPins[d]);
        bitWrite(readByte,d,readBit);
      }

      //if data verified break the verification loop
      if (readByte == 0xFF) {
        Serial.println("Byte verified");  
        break;
      }
    
    
    
    }

    Serial.println("Number "+String(j)+" -> "+binaryRepresentation);    
      
  }

  //digitalWrite(OE,HIGH);
  //pinMode(OE, OUTPUT);
}


/*
void readTest() {

  delay(2000);
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
    delayMicroseconds(100);
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
  }
}*/

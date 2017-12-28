
int OE_0 = 22; // was 13

int A_0 = 44; //was 4 
int A_1 = 46; //was 3
int A_2 = 48; //was 2

int DATA = 24; // was 12
int CLOCK = 26; // was 11

bool soundEnabled = false;

int ledIndex = 0;

int bits[] = {0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0};

void setup() {
  // put your setup code here, to run once:
  pinMode(OE_0, OUTPUT);
  pinMode(A_0, OUTPUT);
  pinMode(A_1, OUTPUT);
  pinMode(A_2, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  Serial.begin(9600);
  digitalWrite(OE_0,LOW);
}

void disableSound() {
  
  //channel selection
  for (int i = 0 ; i < 8 ; i++ ){
      digitalWrite(CLOCK,LOW);
      delayMicroseconds(100);
      digitalWrite(DATA,LOW);
      delayMicroseconds(100);
      digitalWrite(CLOCK,HIGH);
  }
  //atenuation disable
  for (int i = 0 ; i < 8 ; i++ ){
      digitalWrite(CLOCK,LOW);
      delayMicroseconds(100);
      digitalWrite(DATA,HIGH);
      delayMicroseconds(100);
      digitalWrite(CLOCK,HIGH);
  }

  digitalWrite(CLOCK,LOW);
}

void addressFirstCardLowLoad() {
    
    digitalWrite(OE_0,HIGH);
    digitalWrite(A_0,HIGH);
    digitalWrite(A_1,HIGH);
    digitalWrite(A_2,HIGH);

    //Y0
    //digitalWrite(OE_0,HIGH);
    //digitalWrite(A_0,LOW);
    //digitalWrite(A_1,LOW);
    //digitalWrite(A_2,LOW);

    
    //Y1
    //digitalWrite(OE_0,HIGH);
    //digitalWrite(A_0,HIGH);
    //digitalWrite(A_1,LOW);
    //digitalWrite(A_2,LOW);
}

void addressHighLoad() {
  digitalWrite(OE_0,LOW);
}

void enableSound() {

  //channel selection
  for (int i = 0 ; i < 8 ; i++ ){
      digitalWrite(CLOCK,LOW);
      delayMicroseconds(100);
      digitalWrite(DATA,LOW);
      delayMicroseconds(100);
      digitalWrite(CLOCK,HIGH);
  }
  
  //atenuation disable
  for (int i = 0 ; i < 8 ; i++ ){
      digitalWrite(CLOCK,LOW);
      delayMicroseconds(100);
      digitalWrite(DATA,LOW);
      delayMicroseconds(100);
      digitalWrite(CLOCK,HIGH);
  }
  digitalWrite(CLOCK,LOW);
}

void dataTransferTest()
{
  if (ledIndex == 15) {
     bits[ledIndex] = 1;
    }
  
    Serial.println("Write word...");
    
    addressFirstCardLowLoad();
    delayMicroseconds(100);
    writeWord();
    delayMicroseconds(100);
    addressHighLoad();
    
    Serial.println("Write word done !");

    if (ledIndex == 15) {
      for (int i = 0; i < 16 ; i ++){
        bits[i] = 0;  
      }
      ledIndex = 0;
    }else{
      bits[ledIndex] = 1;
      ledIndex+=1;    
    }
    
    delay(200);
}

void writeWord()
{
  for (int i = 15 ; i >= 0 ; i-- ){
      digitalWrite(CLOCK,LOW);
      digitalWrite(DATA,bits[i]);
      digitalWrite(CLOCK,HIGH);
  }
  digitalWrite(CLOCK,LOW);
  digitalWrite(DATA,LOW);
}

void loop() {
  //dataTransferTest();
  addressFirstCardLowLoad();
  delayMicroseconds(100);
  enableSound();
  delayMicroseconds(100);
  addressHighLoad();
  Serial.println("Enable");
  delay(10000);

  addressFirstCardLowLoad();
  delayMicroseconds(100);
  disableSound();
  delayMicroseconds(100);
  addressHighLoad();
  Serial.println("Disable");

  delay(10000);
}

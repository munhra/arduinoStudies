
int pirPin = 13;
int ledPin = 0;
int pirValue = 0;
int calibrationTime = 30;

boolean postPresenceOn = true;
boolean postPresenceOff = true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(100);
  setupPir();
}

void loop() {
  // put your main code here, to run repeatedly:
  controlSimplePirState();
}

void controlSimplePirState() {
  pirValue = digitalRead(pirPin);
  if (pirValue) 
  {  
    if (postPresenceOn) {
      postPresenceOn = false;
      postPresenceOff = true;
      Serial.println("Send post presence true");
      
    }
    digitalWrite(pirPin, LOW);
  }else{
    postPresenceOn = true;
    if (postPresenceOff) {
      Serial.println("Send post presence false");
      
      postPresenceOff = false;  
      postPresenceOn = true;
    }
  }
  digitalWrite(ledPin, pirValue);
}


void setupPir() {
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(pirPin, LOW);
  Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000);
      }
   Serial.println(" done");
   Serial.println("SENSOR ACTIVE");
   delay(50);
}


long lastMillis = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  long currentMillis = millis();

  if (currentMillis - lastMillis > 15000) {
    Serial.println("Send debug "+String(currentMillis - lastMillis));
    lastMillis = currentMillis;
  }
}

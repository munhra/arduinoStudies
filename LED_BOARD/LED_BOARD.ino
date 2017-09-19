void setup() {
  pinMode(15, OUTPUT);
  pinMode(0, OUTPUT);
  Serial.begin (115200);
}

void loop() {
  digitalWrite(15, HIGH);
  //digitalWrite(0, HIGH);
  Serial.println("HIGH");
  delay(500);
  digitalWrite(15, LOW);
  //digitalWrite(0, LOW);
  Serial.println("LOW");
  delay(500);
}

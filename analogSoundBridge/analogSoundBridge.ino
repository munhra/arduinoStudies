int A0_VAL = 0;
int A1_VAL = 0;

int PWM_OUT_0 = 2;
int PWM_OUT_1 = 3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  A0_VAL = analogRead(A0);    // read the input pin
  A1_VAL = analogRead(A1);
  //Serial.println(A0_VAL);
  A0_VAL = map(A0_VAL, 0, 1023, 0, 255);
  A1_VAL = map(A1_VAL, 0, 1023, 0, 255);
  
  analogWrite(PWM_OUT_0,A0_VAL);
  analogWrite(PWM_OUT_1,A1_VAL);
  
  //delay(100);
}

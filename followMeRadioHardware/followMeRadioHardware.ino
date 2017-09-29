
int OE_0 = 13;

int A_0 = 4;
int A_1 = 3;
int A_2 = 2;


void setup() {
  // put your setup code here, to run once:
  pinMode(OE_0, OUTPUT);
  pinMode(A_0, OUTPUT);
  pinMode(A_1, OUTPUT);
  pinMode(A_2, OUTPUT);
  Serial.begin(9600);
  digitalWrite(OE_0,LOW);
}

void loop() {
  
  // Set Last slot LOAD LOW
  delay(10000);
  digitalWrite(OE_0,HIGH);
  digitalWrite(A_0,HIGH);
  digitalWrite(A_1,HIGH);
  digitalWrite(A_2,HIGH);
  
  
  Serial.println("LOW");
  delay(10000);
  digitalWrite(OE_0,LOW);
  
  
  Serial.println("HIGH");
}



int KITCHEN_OUTPUT = 30;
int LIVING_OUTPUT = 32;
int BATHROOM_OUTPUT = 34;
int BEDROOM_OUTPUT = 36;

int KITCHEN_INPUT = 31;
int LIVING_INPUT = 33;
int BATHROOM_INPUT = 35;
int BEDROOM_INPUT = 37;

int inputPins[] = {KITCHEN_INPUT, LIVING_INPUT, BATHROOM_INPUT, BEDROOM_INPUT};
int outputPins[] = {KITCHEN_OUTPUT, LIVING_OUTPUT, BATHROOM_OUTPUT, BEDROOM_OUTPUT};

bool raspRoomValue = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  /*
  for (int i = 0 ; i < 4 ; i++) {
    pinMode(inputPins[i], INPUT);
    pinMode(outputPins[i], OUTPUT);
  }*/
}

void loop() {
  // put your main code here, to run repeatedly:

  //digitalWrite(KITCHEN_OUTPUT,true);
  
  
  for (int i = 0 ; i < 4 ; i++) {
    raspRoomValue = digitalRead(inputPins[i]);
    //Serial.print(" Rasp Value "+String(i)+ "  => "+String(raspRoomValue));
    digitalWrite(outputPins[i],raspRoomValue);
  }
  //Serial.println("");
  //Serial.println("***********************");
  
  /*
  Serial.println("Turn audio ON 1");
  digitalWrite(KITCHEN_OUTPUT,true);
  delay(7000);
  Serial.println("Turn audio FALSE 1");
  digitalWrite(KITCHEN_OUTPUT,false);
  delay(500);
  Serial.println("Turn audio ON 2");
  digitalWrite(LIVING_OUTPUT,true);
  delay(7000);
  Serial.println("Turn audio FALSE 2");
  digitalWrite(LIVING_OUTPUT,false);
  delay(500);

  */
}

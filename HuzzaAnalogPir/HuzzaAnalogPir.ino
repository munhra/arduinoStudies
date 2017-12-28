
const int QTD_VALUES = 5000;

int analogVal;
int ANALOG_PIN = 17;
int analogValues[QTD_VALUES];
int valuesCounter = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Ready !!!");  
}

void loop() {

  analogVal = analogRead(ANALOG_PIN);
  //Serial.println("Analog Val "+String(analogVal));
  //delay(1000);

  if (valuesCounter == QTD_VALUES) {
    valuesCounter = 0;
    Serial.println(sensorMetrics());
  }else{
    analogValues[valuesCounter] = analogVal;
    valuesCounter++;  
  }
  
}

void checkDetection() {
  
}

String sensorMetrics() {

  int totalValues = 0;
  for (int i = 0 ; i < QTD_VALUES ; i++ ) {
    totalValues = totalValues + analogValues[i];   
  }

  float averageValues = totalValues / QTD_VALUES;
  return "Average Values " + String(averageValues);
}


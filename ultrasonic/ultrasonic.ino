/*
********************************************
14CORE ULTRASONIC DISTANCE SENSOR CODE TEST
********************************************
*/
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define TRIGGER 12
#define ECHO    13
 
// NodeMCU Pin D1 > TRIGGER | Pin D2 > ECHO

LiquidCrystal_I2C lcd(0x3F,16,2);
 
void setup() {
  
  Serial.begin (115200);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  //pinMode(BUILTIN_LED, OUTPUT);

  lcd.init();   
  delayMicroseconds(10);
  lcd.backlight();

}
 
void loop() {
  
  long duration, distance;

  lcd.setCursor(0,0);
  lcd.print("TESTE");
  lcd.setCursor(0,1);
  lcd.print("TESTE 2");
  
  digitalWrite(TRIGGER, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = (duration/2) / 29.1;
  
  Serial.print(duration);
  Serial.println(" Duration");
  Serial.print(distance);
  Serial.println(" Centimeter:");
  delay(1000);
}

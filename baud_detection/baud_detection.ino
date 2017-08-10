#include <SoftwareSerial.h>

SoftwareSerial BTSerial(15, 14);

int led = 13;
int ledHIGH = 0;

long bauds[] = {
    // major 
    9600, 57600, 115200,
    
    // others
    19200, 38400, 4800, 2400, 1200, 230400
  };
 

bool detectBleBaudRate() {
  Serial.println("Detecting BLE baud rate:");
  for (int i=0; i<(sizeof(bauds)/sizeof(long)); i++) {
    Serial.write("Checking ");
    long cur_baud = bauds[i];
    Serial.println(cur_baud, DEC);
    
    BTSerial.begin(cur_baud);
    BTSerial.write("AT");
    BTSerial.flush();
    delay(50);
    String response = BTSerial.readString();
    if (response == "OK") {
      Serial.println("Detected");
      return true;
    } else {
      BTSerial.end();
    }
  }
  return false;
}

void setup() {
  // init
  Serial.begin(115200);  // USB (choose 115200 in terminal)
  
  if (detectBleBaudRate())
    Serial.write("Ready, type AT commands\n\n");
  else
    Serial.write("Not ready. Halt");
  
  pinMode(led, OUTPUT);
}

void loop() {
  // read from BLE (HM-10)
  if (BTSerial.available()) {
    Serial.write("ble: ");
    String str = BTSerial.readString();
    Serial.print(str);
    Serial.write('\n');
  }

  // read from USB (Arduino Terminal)
  if (Serial.available()) {
    Serial.write("usb: ");
    String str = Serial.readString();
    BTSerial.print(str);
    Serial.print(str);
    Serial.write('\n');
  }
}


#include <SoftwareSerial.h>

SoftwareSerial xbee(2, 3); // RX, TX

void setup() {

  xbee.begin(9600);
  Serial.begin(9600);

  Serial.println("Setup complete");

}

void loop() {

  //Serial.println(xbee.read());

  if(xbee.available() > 0) {
      Serial.print("Xbee: ");
      char inChar = char(xbee.read());
      Serial.println(inChar);
    }

  if(Serial.available() > 0) {
      xbee.print("Serial: ");
      char inChar = char(Serial.read());
      xbee.println(inChar);
    }

}

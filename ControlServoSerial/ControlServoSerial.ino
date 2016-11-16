#include <SoftwareSerial.h>
#include <Servo.h>

Servo  Servo1, Servo2, Servo3, Servo4;
int    N, S, W, E;

SoftwareSerial xbee(2, 3); // RX, TX

void setup() 

{

  Serial.begin(9600);
  xbee.begin(9600);

  Servo1.attach(5);
  Servo2.attach(6);
  Servo3.attach(9);
  Servo4.attach(10);
  
  Serial.println("Setup completado");

}

void loop() {
  // if there's any serial available, read it:
  while (xbee.available() > 0) 
  
  {

    // look for the next valid integer in the incoming serial stream:
    N = xbee.parseInt(); 
    // do it again:
    S = xbee.parseInt(); 
    // do it again:
    W = xbee.parseInt(); 
    // do it again:
    E = xbee.parseInt(); 

    // look for the newline. That's the end of your
    // sentence:
    if (xbee.read() == '\n') 
    
    {

      Servo1.write(N);

      Servo2.write(S);

      Servo3.write(W);

      Servo4.write(E);     

      // print 
      
      printD(); 
       
    }
  }
}

void printD()

{

      Serial.print("Rotores: ");
      Serial.print(N);
      Serial.print(" | ");
      Serial.print(S);
      Serial.print(" | ");
      Serial.print(W);
      Serial.print(" | ");
      Serial.println(E);

}







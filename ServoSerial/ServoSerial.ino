#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial xbee(2, 3); // RX, TX
Servo N, S, W, E;

int Ns = 50;
int Ss = 50;
int Ws = 50;
int Es = 50;

void setup() {

  Serial.begin(9600);
  xbee.begin(9600);

  N.attach(5);
  S.attach(6);
  W.attach(9);
  E.attach(10);

  Serial.println("Setup correctamente completado");

}

void loop() 

{  
  
  // if there's any serial available, read it:
  while (xbee.available() > 0) 
  {    
    while(Serial.read() != '%') {} //Espera a que llege '%'    
    // look for the next valid integer in the incoming serial stream:
    Ns = xbee.parseInt(); 
    // do it again:
    Ss = xbee.parseInt(); 
    // do it again:
    Ws = xbee.parseInt(); 
    // do it again:
    Es = xbee.parseInt(); 
 
  }
  
      N.write(Ns);
      S.write(Ss);
      W.write(Ws);
      E.write(Es); 
      
}

void arm()

{                            // Funcion del armado del ESC
 N.write(0);
 S.write(0);
 W.write(0);
 E.write(0);
 delay(100);
 N.write(20);
 S.write(20);
 W.write(20);
 E.write(20);
 delay(3000);
 
 Serial.println("Setup de motores hecho");
}

void printD(boolean t)

{
   if (t)
   
   {
      Serial.print("Rotores: ");
      Serial.print(Ns);
      Serial.print(" | ");
      Serial.print(Ss);
      Serial.print(" | ");
      Serial.print(Ws);
      Serial.print(" | ");
      Serial.print(Es);

   }  

}



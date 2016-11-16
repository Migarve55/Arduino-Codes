//
// Programa para controlar el dron desde el mando de xbox
//

#include <SoftwareSerial.h>
SoftwareSerial xbee(2, 3); // RX, TX

#define DB_S true
#define minS 20
#define maxS 200

int Ns = 50;
int Ss = 50;
int Ws = 50;
int Es = 50;

boolean MODO = false;
boolean RB;

int pot,X,Y;
int mod,restaX,restaY;

int botRB = 8;
int josX = A2;
int josY = A4;
int potJ = A0;
 
void setup()
{
  
 Serial.begin(9600);
 xbee.begin(9600);
 
 xbee.println("PruebaXbee");
 Serial.println("Setup completado");
 
 pinMode(botRB, INPUT);
 pinMode(potJ, INPUT);
 pinMode(josX, INPUT);
 pinMode(josY, INPUT);

}
 
 
void loop()

{
 
 pot = map(analogRead(potJ),0,1023,0,200);
 X = map(analogRead(josX),0,1023,-100,100); 
 Y = map(analogRead(josY),0,1023,-100,100);
 RB = digitalRead(botRB);
 
 printDB(DB_S);
 mandar(MODO); 
 
}

void printDB(boolean t)

{
 if (t)
 {

  Serial.print("Eje X: ");Serial.print(X);
  Serial.print(" Eje Y: ");Serial.print(Y);       
   
  Serial.print(" Potencia: ");Serial.print(pot);
  Serial.print(" RB: ");Serial.print(RB);
  Serial.println(); 
   
 }
}

void mandar(boolean t)

{

 if (t)
 {

 }

}







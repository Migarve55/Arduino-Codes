#include <SoftwareSerial.h> //Software Serial Port
#include <Servo.h>

#define RxD 3 // This is the pin that the Bluetooth (BT_TX) will transmit to the Arduino (RxD)
#define TxD 2 // This is the pin that the Bluetooth (BT_RX) will receive from the Arduino (TxD)
 
#define DEBUG false

//SoftwareSerial xbee(RxD,TxD);

// Los rotores

Servo N, S, W, E;
char* rotor[]={"N","S","W","E"};

  int Nspeed;
  int Sspeed;
  int Wspeed;
  int Espeed;
  
  long int BTin;

// El LED de Feedback

int LedFB = 13;

char mensaje;
char recieved;

 void setup()
 
{
  
 Serial.begin(9600); // Allow Serial communication via USB cable to computer (if required) 
 //xbee.begin(9600);
 pinMode(LedFB ,OUTPUT); // El LED de FeedBack
 
   //Rotores
   
   N.attach(5);
   S.attach(6);
   W.attach(10);
   E.attach(11);
   
 }
 
 void loop()
 
 {    
   
      BTin = Serial.parseInt();
     
       if (BTin > 0 && BTin <= 180) // Rotor N (0 - 180)     
     {
        Nspeed = BTin; 
        N.write(Nspeed);  
        Serial.print("Rotor N puesto a: "), Serial.println(Nspeed); 
     }  
     
       if (BTin >= 200 && BTin <= 380) // Rotor S (200 - 380)     
     {
        Sspeed = BTin - 200;
        N.write(Sspeed);  
        Serial.print("Rotor S puesto a: "), Serial.println(Sspeed); 
     }  
     
       if (BTin >= 400 && BTin <= 580) // Rotor W (400 - 580)     
     {
        Wspeed = BTin - 400;
        N.write(Wspeed);  
        Serial.print("Rotor W puesto a: "), Serial.println(Wspeed); 
     }  
     
       if (BTin >= 600 && BTin <= 780) // Rotor E (600 - 780)     
     {
        Espeed = BTin - 600;
        N.write(Espeed);  
        Serial.print("Rotor E puesto a: "), Serial.println(Espeed); 
     } 
     //Si señal  
   //Configura la velocidad de los rotores
   
   N.write(Nspeed);
   S.write(Sspeed);
   W.write(Wspeed);
   E.write(Espeed);
 
   int red = Serial.parseInt();
 }



void serialEvent()
{}
 
void parp()

{
 digitalWrite(LedFB, HIGH);
 delay(1000);
 digitalWrite(LedFB, LOW);
}


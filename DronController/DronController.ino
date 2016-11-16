/* 



*/
 
#include <SoftwareSerial.h> //Software Serial Port
#include <Servo.h>

#define RxD 6 // This is the pin that the Bluetooth (BT_TX) will transmit to the Arduino (RxD)
#define TxD 7 // This is the pin that the Bluetooth (BT_RX) will receive from the Arduino (TxD)
 
#define DEBUG_ENABLED 1

// Aqui van los Pines (ints)

// Los rotores

Servo N, S, W, E;
char* rotor[]={"N","S","W","E"};

  int Nspeed;
  int Sspeed;
  int Wspeed;
  int Espeed;

// El LED de Feedback

int LedFB = 13;

//La velocidad

int vspeed = 0;

// Y el bluetooth

//SoftwareSerial blueToothSerial(RxD,TxD);

//Las entradas y salidas

char BTin;
char BTout;
char SERIALin;
char SERIALout;

/*----------------------SETUP----------------------------*/ 
void setup() 
{ 
  
 Serial.begin(9600); // Allow Serial communication via USB cable to computer (if required)
 pinMode(RxD, INPUT); // Setup the Arduino to receive INPUT from the bluetooth shield on Digital Pin 6
 pinMode(TxD, OUTPUT); // Setup the Arduino to send data (OUTPUT) to the bluetooth shield on Digital Pin 7
 
 pinMode(LedFB ,OUTPUT); // El LED de FeedBack
 
//Los rotores controlados por ESC
 
 N.attach(5); // El rotor norte
 S.attach(6); // El rotor sur
 W.attach(10); // El rotor oeste
 E.attach(11); // El rotor este
 
 delay(100);
 
 //setupBlueToothConnection(); //Used to initialise the Bluetooth shield
 
 
} 

/*-------------------------------------LOOP--------------------------------------------*/ 
void loop()

{ 
if(Serial.available()) { // Detecta si hay señal Bluetooth
      
  //Esto crea una linea en el monitor serial de lo que dice el teléfono.  
    
  //BTin = blueToothSerial.read();
  BTin = Serial.read();
  //SERIALin = Serial.read();  
 
  //Código de los rotores

  if (BTin == 'L') { // Subir
   setRotorsSpeedMore();
  }
  if (BTin == 'B') { // Bajar
   setRotorsSpeedLess(); 
  }
  if (BTin == 'F') { // FeedBack
   LedFeedBack(); 
  }
  if (BTin == 'N') { // N
   turnN(); 
  }
  if (BTin == 'S') { // S
   turnS(); 
  }
  if (BTin == 'W') { // W
   turnW(); 
  }
  if (BTin == 'E') { // E
   turnE(); 
  }
  
  } // IF Señal

} // Loop

void serialEvent() 

{

}

//----------------------------------------- FUNCIONES --------------------------------------------------------------------//
 
// Aqui va las funciones de los motores

void land() //Aterrizaje
{

  Nspeed = 80;
  Sspeed = 80;
  Wspeed = 80;
  Espeed = 80;    
  
  N.write(Nspeed);
  S.write(Sspeed);
  W.write(Wspeed);
  E.write(Espeed);
  
 // delay(10000); // Espera 10 segundos
 Serial.println("Aterrijaze");

}

void setRotorsSpeedMore()

{

 if (vspeed < 180)
 {
  vspeed = vspeed + 10; //Aqui resta uno menos a vspeed
 }

  
 Nspeed = vspeed;
 Sspeed = vspeed;
 Wspeed = vspeed;
 Espeed = vspeed;
  
 N.write(Nspeed); 
 S.write(Sspeed); 
 W.write(Wspeed); 
 E.write(Espeed);    
 
 Serial.println(vspeed);
  
} 

void setRotorsSpeedLess()

{
 if (vspeed > 0)
 {
  vspeed = vspeed - 10; //Aqui resta uno menos a vspeed
 }


 Nspeed = vspeed;
 Sspeed = vspeed;
 Wspeed = vspeed;
 Espeed = vspeed;
  
 N.write(Nspeed); 
 S.write(Sspeed); 
 W.write(Wspeed); 
 E.write(Espeed);  

 Serial.println(vspeed); 
  
} 

void estabilizar()
{
 Nspeed = vspeed;
 Sspeed = vspeed;
 Wspeed = vspeed;
 Espeed = vspeed; 
  
 N.write(Nspeed); 
 S.write(Sspeed); 
 W.write(Wspeed); 
 E.write(Espeed); 
}

void turnN()

{
 estabilizar();
  
  if (Nspeed =! 0) {Nspeed = vspeed - 10;}
  N.write(Nspeed);
  
 Serial.println("La velocidad del rotor N es:" + Nspeed);
  
}
void turnS()

{
  estabilizar();
  
  if (Sspeed =! 0) {Sspeed = vspeed - 10;}
  S.write(Sspeed);
  
 Serial.println("La velocidad del rotor S es:" + Sspeed);
  
}
void turnW()

{  
  estabilizar();
  
  if (Wspeed =! 0) {Wspeed = vspeed - 10;}
  W.write(Wspeed);
  
 Serial.println("La velocidad del rotor W es:" + Wspeed);
  
}
void turnE()

{
  estabilizar();
  
  if (Espeed =! 0) {Espeed = vspeed - 10;}
  E.write(Espeed);
  
 Serial.println("La velocidad del rotor E es:" + Espeed);  
  
}

void LedFeedBack()

{
  digitalWrite(LedFB, HIGH); 
  delay(100);
  digitalWrite(LedFB, LOW); 
}


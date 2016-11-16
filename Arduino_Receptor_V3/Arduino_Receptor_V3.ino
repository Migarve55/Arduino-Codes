#include <Ultrasonic.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>

MPU6050 accelgyro;
int16_t ax, ay, az;
int16_t gx, gy, gz;
int X,Y,Z;
int pot,mod,restaX,restaY;

SoftwareSerial xbee(2, 3); // RX, TX
Ultrasonic ultrasonic(9,8); // (Trig PIN,Echo PIN)

#define PARACAIDAS false
#define EST_SMP true
#define DB_S true
#define maxTiempoSinSenal 10000
#define AlturaM 30

#define minS 20
#define maxS 200

#define minG -16500
#define maxG 16500
#define minDegree -90
#define maxDegree 90

#define respuesta 0 //En milisegundos
#define factorMod 1.8
#define factorRes 200

/*

    Modo de funcionamiento 

    1 - Normal
    2 - DEBUG: De Xbee a monitor Serial 
    3 - Setup de rotores y test
    4 - Test de Xbee
    5 - Controlado desde monitor Serial
    6 - Automatico

*/

//Creo los rotores

Servo N, W, S ,E;

int Ns = 50;
int Ss = 50;
int Ws = 50;
int Es = 50;

int SELECT = 7;
int INTRO = 4;

char incom;
int MODO = 5;
long int count;
int altura, alturaMx, AlturaSoporte;

void setup() //---------------------------------SETUP-------------------------------//

{ 

setupCom();
setupEst();
setupMotores();

Serial.println("Setup completado");
pinMode(13, OUTPUT);digitalWrite(13, HIGH);delay(150);digitalWrite(13, LOW);

}

void loop() //------------------------------------LOOP--------------------------------//

{
  
switch (MODO) //Modo 
{

case 1:  
getDataXbee();
break; 

case 2: 
debugXbeeToSerial();
break; 

case 3:   
debugMotores(); 
break; 

case 4: 
debugXbee();
break;

case 5:
getDataSerial(); 
break;

case 6: 

break; //Fin modo 6

} //Modo

//parachute(PARACAIDAS);
  printD(DB_S);  

} //Loop

//------------------------------------------------------------------------OTRAS FUNCIONES----------------------------------------------------------------------------------------//

int selec()

{
  
delay(1000);  
  
int modo = 1;
boolean selecionando = true;

while (selecionando)
{

 if (digitalRead(SELECT)) {modo++; if (modo == 7){modo = 1;}};
 if (digitalRead(INTRO)) {}//selecionando = false;}

 for (int i = 0; i = modo; i++)
 {
  pinMode(13, HIGH);
  delay(100);  
  pinMode(13, LOW);
 }
}

return modo;

}

void confirm()

{
  
while(xbee.read() != 'E') {}
xbee.write('L');
Serial.println("Todo listo");

} 



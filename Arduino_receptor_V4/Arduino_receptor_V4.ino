/*

 Programa desarrollado para controlar un quadcopter X por Miguel Garnacho Vélez.
 Su uso y modificación es totalmente libre, y dejo notas en el sketch para comprenderlo y mejorarlo.

 Para controlarlo necesitas las librerias incluidas en la carpeta "LIBRERIAS" y un programa de procesing, el cual usa un joystick de PC,
 y otras librerias, mas detalles en el programa de Procesing.
 Tambien se puede usar un mando de xbox modificado, y otra arduino. Los esquemas estan en "DOCUMENTOS". Por lo gneral vale cualquier mando d de Xbox,
 pero hay que tener en cuante que se necesitan habilidades de soldadura blanda y cables, aun así no es complicado, solo hace falta seguir los esquemas.
 
 El hardware del quadcopter puede se cualquiera, mientras que sean 4 motores brushless y un cuarto ESC. El IMU utilizado es el MPU6050, si tienes uno diferente
 tendrás que cmbiar de libreria y modificar el programa. Tiene que tener 3 ejes de giroscopio y 3 de acelerómetro.
 
 Sino comprendeis como funciona el filtro Kalman, me temo que no puedo explicaróslo dado que yo tampoco lo se. Es muy avanzado para mi.

*/
#include <Ultrasonic.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>

MPU6050 accelgyro;
int16_t ax, ay, az;
int16_t gx, gy, gz;
int yaw,pitch,roll;
//int pot,mod,restaX,restaY;
int YawRec,PitchRec,RollRec;
int Vel = 60;
int YawCor,PitchCor,RollCor;      //Valores para corregir la trayectoria.
int xVar,yVar;  
unsigned long timer;
float timeStep = 0.02;

float biasGyroX, biasGyroY, biasGyroZ, biasAccelX, biasAccelY, biasAccelZ;
float pitchGyro = 0;
float pitchAccel = 0;
float pitchPrediction = 0; //Output of Kalman filter
float rollGyro = 0;
float rollAccel = 0;
float rollPrediction = 0;  //Output of Kalman filter
float giroVar = 0.1;
float deltaGiroVar = 0.1;
float accelVar = 5;
float Pxx = 1; // angle variance
float Pvv = 1; // angle change rate variance
float Pxv = 1; // angle and angle change rate covariance
float kx, kv;

SoftwareSerial xbee(2, 3); // RX, TX
Ultrasonic ultrasonic(9,8); // (Trig PIN,Echo PIN)

#define PARACAIDAS false
#define EST_SMP true
#define DB_S true
#define maxTiempoSinSenal 10000
#define AlturaM 30

// NUNCA DEFINIR LAS DOS A LA VEZ, PUEDE HABER ERRORES
//#define XBEE
#define SERIAL 

//#define BAUDIOS 9600 
#define BAUDIOS 115200 

#define minS 20
#define maxS 200

#define minG -16500
#define maxG 16500
#define minDegree -90
#define maxDegree 90

#define minRec -15
#define maxRec 15

//Creo los rotores
Servo N, W, S ,E;

int Ns = 50;
int Ss = 50;
int Ws = 50;
int Es = 50;

int SELECT = 7;
int INTRO = 4;

int MODO = 5;
long int count;
int altura, alturaMx, AlturaSoporte;

void setup() //---------------------------------SETUP-------------------------------//

{ 

setupCom();
setupEst();
setupMotores();
setupKalman();

Serial.println("Setup completado");
pinMode(13, OUTPUT);digitalWrite(13, HIGH);delay(150);digitalWrite(13, LOW);

}

void loop() //------------------------------------LOOP--------------------------------//

{
  
timer = millis();  
  
calcularYPR(); //Consigue el yaw, pitch, roll y los acelerómetros    
//filtrarKalman(); //Lo filtra gracias al yaw pitch roll y acelerómetros
calcularVelocidad(); 
setVelocidad(); 

parachute(PARACAIDAS); 
printD(DB_S); 

timer = millis() - timer;
timer = (timeStep * 1000) - timer; 
//delay(timer);

} 

void serialEvent()

{

#ifdef XBEE
getDataXbee();
#endif

#ifdef SERIAL
getDataSerial();
#endif

}

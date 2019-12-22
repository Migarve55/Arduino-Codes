// Librerias I2C para controlar el mpu6050
// la libreria MPU6050.h necesita I2Cdev.h, I2Cdev.h necesita Wire.h
#include "I2Cdev.h"
#include "Wire.h"
#include "MPU6050.h"

#include <SoftwareSerial.h>

#define NAME "Giroscopio"
#define PIN 4321

MPU6050 sensor;
SoftwareSerial BT(8,9); // RX, TX 

// Valores RAW (sin procesar) del acelerometro y giroscopio en los ejes x,y,z
int ax, ay, az;
int gx, gy, gz;

long tiempo_prev;
float dt;
float ang_x, ang_y;
float ang_x_prev, ang_y_prev;

void sendDataBT(float x, float y) {
  BT.print(x);
  BT.print(':');
  BT.print(y);
  BT.println(';');
}

void SetupBluetooth() {
  BT.print("AT");
  delay(1000);
  BT.print("AT+NAME");
  BT.print(NAME);
  delay(1000);
  BT.print("AT+PIN");
  BT.print(PIN);
  delay(1000);
  BT.print("AT+BAUD8");
  delay(1000);
}

void setup() {
  Serial.begin(57600); 
  BT.begin(9600);
  Wire.begin();           
  sensor.initialize();    
}

void loop() {
  // Leer las aceleraciones y velocidades angulares
  sensor.getAcceleration(&ax, &ay, &az);
  sensor.getRotation(&gx, &gy, &gz);
  
  dt = (millis()-tiempo_prev)/1000.0;
  tiempo_prev=millis();
  
  //Calcular los angulos con acelerometro
  float accel_ang_x=atan(ay/sqrt(pow(ax,2) + pow(az,2)))*(180.0/3.14);
  float accel_ang_y=atan(-ax/sqrt(pow(ay,2) + pow(az,2)))*(180.0/3.14);
  
  //Calcular angulo de rotación con giroscopio y filtro complemento  
  ang_x = 0.98*(ang_x_prev+(gx/131)*dt) + 0.02*accel_ang_x;
  ang_y = 0.98*(ang_y_prev+(gy/131)*dt) + 0.02*accel_ang_y;
  
  
  ang_x_prev=ang_x;
  ang_y_prev=ang_y;

  sendDataBT(ang_x, ang_y);

  delay(50);
}


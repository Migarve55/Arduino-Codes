#include <MPU6050.h>
#include <Wire.h>
#include <I2Cdev.h>

MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;

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
float Pxx = 0.1; // angle variance
float Pvv = 0.1; // angle change rate variance
float Pxv = 0.1; // angle and angle change rate covariance
float kx, kv;
unsigned long timer;

int firstSensor = 0;    // first analog sensor
int secondSensor = 0;   // second analog sensor
int thirdSensor = 0;    // digital sensor
int inByte = 0;         // incoming serial byte

void setup()

{
  
Serial.begin(9600);  
  
Serial.println("Initializing I2C devices...");
accelgyro.initialize();
Serial.println("Testing device connections..."); //Comprueba la conexion
Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
establishContact();  // send a byte to establish contact until receiver responds

}

void loop()

{
  
  timer = millis(); // Inicio del timer
  
  accelgyro.getMotion6(&gx, &gy, &gz, &ax, &ay, &az); //Consigue los datos del giroscopio
  
  pitchAccel = atan2((ay - biasAccelY) / 256, (az - biasAccelZ) / 256) * 360.0 / (2*PI); //Inicio Kalman
  pitchGyro = pitchGyro + ((gx - biasGyroX) / 14.375) * timeStep;
  pitchPrediction = pitchPrediction + ((gx - biasGyroX) / 14.375) * timeStep;
  
  rollAccel = atan2((ax - biasAccelX) / 256, (az - biasAccelZ) / 256) * 360.0 / (2*PI);
  rollGyro = rollGyro - ((gy - biasGyroY) / 14.375) * timeStep; 
  rollPrediction = rollPrediction - ((gy - biasGyroY) / 14.375) * timeStep;
  
  Pxx += timeStep * (2 * Pxv + timeStep * Pvv);
  Pxv += timeStep * Pvv;
  Pxx += timeStep * giroVar;
  Pvv += timeStep * deltaGiroVar;
  kx = Pxx * (1 / (Pxx + accelVar));
  kv = Pxv * (1 / (Pxx + accelVar));
  
  pitchPrediction += (pitchAccel - pitchPrediction) * kx;
  rollPrediction += (rollAccel - rollPrediction) * kx;
  
  Pxx *= (1 - kx);
  Pxv *= (1 - kx);
  Pvv -= kv * Pxv;
  
  //Fin del algoritmo de Kalman

  if (Serial.available() > 0)    
  {    
    // get incoming byte:
    inByte = Serial.read();
    firstSensor = map(pitchPrediction, -16500, 16500, 0, 180);
    secondSensor = map(rollPrediction, -16500, 16500, 0, 180);
    thirdSensor = map(analogRead(A0), 0, 1023, 0, 180);
    // send sensor values:
    Serial.write(firstSensor);
    Serial.write(secondSensor);
    Serial.write(thirdSensor);
  }
  
  timer = millis() - timer;           //Fin del timer
  timer = (timeStep * 1000) - timer; 
  delay(timer);
  
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.print('A');   // send a capital A
    delay(300);
  }
}

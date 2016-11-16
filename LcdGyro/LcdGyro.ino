#include <LiquidCrystal.h>
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

MPU6050 accelgyro;
int16_t gx, gy, gz;
int X,Y;

void setup() 
{

accelgyro.initialize();
lcd.begin(16, 2);
lcd.print("Test LCD OK");
delay(1500);
lcd.clear();
pinMode(13,OUTPUT);
  
}

void loop() 
{

accelgyro.getRotation(&gx, &gy, &gz);

X = map(gx,-17000,17000,-90,90);
Y = map(gy,-17000,17000,-90,90);

lcd.setCursor(0,0);
lcd.print("Giroscopio:");
lcd.setCursor(0,1);
lcd.print("X: ");
lcd.print(X);
lcd.print(" Y:" );
lcd.print(Y);

digitalWrite(13,HIGH);
delay(100);
digitalWrite(13,LOW);

}

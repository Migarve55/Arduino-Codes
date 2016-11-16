
#include <Servo.h>

void setup()
{

//gyro
int X, Y;  
//servo
Servo N, S, W, E;
int Nspeed, Sspeed, Wspeed, Espeed;

N.attach(6);
S.attach(7);
W.attach(11);
E.attach(12);

pinMode(A2, INPUT);
pinMode(A4, INPUT);

}
void loop()
{

  X = analogRead(A2);
  Y = analogRead(A4);
  
  if (X > 0)
  {}
  else
  {}
  if (Y > 0)
  {}
  else
  {}

}

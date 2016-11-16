
void setupKalman() 
{
  int totalGyroXValues = 0;
  int totalGyroYValues = 0;
  int totalGyroZValues = 0;
  int totalAccelXValues = 0;
  int totalAccelYValues = 0;
  int totalAccelZValues = 0;
  int i;
  
  delay(100); //wait for gyro
  for (i = 0; i < 50; i += 1) 
  {
    calcularYPR();
    totalGyroXValues += gx;
    totalGyroYValues += gy;
    totalGyroZValues += gz;
    totalAccelXValues += ax;
    totalAccelYValues += ay;
    totalAccelZValues += az;
    delay(50);
  }
  biasGyroX = totalGyroXValues / 50;
  biasGyroY = totalGyroYValues / 50;
  biasGyroZ = totalGyroZValues / 50;
  biasAccelX = totalAccelXValues / 50;
  biasAccelY = totalAccelYValues / 50;
  biasAccelZ = (totalAccelZValues / 50) - 256;
  
}

void filtrarKalman()

{
  
  pitchAccel = atan2((ay - biasAccelY) / 256, (az - biasAccelZ) / 256) * 360.0 / (2*PI);
  pitchGyro = pitchGyro + ((gx - biasGyroX) / 14.375) * timeStep;
  pitchPrediction = pitchPrediction + ((gx - biasGyroX) / 14.375) * timeStep;
  
  rollAccel = atan2((ax - biasAccelX) / 256, (ay - biasAccelZ) / 256) * 360.0 / (2*PI);
  rollGyro = rollGyro - ((gy - biasGyroY) / 14.375) * timeStep; 
  rollPrediction = rollPrediction - ((gy - biasGyroY) / 14.375) * timeStep;
  
  Pxx += timeStep * (2 * Pxv + timeStep * Pvv);
  Pxv += timeStep * Pvv;
  Pxx += timeStep * giroVar;
  Pvv += timeStep * deltaGiroVar;
  kx = Pxx * (1 / (Pxx + accelVar));
  kv = Pxv * (1 / (Pxx + accelVar));
  
  pitchPrediction += (pitchAccel - pitchPrediction) * kx;  //OUTPUT
  rollPrediction += (rollAccel - rollPrediction) * kx;     //OUTPUT
  
  Pxx *= (1 - kx);
  Pxv *= (1 - kx);
  Pvv -= kv * Pxv;

}

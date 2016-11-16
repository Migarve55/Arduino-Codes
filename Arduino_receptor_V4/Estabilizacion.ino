
void setupEst()

{

AlturaSoporte = ultrasonic.Ranging(CM);
alturaMx = AlturaM;  
  
Wire.begin();
Serial.println("Initializing I2C devices...");
accelgyro.initialize();
Serial.println("Testing device connections..."); //Comprueba la conexion
Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

}

void calcularVelocidad()

{

YawCor = map(-yaw,-90,90,-Vel,Vel);
PitchCor = map(-pitch,-90,90,-Vel,Vel);

xVar = PitchCor + constrain(PitchRec,minRec,maxRec);
yVar = YawCor + constrain(YawRec,minRec,maxRec);

Ns = Vel - yVar;
Ss = Vel + yVar;
Es = Vel - xVar;
Ws = Vel + xVar;

}

void calcularYPR()

{

accelgyro.getMotion6(&gx, &gy, &gz, &ax, &ay, &az); //Consigue los datos del giroscopio

yaw = -map(gy, minG, maxG, minDegree, maxDegree);
pitch = -map(gx, minG, maxG, minDegree, maxDegree);
roll = map(gz, minG, maxG, minDegree, maxDegree);

}

void nivelar(int aM)

{

ultrasonic.Ranging(CM) - AlturaSoporte;
int velocidad;

if (altura < aM) //Los rotores bajan
{velocidad = 100;}
if (altura == aM) //Los rotores mantienn la altura
{velocidad = 80;}
if (altura > aM) //Los rotores suben
{velocidad = 75;}

setVelocidadTodos(velocidad);

}

/*
   delay(respuesta); //Respuesta
   Serial.println("Est"); //DEBUG
   //Calculos de variables necesarias
   
   pot = Ns; //Como todos los valores son iguales, da igual (a la hora de estabilizar)
   mod = int(map(sqrt(sq(X) + sq(Y)),0,128,0,pot)); //calcula el modulo 
   restaX = int(map(X, minDegree, maxDegree, 0, pot));
   restaY = int(map(Y, minDegree, maxDegree, 0, pot));
   
   X = -X;Y = -Y;// Invierte el vector para contrarestar
   
   //Modificacion de velocidad

   if (X > 0 && Y > 0) // 1
   {
   Es = pot - mod;
   Ns = pot - restaY;
   Ss = pot - restaX;
   Ws = pot;
   } 
   if (X < 0 && Y > 0)  // 2
   {
   Ns = pot - mod;
   Es = pot - restaY;
   Ws = pot - restaX;
   Ss = pot;
   }      
   
   if (X < 0 && Y < 0) // 3
   {
   Ws = pot - mod;
   Ns = pot - restaY;
   Ss = pot - restaX;
   Es = pot;
   } 
   if (X > 0 && Y < 0)  // 4
   {
   Ss = pot - mod;
   Es = pot - restaY;
   Ws = pot - restaX;
   Ns = pot;
   }
     
   if (X == 0) //Se mueve por el eje Y 
   {
    if (Y > 0) 
    {Ns = pot - restaY;Es = pot - restaY;Ws = pot;Ss = pot;} 
    else 
    {Ws = pot - restaY;Ss = pot - restaY;Ns = pot;Es = pot;}
   }
   if (Y == 0) //Se mueve por el eje X
   {
    if (X > 0) 
    {Es = pot - restaX;Ss = pot - restaX;Ns = pot;Ws = pot;} 
    else 
    {Ws = pot - restaX;Ns = pot - restaX;Ss = pot;Es = pot;}
   }   

   if (X == 0 && Y == 0) //Origen
   {Ns = pot;Ss = pot;Ws = pot;Es = pot;}
*/

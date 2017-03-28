#include <SoftwareSerial.h>
#include <AFMotor.h> 

AF_DCMotor Lmotor(1); //Setup left motor
AF_DCMotor Rmotor(2); //Setup right motor

int motorLchange = 8;
int motorRchange = 0;

int Speed = 100;

int Sr, Sl;

SoftwareSerial BT(6, 7); // RX, TX

void setup() 

{

  Serial.begin(9600);
  setupBlueToothConnection();
  
  Serial.println("Setup completado");
  
  Lmotor.setSpeed(Speed + motorLchange);            //Sets the left motor speed to 200 / 255
  Rmotor.setSpeed(Speed + motorRchange);            //Sets the right motor speed to 200 / 255
  
  Lmotor.run(RELEASE);
  Rmotor.run(RELEASE);
  
  while(BT.read() != '?') {}
  BT.print('R');
  Serial.println("Conectado");
  
}

void loop() 

{
  
  while (BT.available() > 0) 
  
  {
   
   switch(BT.read())
   
   {
   case 'W': Lmotor.run(FORWARD); Rmotor.run(FORWARD); break;
   case 'A': Lmotor.run(RELEASE); Rmotor.run(FORWARD); break;
   case 'S': Lmotor.run(FORWARD); Rmotor.run(RELEASE); break;
   case 'D': Lmotor.run(BACKWARD); Rmotor.run(BACKWARD); break;
   case '+': if (Speed < 250) {Speed += 10;} break;
   case '-': if (Speed > 0) {Speed -= 10;} break;
   case 'X': Lmotor.run(RELEASE); Rmotor.run(RELEASE); break;
   
   default: BT.print("null \n"); break;
   }
   
  Lmotor.setSpeed(Speed + motorLchange);            //Sets the left motor speed to 200 / 255
  Rmotor.setSpeed(Speed + motorRchange);            //Sets the right motor speed to 200 / 255
       
  }
 
}

void setupBlueToothConnection()
{
 BT.begin(38400); //Set BluetoothBee BaudRate to default baud rate 38400
 BT.print("\r\n+STWMOD=0\r\n"); //set the bluetooth work in slave mode
 BT.print("\r\n+STNA=RCarduino\r\n"); //set the bluetooth name as "RCarduino"
 BT.print("\r\n+STOAUT=1\r\n"); // Permit Paired device to connect me
 BT.print("\r\n+STAUTO=0\r\n"); // Auto-connection should be forbidden here
 delay(2000); // This delay is required.
 BT.print("\r\n+INQ=1\r\n"); //make the slave bluetooth inquirable 
 Serial.println("The slave bluetooth is inquirable!");
 delay(2000); // This delay is required.
 BT.flush();
}



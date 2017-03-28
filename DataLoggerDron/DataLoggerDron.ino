
#include <SoftwareSerial.h>

SoftwareSerial xbee(2, 3); // RX, TX

String data[3];
int dataLength = 3;

boolean isConnected = false;
char start = '%'; 
char separator = ',';
char endChar = ';';
char request = 'M';

void setup() 

{

  Serial.begin(9600);
  xbee.begin(9600);

  Serial.println("Connecting to logger");
  connectTologger();
  Serial.println("Connected to logger successfully");

}

float n = 0.0;
float r = 0.0;

void loop()

{

  n += 1.5;
  if (n > 1000.0) n = 0.0;

  r = random(0,1000);

  data[0] = String(n);
  data[1] = String(r);
  data[2] = String(69.69);

  if (xbee.available() > 0)  
      {if (xbee.read() == request)sendData(data);}

  delay(10);
  
}


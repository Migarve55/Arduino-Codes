/*

  LiquidCrystal Library - BT Input

*/

#define RxD 5
#define TxD 6

// include the library code:
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

SoftwareSerial bt(RxD,TxD);

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);


void setup() 

{
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Inicia la comunicacion BT:
  setupBlueToothConnection();
  
}

void loop()

{
  
  if (bt.available()) 
  {    
    delay(100);
    lcd.clear();

    while (bt.available() > 0) 
    {lcd.write(bt.read());}
  }
  
}

void setupBlueToothConnection()
{
 bt.begin(38400); //Set BluetoothBee BaudRate to default baud rate 38400
 bt.print("\r\n+STWMOD=0\r\n"); //set the bluetooth work in slave mode
 bt.print("\r\n+STNA=LCDarduino\r\n"); //set the bluetooth name as "SeeedBTSlave"
 bt.print("\r\n+STOAUT=1\r\n"); // Permit Paired device to connect me
 bt.print("\r\n+STAUTO=0\r\n"); // Auto-connection should be forbidden here
 delay(2000); // This delay is required.
 bt.print("\r\n+INQ=1\r\n"); //make the slave bluetooth inquirable 
 Serial.println("The slave bluetooth is inquirable!");
 delay(2000); // This delay is required.
 bt.flush();
}

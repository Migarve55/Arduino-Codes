#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int minutos = 5;
int segundos = 0;

int pinFusor = 2;
int pinBoton = 4;

boolean arm = false;

void setup() 
{

pinMode(pinFusor,OUTPUT);
pinMode(pinBoton,INPUT);  
  
lcd.begin(16, 2);
lcd.print("Test LCD OK");
delay(1500);
lcd.clear();

lcd.print("Pulsa para");lcd.setCursor(0,1);lcd.print("activar");
while(!digitalRead(pinBoton)) {} //Espera a que la armes
lcd.clear();
  
}

void loop() 
{

lcd.clear();
if (digitalRead(pinBoton)) 
{if (arm) {arm = false;} else {arm = true;}}
  
lcd.setCursor(0,0);
if (arm)
{lcd.print("Bomba armada");}
else
{lcd.print("Bomba desarmada");}

lcd.setCursor(0,1);
lcd.print(minutos);
lcd.print(":");
lcd.print(segundos);

segundos--; //Baja un segundo
if (segundos < 0) {minutos--;segundos = 59;}

delay(1000); //Espera un segundo

if(minutos == 0 && segundos == 0)

{

 if (arm)

 {  
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("BUM!!!!!");
 digitalWrite(pinFusor,HIGH);
 while(true){}//Para hasta que reinicies el arduino
 } 
 else 
 {
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Bomba abortada");
 while(true){}//Para hasta que reinicies el arduino
 }
 
}

}

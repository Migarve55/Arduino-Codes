#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int tmpSensor = A0; //Pin del sensor de temperatura
int tmp; //Variable de la temperatura

void setup()

{

  lcd.begin(16,2);
  lcd.print("Test LCD OK");
  delay(1500);
  lcd.clear();
  pinMode(tmpSensor,INPUT);

}

void loop()

{
  
tmp = getTmp();

//lcd.clear(); //Reinicia el LCD
lcd.setCursor(0,0);
lcd.print("Temperatura:");
lcd.setCursor(0,1);
lcd.print(tmp);
lcd.setCursor(4,1);
lcd.print("C");
delay(1000);

}

int getTmp()

{

 int reading = analogRead(tmpSensor);  
 float voltage = reading * 0.004882814;
 //voltage /= 1024.0; 
 int t = (voltage - 0.5) * 100 ;
 
 return t;

}

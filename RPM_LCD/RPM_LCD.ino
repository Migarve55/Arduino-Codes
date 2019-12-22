#include <LiquidCrystal.h>

const byte interruptPin = 2;
volatile byte rev = 0;

int d = 1000;
unsigned long t, lt;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {

  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), rpm, CHANGE);
  
  lcd.begin(16, 2);
  lcd.noCursor();
  
  lcd.write("Tacometro listo");
  delay(1000);
  lcd.clear();
}

void loop() 
{
  t = millis();
  if ((t - lt) >= d) {
  lcd.clear();
  lcd.print("RPM: " + String(rev * 60));
  lt = t; 
  rev = 0;}
}

void rpm() 
{
  rev++;
}

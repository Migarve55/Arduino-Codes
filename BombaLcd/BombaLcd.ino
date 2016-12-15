#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//Initial time
int minutes = 5;
int seconds = 0;

const boolean MINUTES_VALUE = false;
const boolean SECONDS_VALUE = true;

const int MAX_MINUTES = 30;

//Pins
int loadPin = 2; //Pin to attach the fuse

//Buttons variables
int adc_key_val[5] = {50, 200, 400, 600, 800 };
int NUM_KEYS       = 5;  
//Button keys
const int SELECT         = 5;
const int UP             = 2;
const int DOWN           = 3;
const int LEFT           = 4;
const int RIGHT          = 1;

const int BOUNCE = 60;

//Armed variable
boolean armed = false;

void setup() 
{

  pinMode(loadPin,OUTPUT);
    
  lcd.begin(16, 2);
  lcd.print("Test LCD OK");
  delay(1500);
  lcd.clear();
  
  lcd.print("Press select");lcd.setCursor(0,1);lcd.print("to arm");
  while(!getKey(analogRead(0)) == SELECT) {} //Wait to arm the bomb
  lcd.clear();

  //Select time
  selectTime(&minutes,&seconds);
}

void loop() 
{

  lcd.clear();
  
  if (getKey(analogRead(0)) == SELECT) {
    armed = !armed;}
    
  lcd.setCursor(0,0);
  if (armed)
  {lcd.print("Bomb armed");}
  else
  {lcd.print("Bomb disarmed");}
  
  lcd.setCursor(0,1);
  lcd.print(minutes);
  lcd.print(":");
  if (seconds < 10) {
    lcd.print("0");}
  lcd.print(seconds);
  
  seconds--; //Baja un segundo
  if (seconds < 0) {minutes--;seconds = 59;}
  
  delay(1000); //Espera un segundo

  //Counter reaches 0:00
  if(minutes == 0 && seconds <= 0){
     if (armed) {  
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("BUM!!!!!");
       digitalWrite(loadPin,HIGH);
       while(true){}}//Para hasta que reinicies el arduino
     else {
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Bomb aborted");
       while(true){}//Para hasta que reinicies el arduino
     }
  }
}

 /**
 * Gets the key 
 */
  int getKey(unsigned int input)
  {
    int k;
    for (k = 0; k < NUM_KEYS; k++)
    {
      if (input < adc_key_val[k])
      {
        return k+1;
      }
    }   
    if (k >= NUM_KEYS)k = -1;  // No valid key pressed
    return k;
  }

void selectTime(int *minut, int *sec)

{

//Used by the getKey method
int key            =-1;
int oldkey         =-1;

boolean selecting = true;
int selectedTime[2] = {5,0}; 

boolean selection = false; //false for minutes, true for seconds

while(selecting)

{

  lcd.setCursor(0,0);
  if (selection == MINUTES_VALUE) {
    lcd.print("Select minutes:");}
  else {
    lcd.print("Select seconds:");}
  lcd.setCursor(0,1);
  lcd.print(selectedTime[0]);
  lcd.print(":");
  if (selectedTime[1] < 10) {
    lcd.print("0");}
  lcd.print(selectedTime[1]);

   key = getKey(analogRead(0));
   if (key != oldkey)   // if keypress is detected
   {
     delay(BOUNCE);  // wait for debounce time
     key = getKey(analogRead(0));
     if (key != oldkey)    
     {          
       //oldkey = key;
       if (key >=0) //Procesing keys
       {
          switch(key) 
          {
          
          case SELECT: //End
            selecting = false;
          break;
          
          case UP:  
          if (selection == MINUTES_VALUE) {
            if (selectedTime[0] < MAX_MINUTES) {
              selectedTime[0]++;}}
          else {
            selectedTime[1]++;
            if (selectedTime[1] > 59) {
                selectedTime[1] = 0;
              }           
            }
          break;
          
          case DOWN:  
          if (selection == MINUTES_VALUE) {
            if (selectedTime[0] > 0) {
              selectedTime[0]--;}}
          else {
            selectedTime[1]--;
            if (selectedTime[1] < 0) {
                selectedTime[1] = 59;
              }
            }
          break;
          
          case LEFT:  
          selection = MINUTES_VALUE;
          break;
          
          case RIGHT: 
          selection = SECONDS_VALUE; 
          break;
            
          }              
       }
     }
   }
   delay(100);

  lcd.clear(); //Borra el display para dibujarlo otra vez.

  }
  *minut = selectedTime[0];
  *sec = selectedTime[1];
}


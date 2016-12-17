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

const int BOUNCE = 150;

//Armed variable
boolean armed = false;

//IMPORTANT: Disarm code
const int code[] = {1,2,3,4};

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
    if(inputCode()) {
      armed = !armed;}}
    
  lcd.setCursor(0,0);
  if (armed)
  {lcd.print("Bomb armed");}
  else
  {lcd.print("Bomb disarmed");}
  
  lcd.setCursor(0,1);
  lcd.print("Time: ");
  lcd.print(minutes);
  lcd.print(":");
  if (seconds < 10) {
    lcd.print("0");}
  lcd.print(seconds);
  
  updateTime();

  //Counter reaches 0:00
  checkTimer();
  delay(1000); //Wait 1 seconds
}

void updateTime() {
    //Blink led (pin 13), on board
    digitalWrite(13,HIGH);
    digitalWrite(13,LOW);
    seconds--; //Updates time
    if (seconds < 0) {minutes--;seconds = 59;}
  }

void checkTimer()
{
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

boolean selecting = true;
int selectedTime[2] = {5,0}; 

int key;

boolean selection = false; //false for minutes, true for seconds

while(selecting)

{
  lcd.clear(); 
  lcd.setCursor(0,0);
  if (selection == MINUTES_VALUE) {
    lcd.print("Select minutes:");}
  else {
    lcd.print("Select seconds:");}
  lcd.setCursor(0,1);
  lcd.print("Time: ");
  lcd.print(selectedTime[0]);
  lcd.print(":");
  if (selectedTime[1] < 10) {
    lcd.print("0");}
  lcd.print(selectedTime[1]);
  
  delay(BOUNCE);  // wait for debounce time    
  key = getKey(analogRead(0));
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
  delay(100);
  lcd.clear(); 

  *minut = selectedTime[0];
  *sec = selectedTime[1];
}

boolean inputCode() {

    //Used by the getKey method
    int key            =-1;
    int oldkey         =-1;
    //Code inputed by the user
    int inputCode[] = {0,0,0,0};
    int currentDigit = -1;

    boolean inputing = true;

    int t; //Used to measure time
    
    lcd.clear();
    
    boolean result = true;
    while (inputing) {
       int t0 = millis();
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Insert code:");
       //Display current input code
       for(int i = 0;i < 4;i++) {
         lcd.print(inputCode[i]);
       }    
       //Print cursor
       lcd.setCursor(currentDigit+12,1);
       lcd.print('^');
       key = getKey(analogRead(0));
       if (key != oldkey)// if keypress is detected
       {
         delay(50);  // wait for debounce time
         key = getKey(analogRead(0));
         if (key != oldkey)    
         {          
           oldkey = key;
           if (key >=0) //Procesing keys
           {
              switch(key) 
              {
              
              case SELECT: //Confirm number
              if (currentDigit == 3) {
                inputing = false;}
              break;
              
              case UP:
              inputCode[currentDigit]++;  
              if (inputCode[currentDigit] > 9) {
                inputCode[currentDigit] = 0;}
              break;
              
              case DOWN: 
              inputCode[currentDigit]--;   
              if (inputCode[currentDigit] < 0) {
                inputCode[currentDigit] = 9;}
              break;

              case LEFT:  
              currentDigit--;
              if (currentDigit < 0) {
                currentDigit = 3;}
              break;
              
              case RIGHT: 
              currentDigit++;
              if (currentDigit > 3) {
                currentDigit = 0;}
              break;     
              
             }              
           }
         }
       }
       //Restart
       delay(50);
       t += millis() - t0;
       if(t > 1000) {
        updateTime();
        t = 0;
        }
       checkTimer();
      }
    lcd.setCursor(0,1);  
    for (int i = 0;i < 4;i++) { //Verify code
      if (code[i] != inputCode[i]) {
        result = false;}}
    if (result) {
      lcd.print("Code correct    ");}
    else {
      lcd.print("Code incorrect  ");}
    delay(1000);
    lcd.clear();
    return result;
  }


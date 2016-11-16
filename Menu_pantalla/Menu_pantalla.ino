/*

Programa arduino para un lcd con menu.

*/

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int adc_key_val[5] = {50, 200, 400, 600, 800 };
int NUM_KEYS       = 5;  
int Modo           = 1;
int key            = -1;
int oldkey         = -1;

char charModo[5][13] = {"Modo normal ",
                        "DB:Xbee - MS",               
                        "Test rotores",
                        "Test de Xbee",
                        "Desde Mon.Sr"};

void setup()

{
  
  lcd.begin(16, 2);
  lcd.print("Pantalla LCD ok");
  delay(2000);
  lcd.clear();
  
  selectModo(); //Selecciona el modo

}

void loop()

{

  switch(Modo) //Despues de configurar el modo, que haga lo que quiera
  
  {
  
  case 1:  
  break;
  
  case 2:  
  break;
  
  case 3:  
  break;
  
  case 4:  
  break;
  
  case 5:  
  break;
    
  }
    
}


int get_key(unsigned int input)
{
    int k;
    for (k = 0; k < NUM_KEYS; k++)
    {
      if (input < adc_key_val[k])
      {
        return k;
      }
    }   
    if (k >= NUM_KEYS)k = -1;  // No valid key pressed
    return k;
}

void selectModo()

{

boolean terminado = false;

while(terminado != true)

{

  lcd.setCursor(0, 0);
  lcd.print("Modo: ");
  lcd.setCursor(0, 1);
  lcd.print("< "), lcd.print(charModo[Modo]), lcd.print(" >");

   key = get_key(analogRead(0));
   if (key != oldkey)   // if keypress is detected
   {
     delay(50);  // wait for debounce time
     key = get_key(analogRead(0));
     if (key != oldkey)    
     {          
       oldkey = key;
       if (key >=0) //Dentro de aquí se procesan las teclas
       {
           
         if (key == 1) {if (Modo != 5) {Modo++;}} // >>>
         if (key == 4) {if (Modo != 1) {Modo--;}} // <<<
         
         if (key == 5) {terminado = true;} //Si pulsas select termina el bucle
              
       }
     }
   }
   delay(100);

  lcd.clear(); //Borra el display para dibujarlo otra vez.

}

  lcd.setCursor(0, 0);
  lcd.print("Has seleccionado");
  lcd.setCursor(0, 1);
  lcd.print(charModo[Modo]);
  delay(2000);
  lcd.clear();

}




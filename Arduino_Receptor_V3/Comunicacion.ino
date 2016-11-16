
void setupCom()

{

Serial.begin(9600);
xbee.begin(9600);
xbee.println("PruebaXbee");


}

void getDataXbee()

{

 while (xbee.available() > 0)   
  {
   if (xbee.read() == '%')
   {
    Ns = xbee.parseInt(); 
    Ss = xbee.parseInt(); 
    Ws = xbee.parseInt(); 
    Es = xbee.parseInt(); 

    if (xbee.read() == '\n')     
    {}       
   }    
  } 
 }
  
void getDataSerial()

{
 while (Serial.available() > 0)  
  {
   if (Serial.read() == '%')
   {
    Ns = Serial.parseInt(); 
    Ss = Serial.parseInt(); 
    Ws = Serial.parseInt(); 
    Es = Serial.parseInt();           
    
   }    
  }
}  



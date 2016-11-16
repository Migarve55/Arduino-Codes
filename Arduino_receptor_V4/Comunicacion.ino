

void setupCom()

{

Serial.begin(BAUDIOS);
xbee.begin(BAUDIOS);
xbee.println("PruebaXbee");


}

void getDataXbee()

{

 while (xbee.available() > 0)   
  {
   if (xbee.read() == '%')
   {
    YawRec = xbee.parseInt(); 
    PitchRec = xbee.parseInt(); 
    RollRec = xbee.parseInt(); 
    Vel = xbee.parseInt(); 

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
    YawRec = Serial.parseInt(); 
    PitchRec = Serial.parseInt(); 
    RollRec = Serial.parseInt(); 
    Vel = Serial.parseInt();               
   }    
  }
}  



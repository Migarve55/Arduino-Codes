void printD(boolean t)

{
   if (t)   
   {
      Serial.print("Rotores: ");
      Serial.print(Ns);Serial.print(" | ");Serial.print(Ss);Serial.print(" | ");Serial.print(Ws);Serial.print(" | ");Serial.print(Es);
      
      Serial.print(" Giroscopio:");
      Serial.print(" X: ");Serial.print(X);Serial.print(" Y: ");Serial.print(Y);Serial.print(" Z: ");Serial.println(Z);

   }  
}

void debugXbeeToSerial()

{
if (xbee.available() > 0)
{Serial.println(xbee.read());}
}

void debugXbee()
{
xbee.println("Probando transmision inalambrica por Xbee");
delay(1500);
}

void debugMotores()

{

 N.write(50);
 S.write(50);
 W.write(50);
 E.write(50);

delay(5000); 

 N.write(100);
 S.write(100);
 W.write(100);
 E.write(100);

delay(5000); 

 N.write(200);
 S.write(200);
 W.write(200);
 E.write(200);
 
delay(5000); 

 N.write(20);
 S.write(20);
 W.write(20);
 E.write(20);
 
 delay(1000);
 
while (true) {} //Aqui finaliza el test hasta que se para. 
}

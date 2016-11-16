
void setupMotores()

{
  
  N.attach(5); 
  S.attach(6); 
  W.attach(9); 
  E.attach(10);

  arm();  
  
}

void setVelocidadTodos(int vel)

{

      N.write(vel);
      S.write(vel);
      W.write(vel);
      E.write(vel); 

}

void setVelocidad()

{
      
      N.write(Ns);
      S.write(Ss); 
      W.write(Ws);
      E.write(Es);  
             
}

void arm()

{                            // Funcion del armado del ESC
 N.write(0);
 S.write(0);
 W.write(0);
 E.write(0);
 delay(100);
 N.write(20);
 S.write(20);
 W.write(20);
 E.write(20);
 delay(2000);
 
 Serial.println("Setup de motores hecho");
}

void parachute(boolean p)

{
 if (p) //Si el protocolo esta activado
 {
   
   if (xbee.available()) {count = 0;} else {count++;}//Cada vez que no hay señal suma 1 al count
   
   if (count = maxTiempoSinSenal) 
 
    { 
      
      N.write(constrain(60,minS,maxS));
      S.write(constrain(60,minS,maxS));
      W.write(constrain(60,minS,maxS));
      E.write(constrain(60,minS,maxS)); 
      
      Serial.println("Protocolo de aterrizaje");
    } //Se activa el protocolo 
 }
}


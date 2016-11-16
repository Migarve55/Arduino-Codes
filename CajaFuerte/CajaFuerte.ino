
#include <Servo.h>

Servo cerrojo;

int verde = 8;
int rojo = 7;

int boton = 4;
int seguro = 12;

boolean cerrado = false;

int clave[] = {6, 3, 8, 0};

void setup()

{
  
  pinMode(verde, OUTPUT); //led verde
  pinMode(rojo, OUTPUT); //led rojo
  pinMode(boton, INPUT); //boton
  
  pinMode(A3, INPUT); // pot
  
  pinMode(seguro, INPUT); //Seguro

  //Setup del servo
  cerrojo.attach(5);  
  
  //Test del servo
  cerrojo.write(0);
  cerrojo.write(90);
  cerrojo.write(0);
  
  testCerrar(); //Espara a que se cierre la puerta
  
}

void loop()

{

  testBotonAbrir(); //Comprueba si quieres abrir la puerta    
  testCerrado(); //Comprueba si esta cerrado esta cerrado
  
}

void testCerrar()

{
  
  while(digitalRead(seguro) != HIGH)
  {
  digitalWrite(verde, HIGH), digitalWrite(rojo, HIGH); //Ponen los dos leds encendidos, para indicar que se tiene que cerrar la puerta.
  }
  
  cerrojo.write(90); //Cierra la puerta
  
  digitalWrite(verde, LOW), digitalWrite(rojo, LOW); //Pone las luces en modo "Cerrado"
  cerrado = true;
  
}

void testCerrado()

{  
 if (digitalRead(seguro) == LOW && cerrado == true) 
 {
  //alarma
 }
}

void testBotonAbrir()

{

if (digitalRead(boton) == HIGH)
 {

   
   
   
 }
}

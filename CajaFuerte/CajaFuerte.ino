
#include <Servo.h>

Servo lock;

int greenLEDpin = 8;
int redLEDpin = 7;

int button = 4;
int closedSensor = 12;

int speakerPin = 9;

boolean closed = false;
int closedPosition = 90;
int openedPosition = 0;

int code[] = {6, 3, 8, 0};

//Other variables
int errorCounter = 0;
int maxErrors = 3;

int alarmDuration = 10000; //In milliseconds

void setup()

{
  
  pinMode(greenLEDpin, OUTPUT); //Green LED
  pinMode(redLEDpin, OUTPUT);  //Red LED
  pinMode(button, INPUT); //Button
  
  pinMode(A3, INPUT); // pot
  
  pinMode(closedSensor, INPUT); //Safe

  //Serevo setup 
  lock.attach(5);  
  
  //Servo test
  lock.write(closedPosition);
  lock.write(openedPosition);
  lock.write(closedPosition);

  //Wait to lock the door until you close it
  testClose();
  
}

void loop()

{

  init:

 //Alarm checking
  if (closed && digitalRead(closedSensor) == LOW) {
    alarm();
    goto init;
  }

  //User wants to open the safebox
  if (closed && digitalRead(button) == HIGH) {
  boolean Running = true;
    while (Running) {
      if(checkCode()) {
        digitalWrite(greenLEDpin, HIGH),delay(500), digitalWrite(greenLEDpin, LOW);
        Running = false;} //Code was correct
      else {
        digitalWrite(redLEDpin, HIGH),delay(500), digitalWrite(redLEDpin, LOW);
        errorCounter++;} //Code was incorrect
      if (errorCounter >= maxErrors) { //Too many errors
          alarm();
          goto init;
        }
     }
     //If the code was correct, open it
     lock.write(openedPosition); //Open
     delay(3000);
     testClose(); //Close
  }
}

void testClose()
{
  digitalWrite(greenLEDpin, HIGH), digitalWrite(redLEDpin, HIGH);
  
  while(digitalRead(closedSensor) != HIGH);
  lock.write(closedPosition);
  
  digitalWrite(greenLEDpin, LOW), digitalWrite(redLEDpin, LOW); 
  closed = true;
}

boolean checkCode() {
    boolean result = true;
    for (int i = 0;i < 4;i++) {
        while(digitalRead(button) != HIGH);
        if (code[i] != map(analogRead(A3),0,1023,0,9)) result = false;
      }
    return result;
  }

void alarm() {
  int duration = 0;
  while(alarmDuration > duration) {
      digitalWrite(greenLEDpin, HIGH), digitalWrite(redLEDpin, LOW);
      tone(speakerPin, 400, 100);
      digitalWrite(greenLEDpin, LOW), digitalWrite(redLEDpin, HIGH);
      tone(speakerPin, 800, 100);
      duration += 200;
    }
  noTone(speakerPin); //Stop speaker
  }

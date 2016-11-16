
String strCompare1 = "A0.0";
String strCompare2 = "A-1.0";
String strCompare3 = "A1.0";
String strCompare4 = "V0.0";
char inByte;
String strInput = "";
 
void setup(){
 Serial.begin(9600);
}
 
 
void loop(){
 
 
 
 while (Serial.available() > 0)
 {
  // get incoming byte:
  inByte = Serial.read();
  if (inByte == '\r'){
   //compare input message
   if(strInput.equals(strCompare1)){
    //If A 0 do stuff
   }
   if(strInput.equals(strCompare2)){
    //If A -1 do stuff
   }
   if(strInput.equals(strCompare3)){
    //If A 1 do stuff
   }
   if(strInput.equals(strCompare4)){
    //If V 0 do stuff
   }
 
 
   //reset strInput
   strInput = "";
  }
  else
  {
  strInput += inByte;
  }
 } 
 
 
}


String testString = "%181.50,260.00,69.69,;";

Serial connect(Serial myPort ,int baud)

{
  
  boolean connected = false;
  
  int p = 0, t = 0;     
  
  int wait = 3000; //Waits to response per port
  
  int serialNum = Serial.list().length;
  if (serialNum > 0)println("Number of avaliable ports: " + serialNum);else println("There are no avaliable ports");
  
  for (int i = 0; i < serialNum; i++)
  {
    
  try {myPort = new Serial(this, Serial.list()[i], baud);} 
  catch(Exception e) {println("Error while opening port: " + e); break;}
  delay(500); // Wait
  
  println("Waiting port: " + Serial.list()[i]);
  
  t = millis();
  while((millis() - t) < wait) 
  {
  if (myPort.read() == 'P') 
  {myPort.write('E'); connected = true; p = i; break;} //Echo
  }
  if (connected)break;
  println("There was no response : " + Serial.list()[i]);
  myPort.stop(); //Close port
  }
  
  if (connected) {
    println("Conected to port number: " + Serial.list()[p]);}
  else {
    println("No port detected");
    return null;
  }
  
  return myPort;
  
}  
 
String[] getData(Serial myPort) {

  String data[]  = new String[dataLength];
  
  String rawData = myPort.readStringUntil(endChar);
  //rawData = testString; //This is used only for testing
  if (rawData != null) {
    println("Raw data: " + rawData);
    if (rawData.charAt(0) == start) {
      //Remove the initial char
      rawData = rawData.substring(1,rawData.length()-1);
      for (int i = 0;i < dataLength;i++) {
        int index = rawData.indexOf(separator);
        if (index != -1) {
          data[i] = rawData.substring(0,index);
        //Cut the recovered data
        rawData = rawData.substring(rawData.indexOf(separator)+1,rawData.length());}
      }
    }
  }
  return data;

}

boolean isNull(String d[]) {
  for (int i = 0;i < dataLength;i++) {
    if(d[i] == null) return true;
  }
  return false;
}
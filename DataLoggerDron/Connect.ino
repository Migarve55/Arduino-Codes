void connectTologger()

{

  while (!isConnected)
  { 
  xbee.write('P');
  if (xbee.read() == 'E') {isConnected = true;} //Cuando recibe E de "Eco" finaliza
  delay(250);
  }

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

}

void sendData(String data[])

{

  xbee.write(start);
  for (int i = 0; i < dataLength; i++) {
      xbee.print(data[i]);
      xbee.write(separator);
    }
  xbee.write(endChar);
  
}

//import controlP5.*;
import processing.serial.*;
Serial port;

int dataLength = 3;
String data[] = new String[dataLength];

char start = '%'; 
char separator = ',';
char endChar = ';';
char request = 'M';

int trigger = 100; //Trigger

//Total data
ArrayList<Float[]> totalData = new ArrayList<Float[]>();

void setup()

{ 
  
  size(970,600); //970,600
  print("Connecting...");
  port = connect(port, 9600);
  if (port == null) {
    println("Failed to stablish communication with the port. Closing program.");
    delay(2000);
    exit();
  }
  else {
    println("Connected successfully");}
  
}

long frame = 0;
int t = trigger,t0 = 0;
boolean NewData = false;

void draw() 

{
  
  background(0);
  
  t0 = millis();
  
  if(t < 0) {
    port.write(request); //Request data 
    t = trigger;
  }
  if (port.available() > 0) { //Read data
    data = getData(port);
    NewData = true;
  }

  //Proccess data
  if (!isNull(data) && NewData) {
    printData(data);
    Float newData[] = new Float[dataLength];
    for (int i = 0;i < dataLength;i++) {
      newData[i] = float(data[i]);}
    totalData.add(newData);
    NewData = false;
  }
  
  //Graph
  
  drawGraphs(50,50,870,500,totalData);

  text(String.format("Frame: %s - Data: %s - Next request: %s",str(frame),str(totalData.size()),str(t)),50,580);
  frame++;
  
  t -= millis() - t0;

}

void printData(String d[]) {
  for (int i = 0;i < dataLength;i++) {
    print("Data " + str(i) + ":" + d[i] + " ");}
  println();
}
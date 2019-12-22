
const byte interruptPin = 3;
volatile byte rev = 0;

int d = 1000;
unsigned long t, lt;

void setup() {

  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), rpm, CHANGE);
  Serial.begin(9600);
}

void loop() 
{
  t = millis();
  if ((t - lt) >= d) {
  Serial.println(String(rev * 60));
  lt = t; 
  rev = 0;}
}

void rpm() 
{
  rev++;
}

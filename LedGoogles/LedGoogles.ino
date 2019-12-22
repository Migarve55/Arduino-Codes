#include <LedControl.h>

//#define DEBUG //Comment this to disable serial debugging
//#define JOYSTICK //Comment to disable joystick

#define DIN 8
#define CLK 10
#define CS  9
#define RX A5
#define RY A4

#define LEFT_EYE 0
#define RIGHT_EYE 1

#define LED_INTENSITY 10

#define CROSS 0 
#define PUPIL 1 
#define BIG_DOT 2 
#define BIG_PUPIL 3 
#define UWU 4 
#define LINE_R 5 
#define LINE_L 6 
#define EYE_OPEN 7 
#define EYE_CLOSED 8 
#define MAX_PUPIL 9 
#define QUESTION 10 
#define SURPRISE 11 

#define SHOW_RANDOM_POS 10
#define PATTERNS_LEN 12

static int PATTERNS[][8] = {
    {0x81,0x42,0x24,0x18,0x18,0x24,0x42,0x81}, //CROSS
    {0x00,0x18,0x24,0x42,0x42,0x24,0x18,0x00}, //PUPIL
    {0x00,0x00,0x18,0x3C,0x3C,0x18,0x00,0x00}, //BIG_DOT
    {0x00,0x3C,0x42,0x42,0x42,0x42,0x3C,0x00}, //BIG_PUPIL
    {0x00,0x18,0x3C,0x7E,0xE7,0xC3,0x00,0x00}, //UWU
    {0xC0,0xE0,0x70,0x38,0x1C,0x0E,0x07,0x03}, //LINE_R
    {0x03,0x07,0x0E,0x1C,0x38,0x70,0xE0,0xC0}, //LINE_L
    {0x00,0x3C,0x42,0x00,0x00,0x00,0x00,0x00}, //EYE_OPEN 
    {0x00,0x00,0x00,0x81,0x81,0x42,0x3C,0x00}, //EYE_CLOSED
    {0x7E,0x81,0x81,0x81,0x81,0x81,0x81,0x7E}, //MAX_PUPIL
    {0x18,0x24,0x24,0x08,0x08,0x08,0x00,0x08}, //QUESTION
    {0x18,0x18,0x18,0x18,0x18,0x00,0x18,0x18}  //SURPRISE
}; 

int currentMask = MAX_PUPIL;
bool randomOn = false;

LedControl lc = LedControl(DIN, CLK, CS, 2);

//Auxiliar functions

void getPattern(int pattern[], int index) {
  for (int i = 0;i < 8;i++)
    pattern[i] = PATTERNS[index][i];  
}

void loadPattern(int pattern[]) {
  loadPatternIntoEye(pattern, LEFT_EYE);
  loadPatternIntoEye(pattern, RIGHT_EYE);
}

void loadPatternIntoEye(int pattern[], int eye) {
  #ifdef DEBUG
    printPattern(pattern);
  #endif
  for (int i = 0;i < 8;i++)
    lc.setRow(eye,i,pattern[i]);
}

void createDotPattern(int pattern[], int x, int y) {
  //Offset
  x += 3;
  y += 4;
  //Create array
  for (int i = 0;i < 8;i++) {
    if (y == i || y == i + 1)
      pattern[i] = 0x3 << x;
    else
      pattern[i] = 0;
  }
}

void maskPattern(int pattern1[], int pattern2[]) {
  for (int i = 0;i < 8;i++)
    pattern1[i] |= pattern2[i];
}

//Joystick functions

void getPos(int &x, int &y) {
  x = map(analogRead(RX),0,1023,-3,3);
  y = map(analogRead(RY),0,1023,-3,3);
}

//Animation functions

void blinkEyes(int x, int y, int t) {
  loadPattern(PATTERNS[EYE_CLOSED]);
  delay(t);
  moveEyes(x, y);
}

void blinkEyes(int x, int y, int mask, int t) {
  loadPattern(PATTERNS[EYE_CLOSED]);
  delay(t);
  moveEyes(x, y, mask);
}

void blinkEye(int eye, int x, int y, int t) {
  loadPatternIntoEye(PATTERNS[EYE_CLOSED], eye);
  delay(t);
  moveEyes(x, y);
}

void blinkEye(int eye, int x, int y, int mask, int t) {
  loadPatternIntoEye(PATTERNS[EYE_CLOSED], eye);
  delay(t);
  moveEyes(x, y, mask);
}

void loadColumn(int pos, int val) {
  int mask;
  for (int i = 0;i < val;i++)
    mask |= 1 << i;
  if (pos < 8)
    lc.setColumn(0, pos, mask);
  else 
    lc.setColumn(1, pos - 8, mask);
}

void musicWave() {
  for (int i = 0;i < 50;i++) {
    for (int pos = 0;pos < 16;pos++) {
      loadColumn(pos, 1 + random(8));
    }
    delay(50);
  }
}

/**
 * Default eyes (normal eyes that use two masks)
 */
void moveEyes(int x, int y) {
  int pattern[8], p1[8], p2[8];
  createDotPattern(pattern, x, y);

  getPattern(p1, EYE_OPEN);
  maskPattern(pattern, p1);
  getPattern(p2, EYE_CLOSED);
  maskPattern(pattern, p2);

  loadPattern(pattern);
}

/**
 * Creates eyes with an spefific mask for the circle
 */
void moveEyes(int x, int y, int m) {
  int pattern[8], mask[8];
  createDotPattern(pattern, x, y);

  getPattern(mask, m);
  maskPattern(pattern, mask);

  loadPattern(pattern);
}

void setPattern(int index) {
  loadPattern(PATTERNS[index]);
}

void angry() {
  loadPatternIntoEye(PATTERNS[LINE_R], LEFT_EYE);
  loadPatternIntoEye(PATTERNS[LINE_L], RIGHT_EYE);
}

void sad() {
  loadPatternIntoEye(PATTERNS[LINE_L], LEFT_EYE);
  loadPatternIntoEye(PATTERNS[LINE_R], RIGHT_EYE);
}

//Serial debug functions

void printPattern(int pattern[]) {
  Serial.println();
  for (int i = 0;i < 8;i++) {
    for (int b = 7;b >= 0;b--) {
      Serial.print(1 << b & pattern[i] ? "0 " : ". ");
    }
    Serial.println();
  }
}

void toggleRandomDemo() {
  randomOn = !randomOn;
  Serial.print("Random is now: ");
  Serial.println(randomOn ? "ON" : "OFF");
}

//Demo function

void showPatterns() {
  for (int i = 0;i < PATTERNS_LEN;i++) {
    setPattern(i);
    delay(1000);
  }
}

void showRandomAnimation() {
  int animation = random(7);
  switch (animation) {
      case 0: 
        musicWave();
        break;
      case 1:
        setPattern(CROSS);
        delay(1500);
        break;
      case 2:
        angry();
        delay(1500);
        break;
      case 3:
        sad();
        delay(1500);
        break;
      case 4:
        setPattern(UWU);
        delay(1500);
        break;
      case 5:
        setPattern(SURPRISE);
        delay(1000);
        break;
      case 6:
        setPattern(QUESTION);
        delay(2000);
        break;
    }
}

void setup() {
  randomSeed(analogRead(0));
  #ifdef JOYSTICK
    pinMode(RX, INPUT);
    pinMode(RY, INPUT);
  #endif
  //Setup Led display
  lc.shutdown(0,false);   
  lc.shutdown(1,false);  
  lc.setIntensity(0, LED_INTENSITY);    
  lc.setIntensity(1, LED_INTENSITY);  
  lc.clearDisplay(0);      
  lc.clearDisplay(1);    
  //Setup serial communciation
  Serial.begin(9600);
  Serial.println("Pixel Glasses demo");
}

void loop() {
  //Normal operation, it just moves de eyes around using the joystick 
  int x, y;
  #ifdef JOYSTICK
    getPos(x, y);
  #endif
  //Maybe in will set a random pattern
  int r = random(100);
  if (r < SHOW_RANDOM_POS && randomOn) 
    showRandomAnimation();
  else
    moveEyes(x, y, currentMask); //X and y are swapped
  delay(200);
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char) Serial.read();
    int x = 0, y = 0;
    #ifdef JOYSTICK
      getPos(x, y);
    #endif
    switch (inChar) {
      case 'T': 
        toggleRandomDemo();
        break;
      case 'M': 
        Serial.println("Music wave");
        musicWave();
        break;
      case 'B': //Blink both eyes
        Serial.println("Blinking both eyes");
        blinkEyes(x, y, currentMask, 250);
        break;
      case 'L':
        Serial.println("Blinking left eye");
        blinkEye(LEFT_EYE, x, y, currentMask, 250);
        break;
      case 'R':
        Serial.println("Blinking right  eye");
        blinkEye(RIGHT_EYE, x, y, currentMask, 250);
        break;
      case 'D':
        Serial.println("Dead");
        setPattern(CROSS);
        delay(1500);
        break;
      case 'A':
        Serial.println("Angry");
        angry();
        delay(1500);
        break;
      case 'S':
        Serial.println("Sad");
        sad();
        delay(1500);
        break;
      case 'U':
        Serial.println("UWU");
        setPattern(UWU);
        delay(1500);
        break;
      case '!':
        Serial.println("Surprise");
        setPattern(SURPRISE);
        delay(1000);
        break;
      case '?':
        Serial.println("Question");
        setPattern(QUESTION);
        delay(2000);
        break;
      default:
        Serial.println("Unknown command");
    }
  }
}



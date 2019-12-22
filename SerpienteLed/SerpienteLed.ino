#include <HTDriver.h>

#define LEDARRAY_D 2
#define LEDARRAY_C 3
#define LEDARRAY_B 4
#define LEDARRAY_A 5
#define LEDARRAY_OE 6
#define LEDARRAY_DI 7
#define LEDARRAY_CLK 8
#define LEDARRAY_ST 9

#define PX A0
#define PY A1

#define TGR_UP 700
#define TGR_DW 300
#define DT 500 //Time between frames

unsigned char board[16][16];

int currentSize = 5;
int x, y;   //Coordinates of the point on the screen
int sx, sy; //Score position
int vx = 0, vy = 1; //Velocity vector
long t; //Counter

HTDriver driver(LEDARRAY_A,LEDARRAY_B,LEDARRAY_C,LEDARRAY_D,LEDARRAY_OE,LEDARRAY_DI,LEDARRAY_CLK,LEDARRAY_ST);

void spawnPoint() {
  do {
    sx = random(0,15); 
    sy = random(0,15);
  } while (board[sx][sy] > 0); //Do not spawn in the body
}

void reset() {
  currentSize = 5;
  for (int i = 0;i < 16;i++)
    for(int j = 0;j < 16;j++)
      board[i][j] = 0;
  x = random(0,15); 
  y = random(0,15);
  spawnPoint();
}

void updateVel() {
  int valX = analogRead(PX);
  int valY = analogRead(PY);
  int nx = vx, ny = vy; //New vectors
  if (valX > TGR_UP) {
    nx = 0; 
    ny = 1;
  } else if (valX < TGR_DW) {
    nx = 0; 
    ny = -1;
  } else if (valY > TGR_UP) {
    nx = 1; 
    ny = 0;
  } else if (valY < TGR_DW) {
    nx = -1; 
    ny = 0;
  }
  //Check it does not collide with itself
  if (!(vx == nx && vy != ny) && !(vx != nx && vy == ny)) {
    vx = nx;
    vy = ny;  
  }
  //Serial.println("Vel x: " + String(vx) + " y: " + String(vy));
}

void updatePos() {
  //X
  x += vx;
  x = x > 15 ? 0 : x;
  x = x < 0 ? 15 : x;
  //Y
  y += vy;
  y = y > 15 ? 0 : y;
  y = y < 0 ? 15 : y;
}

void updateMatrix() {
  for (int i = 0;i < 16;i++) {
    for(int j = 0;j < 16;j++) {
      board[i][j] = max(0, board[i][j] - 1);
      driver.setPixel(i, j, board[i][j] > 0 ? HIGH : LOW);
    }
  }
  driver.setPixel(sx, sy, HIGH);
}

void updateGame() {
  updateVel();
  updatePos();
  if (sx == x && sy == y) {
    spawnPoint();
    currentSize++;
  } else if (board[x][y] > 0) //Collision with body
    reset();
  board[x][y] = currentSize;
  //Update matrix
  updateMatrix();
}

void setup() {
  driver.begin();
  pinMode(PX, INPUT);
  pinMode(PY, INPUT);
  randomSeed(analogRead(A5));
  reset();
  t = millis();
  Serial.begin(9600);
}

void loop() {
  if (millis() - t > DT) { //Update screen
    updateGame();
    t = millis();
  }
  driver.update();
}


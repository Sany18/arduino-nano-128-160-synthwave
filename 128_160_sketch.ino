#include <TFT.h>
#include <SPI.h>
#include <SD.h>

// pin definition
#define cs   4
#define dc   3
#define rst  2

int Y = 128;
int X = 160;

int iteration = 1;

// create an instance of the library
TFT TFTscreen = TFT(cs, dc, rst);

void setup() {
  TFTscreen.begin();
  drawSky();
  drawGround();
}

void loop() {
  drawGroundLines();
  iteration++;
}

void drawGroundLines() {
  int amount_of_lines = 16;

  for (int i = 0; i <= amount_of_lines; i++) {
    int stepX = X / amount_of_lines;
    int stepY = Y / amount_of_lines / 2;
    float previousStepMultiplier = getStepMultiplier(iteration - 1); // 0..1
    float currentStepMultiplier = getStepMultiplier(iteration); // 0..1

    // remove previous lines
    int Y_pos_prev = pow(i + previousStepMultiplier, 2) + 64;
    TFTscreen.stroke(41, 4, 27); // ground color
    if (i <= amount_of_lines / 2) { // avoid lines off screen
      TFTscreen.line(0, Y_pos_prev, 160, Y_pos_prev); // horizontal lines
    }

    // draw new lines
    TFTscreen.stroke(77, 15, 55); // lines color
    int Y_pos = pow(i + currentStepMultiplier, 2) + 64;
    if (i <= amount_of_lines / 2) { // avoid horizontal lines off screen
      TFTscreen.line(0, Y_pos, 160, Y_pos); // horizontal lines
    }
 
    TFTscreen.line(stepX * i * 3 - 160, 128, stepX * i, 65); // vertical lines    
  }

  TFTscreen.noStroke();
}

void drawSky() {
  // sky
  TFTscreen.fill(10, 0, 15); // dark purple (sky color)
  TFTscreen.rect(0,0,160,64);  

  // sun
  TFTscreen.fill(10, 103, 201); // orange
  TFTscreen.circle(80, 50, 26);

  // sun lines
  TFTscreen.fill(10, 0, 15); // sky color
  TFTscreen.rect(54,22,53,6);
  TFTscreen.rect(54,32,53,4);
  TFTscreen.rect(54,41,53,3);
  TFTscreen.rect(54,50,53,2);
  TFTscreen.rect(54,58,53,1);

  // left mountains
  int groundHeight = 63;
  drawMountain(-10, 50, 12, 0x4007);
  drawMountain(15, 30, 18, 0x4007);
  drawMountain(35, 20, 10, 0x3005);

  // right mountains
  drawMountain(102, 20, 10, 0x4007);
  drawMountain(130, 30, 20, 0x0801);
  drawMountain(115, 18, 5, 0x2001);
}

void drawGround() {
  TFTscreen.fill(41, 4, 27); // purple
  TFTscreen.rect(0,64,160,64);
}

void drawMountain(int positionX, int width, int height, int color) {
  int groundHeight = 63;
  TFTscreen.fillTriangle(positionX, groundHeight, positionX + width / 2, groundHeight - height, positionX + width, groundHeight, 0x4007);
}

float getStepMultiplier(int _step) { // 0...9999 to 0...1
  int a = _step % 10;
  return a * 0.1;
}

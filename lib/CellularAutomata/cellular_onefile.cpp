/*
  Connections:
  ST7789:            ESP32:
  SCL (clock) ------- GPIO_19
  SDA (data in) ----- GPIO_18
  RES (reset) ------- GPIO_5
  DC (data/command) - GPIO_17
  CS (chip select) -- GPIO_16
  BLK (blank  backlit) -- GPIO_4

Resolution: 240px x 280px
Size: 1.69 inch
*/
//Cellular automata to main.cpp in one file without external library


#include <SPI.h>

#include <TFT_eSPI.h> // Hardware-specific library

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

//#define GRIDX 80
//#define GRIDY 60
//#define CELLXY 4

#define GRIDX 160
#define GRIDY 120
#define CELLXY 2

#define GEN_DELAY 0

//Current grid
uint8_t grid[GRIDX][GRIDY];

//The new grid for the next generation
uint8_t newgrid[GRIDX][GRIDY];

//Number of generations
#define NUMGEN 600

uint16_t genCount = 0;

void initGrid();
void drawGrid();
void computeCA();
int getNumberOfNeighbors(int x, int y);



void setup()   {

  //Set up the display
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(0, 0);

}

void loop() {

  //Display a simple splash screen
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(2);
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(40, 5);
  tft.println(F("Arduino"));
  tft.setCursor(35, 25);
  tft.println(F("Cellular"));
  tft.setCursor(35, 45);
  tft.println(F("Automata"));

  delay(1000);

  tft.fillScreen(TFT_BLACK);

  initGrid();

  genCount = NUMGEN;

  drawGrid();

  //Compute generations
  for (int gen = 0; gen < genCount; gen++)
  {
    computeCA();
    drawGrid();
    delay(GEN_DELAY);
    for (int16_t x = 1; x < GRIDX-1; x++) {
      for (int16_t y = 1; y < GRIDY-1; y++) {
        grid[x][y] = newgrid[x][y];
      }
    }

  }
}

//Draws the grid on the display
void drawGrid(void) {
  uint16_t color = TFT_WHITE;
  for (int16_t x = 1; x < GRIDX - 1; x++) {
    for (int16_t y = 1; y < GRIDY - 1; y++) {
      if ((grid[x][y]) != (newgrid[x][y])) {
        if (newgrid[x][y] == 1) color = 0xFFFF; // Change color based on cell state
        else color = TFT_BLACK;
        tft.fillRect(CELLXY * x, CELLXY * y, CELLXY, CELLXY, color);
      }
    }
  }
}


//Initialise Grid
void initGrid(void) {
  for (int16_t x = 0; x < GRIDX; x++) {
    for (int16_t y = 0; y < GRIDY; y++) {
      newgrid[x][y] = 0;

      if (x == 0 || x == GRIDX - 1 || y == 0 || y == GRIDY - 1) {
        grid[x][y] = 0;
      }
      else {
        if (random(3) == 1)
          grid[x][y] = 1;
        else
          grid[x][y] = 0;
      }

    }
  }
}

//Compute the CA. Basically everything related to CA starts here
void computeCA() {
  for (int16_t x = 1; x < GRIDX; x++) {
    for (int16_t y = 1; y < GRIDY; y++) {
      int neighbors = getNumberOfNeighbors(x, y);
      if (grid[x][y] == 1 && (neighbors == 2 || neighbors == 3 ))
      {
        newgrid[x][y] = 1;
      }
      else if (grid[x][y] == 1)  newgrid[x][y] = 0;
      if (grid[x][y] == 0 && (neighbors == 3))
      {
        newgrid[x][y] = 1;
      }
      else if (grid[x][y] == 0) newgrid[x][y] = 0;
    }
  }
}

// Check the Moore neighbourhood
int getNumberOfNeighbors(int x, int y) {
  return grid[x - 1][y] + grid[x - 1][y - 1] + grid[x][y - 1] + grid[x + 1][y - 1] + grid[x + 1][y] + grid[x + 1][y + 1] + grid[x][y + 1] + grid[x - 1][y + 1];
}







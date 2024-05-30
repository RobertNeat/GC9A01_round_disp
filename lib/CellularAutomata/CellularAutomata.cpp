#include "CellularAutomata.h"
#include <SPI.h>
#include <TFT_eSPI.h>

CellularAutomata::CellularAutomata(TFT_eSPI &display) : tft(display), genCount(0) {}

void CellularAutomata::setup() {
    tft.init();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE);
    tft.setCursor(0, 0);
    displaySplashScreen();
    initGrid();
    drawGrid();
}

void CellularAutomata::loop() {
    if (genCount < NUMGEN) {
        computeCA();
        drawGrid();
        delay(GEN_DELAY);
        for (int16_t x = 1; x < GRIDX - 1; x++) {
            for (int16_t y = 1; y < GRIDY - 1; y++) {
                grid[x][y] = newgrid[x][y];
            }
        }
        genCount++;
    } else {
        genCount = 0;
        displaySplashScreen();
        initGrid();
    }
}


void CellularAutomata::initGrid() {
    for (int16_t x = 0; x < GRIDX; x++) {
        for (int16_t y = 0; y < GRIDY; y++) {
            newgrid[x][y] = 0;
            if (x == 0 || x == GRIDX - 1 || y == 0 || y == GRIDY - 1) {
                grid[x][y] = 0;
            } else {
                grid[x][y] = random(3) == 1 ? 1 : 0;
            }
        }
    }
}

void CellularAutomata::drawGrid() {
    uint16_t color = TFT_WHITE;
    for (int16_t x = 1; x < GRIDX - 1; x++) {
        for (int16_t y = 1; y < GRIDY - 1; y++) {
            if (grid[x][y] != newgrid[x][y]) {
                color = newgrid[x][y] == 1 ? 0xFFFF : TFT_BLACK;
                tft.fillRect(CELLXY * x, CELLXY * y, CELLXY, CELLXY, color);
            }
        }
    }
}

void CellularAutomata::computeCA() {
    for (int16_t x = 1; x < GRIDX; x++) {
        for (int16_t y = 1; y < GRIDY; y++) {
            int neighbors = getNumberOfNeighbors(x, y);
            if (grid[x][y] == 1) {
                newgrid[x][y] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
            } else {
                newgrid[x][y] = (neighbors == 3) ? 1 : 0;
            }
        }
    }
}

int CellularAutomata::getNumberOfNeighbors(int x, int y) {
    return grid[x - 1][y] + grid[x - 1][y - 1] + grid[x][y - 1] + grid[x + 1][y - 1] +
           grid[x + 1][y] + grid[x + 1][y + 1] + grid[x][y + 1] + grid[x - 1][y + 1];
}

void CellularAutomata::displaySplashScreen() {
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
}

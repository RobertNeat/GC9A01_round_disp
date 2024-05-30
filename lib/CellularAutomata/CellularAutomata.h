#ifndef CELLULAR_AUTOMATA_H
#define CELLULAR_AUTOMATA_H

#include <TFT_eSPI.h>

class CellularAutomata {
public:
    CellularAutomata(TFT_eSPI &display);
    void setup();
    void loop();

private:
    static const int GRIDX = 160;
    static const int GRIDY = 120;
    static const int CELLXY = 2;
    static const int GEN_DELAY = 0;
    static const int NUMGEN = 600;

    TFT_eSPI &tft;
    uint8_t grid[GRIDX][GRIDY];
    uint8_t newgrid[GRIDX][GRIDY];
    uint16_t genCount;

    void initGrid();
    void drawGrid();
    void computeCA();
    int getNumberOfNeighbors(int x, int y);
    void displaySplashScreen();
};

#endif


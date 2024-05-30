/*  //cellular automata code
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <CellularAutomata.h>

TFT_eSPI tft = TFT_eSPI();
CellularAutomata automata(tft);

void setup() {
    automata.setup();
}

void loop() {
    automata.loop();
}
*/



/*
  Connections:
  GC9A01:            ESP32:
  RST (reset) ------- GPIO_27
  CS (chip select) -- GPIO_26
  DC (data/command) - GPIO_25
  SDA (data in) ----- GPIO_33
  SCL (clock) ------- GPIO_32

  resolution: 240px x 240px
  size: 1.28 inch
*/


#include <Arduino.h>
#include <TFT_eSPI.h>       // Include the graphics library
TFT_eSPI tft = TFT_eSPI();  // Create object "tft"

void setup_global_arc(); //common setups for arcs
void setup_first_arc(); //setup for first (outer) arc
void setup_second_arc(); //setup for second arc
void setup_third_arc(); //setup for third arc

//Inicjalizacja zmiennych zewnętrznego łuku:
uint16_t bg_color;
uint16_t x;
uint16_t y;
uint8_t thickness;
uint16_t start_angle;
bool arc_end = true;           // true = round ends, false = square ends (arc_end parameter can be omitted, ends will then be square)

uint16_t first_fg_color;
uint8_t first_radius;
uint8_t first_inner_radius;
uint16_t first_end_angle = 10;

  //second arc properties
uint16_t second_fg_color;
uint8_t second_radius;
uint8_t second_inner_radius;
uint16_t second_end_angle = 10;

  //third arc properties
uint16_t third_fg_color;
uint8_t third_radius;
uint8_t third_inner_radius;
uint16_t third_end_angle = 10;

uint16_t loop_counter = 0;
int16_t textWidth = 0;
int16_t textHeight = 0;
bool first_loop = true;

void setup(void) {
  Serial.begin(115200);

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  setup_global_arc();
  setup_first_arc();
  setup_second_arc();
  setup_third_arc();

  for(int i=0;i<365;i++){
    tft.drawSmoothArc(x, y, first_radius, first_inner_radius, start_angle, first_end_angle, first_fg_color, bg_color, arc_end);
    tft.drawSmoothArc(x, y, second_radius, second_inner_radius, start_angle, second_end_angle, second_fg_color, bg_color, arc_end);
    tft.drawSmoothArc(x, y, third_radius, third_inner_radius, start_angle, third_end_angle, third_fg_color, bg_color, arc_end);
    first_end_angle += 1;
    second_end_angle += 1;
    third_end_angle += 1;

    //delay(1);
  }
  first_end_angle = 10;
  second_end_angle = 10;
  third_end_angle = 10;

  tft.fillScreen(TFT_BLACK);
}

void loop()
{
  if(first_loop){
    textWidth = 25;
    textHeight = 40;
  }else{
    textWidth = tft.textWidth(std::to_string(loop_counter).c_str());
    textHeight = tft.fontHeight();
  }
  

  tft.setCursor((tft.width()/2)-(textWidth/2),(tft.height()/2)-(textHeight/2));//wyśrodkowanie poziome jest zastosowane
  tft.setTextColor(TFT_WHITE, TFT_BLACK, true),
  tft.setTextSize(4);
  tft.setTextFont(2);
  tft.print(loop_counter);
  loop_counter ++;

  first_loop = false;
  delay(1000); 
}

void setup_global_arc(){
  bg_color = TFT_BLACK;       // This is the background colour used for smoothing (anti-aliasing)
  x = tft.width()/2;  // Position of centre of arc
  y = tft.height()/2;
  thickness = 10;     // Thickness
  start_angle = 0; // Start angle must be in range 0 to 360
}

void setup_first_arc(){
  first_fg_color = 0xf818;  //RGB565 color picker
  first_radius = 120;       // Outer arc radius
  first_inner_radius = first_radius - thickness;        // Calculate inner radius (can be 0 for circle segment)
}

void setup_second_arc(){
  second_fg_color = 0x8760;
  second_radius = 100;
  second_inner_radius = second_radius - thickness;
}

void setup_third_arc(){
  third_fg_color = 0x05fb;
  third_radius = 80;
  third_inner_radius = third_radius - thickness;
}

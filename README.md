# GC9A01 round display

This project is the user setup for GC9A01 working with TFTeSPI.

Pin setup is as follows (can be changed in UserSetup.h):

```
  Connections:
  GC9A01:            ESP32:
  RST (reset) ------- GPIO_27
  CS (chip select) -- GPIO_26
  DC (data/command) - GPIO_25
  SDA (data in) ----- GPIO_33
  SCL (clock) ------- GPIO_32
```

### Display properties:

- Screen technology: TFT LCD
- Interface: SPI
- Colour display
- Resolution: 240px x 240px
- Size: 1.28 inch
- Brightness: 400 CD/m2
- Logic voltage: 3.3 V

### ESP 32 pinout:

![ESP32-DEV-CP2102-C-003](https://github.com/RobertNeat/GC9A01_round_disp/assets/47086490/bae3be4e-c9f3-493d-93c9-11ee169ad772)

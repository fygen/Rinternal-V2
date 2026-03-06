#ifndef OLED_H
#define OLED_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

class OLED {
public:
    OLED() : display(128, 64, &Wire, -1) {} // Constructor içinde başlatma
    void setup();
    int write(const String& message) { return write(message.c_str()); }
    int write(const char *message);
    void clear();

private:
    Adafruit_SSD1306 display;
    int cursorX = 0;
    int cursorY = 0;
    const int lineHeight = 10; 
    const int screenWidth = 128;
    const int screenHeight = 64;
};

#endif
#ifndef OLED_H
#define OLED_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class OLED {
public:
    // Pass the display reference or initialize it here
    void setup();
    void write(const char *message);
    void clear();
    void setCursor(int x, int y);
    void loop(); // If you need to handle any updates or animations
private:
    Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire, -1);
    int cursorX = 0;
    int cursorY = 0;
    const int lineHeight = 10; // Adjust based on your font size
    const int screenWidth = 128;
    const int screenHeight = 64;
};
#endif
#ifndef OLED_H
#define OLED_H

#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#define OLED_RESET     U8X8_PIN_NONE // Reset pin
#define OLED_SDA 14                  // D6
#define OLED_SCL 12           // D5

class OLED {
public:
    // ESP8266 için: F = Full Buffer, HW = Hardware I2C
    // Pins: D2 (SDA), D1 (SCL) varsayılan donanım pinleridir.
    OLED() : u8g2(U8G2_R0, OLED_RESET, OLED_SCL, OLED_SDA) {}

    void setup();
    int write(const String& message);
    int write(const char *message);
    void clear();

private:
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;
    int cursorX = 0;
    int cursorY = 10; // U8g2'de cursor (0,0) sol alt köşe gibidir, o yüzden 10'dan başlarız
    const int lineHeight = 12; 
    const int screenWidth = 128;
    const int screenHeight = 64;
};

#endif
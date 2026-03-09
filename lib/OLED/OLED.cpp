#include "OLED.h"

void OLED::setup()
{
    // 0x3C genelde SSD1306 adresidir.
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println(F("SSD1306 allocation failed"));
        return;
    }
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.display();
    display.println("OLED Baslatildi!");
    Serial.println("OLED Baslatildi!");
}

// Hem String hem char* desteği
int OLED::write(const String &message) { return write(message.c_str()); }

int OLED::write(const char *message)
{
    int16_t x1, y1;
    uint16_t w, h;
    display.getTextBounds(message, cursorX, cursorY, &x1, &y1, &w, &h);

    // Satır sonuna gelindi mi?
    if (cursorX + w > screenWidth)
    {
        cursorX = 0;
        cursorY += lineHeight;
    }

    // Ekran doldu mu?
    if (cursorY + h > screenHeight)
    {
        display.clearDisplay();
        cursorX = 0;
        cursorY = 0;
    }

    display.setCursor(cursorX, cursorY);
    display.print(message);
    display.print(" "); // Kelime arası boşluk
    display.display();

    // İmleci güncelle
    cursorX = display.getCursorX();
    cursorY = display.getCursorY();
    return 1;
}

void OLED::clear()
{
    display.clearDisplay();
    display.display();
    cursorX = 0;
    cursorY = 0;
}
#ifndef OLED_CONTROL_FROM_U8GLIB2_H
#define OLED_CONTROL_FROM_U8GLIB2_H

#include <U8g2lib.h>
extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;
#define OLED_RESET     U8X8_PIN_NONE // Reset pin
#define OLED_SDA 14                  // D6
#define OLED_SCL 12           // D5

void handle_oled(int c);
void write_to_oled(const char* str);
#endif // OLED_CONTROL_FROM_U8GLIB2_H
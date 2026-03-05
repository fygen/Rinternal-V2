
#include "oledControlFromU8glib2.hpp"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, OLED_RESET, OLED_SCL, OLED_SDA);

void handle_oled(int c) {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 10, "Display is working!");
  u8g2.drawStr(0, 30, "Have fun with it");
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "Uptime: %ds", c);
  u8g2.drawStr(0, 50, buffer);
  u8g2.sendBuffer();
}

void write_to_oled(const char* str){
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0, 10, str);
    u8g2.sendBuffer();
}



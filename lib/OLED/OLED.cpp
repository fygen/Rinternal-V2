#include "OLED.h"

String OLED::setBrightness(int level)
{
    if (level < 0 || level > 255)
    {
        return "Hata: Parlaklık seviyesi 0-255 arasında olmalıdır.";
    }
    u8g2.setContrast(level);
    return "Parlaklık seviyesi ayarlandı."; // Başarılı
}

String OLED::getOledStatus()
{
    return "CursorX: " + String(cursorX) + ", CursorY: " + String(cursorY) +
           ", ScreenWidth: " + String(screenWidth) + ", ScreenHeight: " + String(screenHeight) +
           ", LineHeight: " + String(lineHeight);
}
String OLED::setCursor(int x, int y)
{
    cursorX = x;
    cursorY = y;
    return "Cursor ayarlandı."; // Başarılı
}
String OLED::setLineHeight(int height)
{
    lineHeight = height;
    return "Satır yüksekliği ayarlandı."; // Başarılı
}
String OLED::setScreenSize(int width, int height)
{
    screenWidth = width;
    screenHeight = height;
    return "Ekran boyutu ayarlandı."; // Başarılı
}

void OLED::setup()
{
    Serial.println("OLED: U8g2 baslatiliyor...");

    // ESP8266 varsayılan I2C pinleri (SDA=4, SCL=5)
    // Eğer farklı pin kullanıyorsan Wire.begin(SDA, SCL); yapmalısın.
    if (!u8g2.begin())
    {
        Serial.println("OLED: u8g2.begin() FAILED!");
        return;
    }

    u8g2.setFont(u8g2_font_ncenB08_tr); // Standart okunabilir font
    u8g2.clearBuffer();
    u8g2.drawStr(0, 10, "OLED Hazir!");
    u8g2.sendBuffer();
    u8g2.setContrast(brightness); // Varsayılan parlaklık

    Serial.println("OLED: Baslatildi ve Test Mesaji Yazildi.");
}

int OLED::write(const String &message) { return write(message.c_str()); }

int OLED::write(const char *message)
{
    // Fonta göre metin genişliğini hesapla
    int w = u8g2.getStrWidth(message);

    // Satır sonu kontrolü
    if (cursorX + w > screenWidth)
    {
        cursorX = 0;
        cursorY += lineHeight;
    }

    // Ekran doldu mu kontrolü
    if (cursorY > screenHeight)
    {
        u8g2.clearBuffer();
        cursorX = 0;
        cursorY = lineHeight;
    }

    // Yazdır
    u8g2.drawStr(cursorX, cursorY, message);
    u8g2.sendBuffer();

    // İmleci bir sonraki kelime için kaydır (boşluk payı ile)
    cursorX += w + 4;

    return 1;
}

void OLED::clear()
{
    u8g2.clearBuffer();
    u8g2.sendBuffer();
    cursorX = 0;
    cursorY = lineHeight;
}
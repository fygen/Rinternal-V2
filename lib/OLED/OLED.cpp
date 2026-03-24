#include "OLED.h"

String OLED::setInverse(bool isInverse) {
    u8g2.setBitmapMode(isInverse); // Karakter bazlı tersleme
    // Veya tüm ekranı donanımsal olarak ters çevirmek için:
    // u8g2.sendF("c", isInverse ? 0xA7 : 0xA6); 
    return isInverse ? "Ters mod etkinlestirildi." : "Ters mod devre disi birakildi.";
}

String OLED::drawProgressBar(int x, int y, int w, int h, int percentage) {
    if (percentage > 100) percentage = 100;
    if (percentage < 0) percentage = 0;
    
    // Dış çerçeve
    u8g2.drawFrame(x, y, w, h);
    // İç doluluk
    int barWidth = ((w - 4) * percentage) / 100;
    u8g2.drawBox(x + 2, y + 2, barWidth, h - 4);
    u8g2.sendBuffer();
    return "İlerleme çubuğu çizildi.";
}

String OLED::drawCentered(int y, const char* message) {
    int w = u8g2.getStrWidth(message);
    int x = (screenWidth - w) / 2;
    u8g2.drawStr(x, y, message);
    u8g2.sendBuffer();
    return "Metin ortalandı.";
}

String OLED::setBrightness(int level)
{
    if (level < 0 || level > 255)
    {
        return "Hata: Parlaklık seviyesi 0-255 arasında olmalıdır.";
    }
    u8g2.setContrast(level);

    u8g2.beginSimple();

    return "Parlaklık seviyesi ayarlandı."; // Başarılı
}


String OLED::getStatus()
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
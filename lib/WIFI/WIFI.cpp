#include "WIFI.h"
#include "SYSTEM.h" // SYSTEM sınıfını dahil ediyoruz, böylece burada kullanabiliriz.
#include "OLED.h"

WIFI::WIFI(){}

String WIFI::setup()
{
    WiFiManager wm;
    delay(100);
    sys.oled->write("WiFi Baglaniliyor...");

    bool res = wm.autoConnect("AutoConnectAP","password"); 

    if(!res) {
        Serial.println("Bağlantı başarısız veya zaman aşımı.");
        // ESP.restart(); // İstersen burada reset atabilirsin
        return "Bağlantı başarısız veya zaman aşımı.";
    } else {
        Serial.println("WiFi Bağlandı..!");
        Serial.print("IP Adresiniz: ");
        Serial.println(WiFi.localIP());
        return  "IP Adresiniz: " +  WiFi.localIP().toString();
    }
}

String WIFI::reset()
{
    WiFiManager wm;
    wm.resetSettings();
    return "WiFi Ayarları Sıfırlandı. Cihazı yeniden başlatın.";
}

String WIFI::connect()
{
    WiFi.begin();
    return "WiFi Bağlantısı kuruldu.";
}

String WIFI::restart()
{
    ESP.restart();
    return "Cihaz yeniden başlatılıyor.";
}
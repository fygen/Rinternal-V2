#include "WIFI.h"

WIFI::WIFI()
{
    setup();
}

String WIFI::setup()
{
    Serial.begin(115200);
    WiFiManager wm;
    delay(100);

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
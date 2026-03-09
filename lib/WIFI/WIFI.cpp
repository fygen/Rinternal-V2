#include "WIFI.h"
#include "SYSTEM.h" // SYSTEM sınıfını dahil ediyoruz, böylece burada kullanabiliriz.
#include "OLED.h"

WIFI::WIFI(){}

String WIFI::setup()
{
    WiFiManager wm;
    sys.oled->write("WIFI bagli degilse...");
    sys.oled->write("AutoConnectAP-password");
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
    setup(); // Sıfırladıktan sonra tekrar bağlanmayı dene
}

String WIFI::connect(String ssid, String password)
{
    WiFi.begin(ssid, password); // Buraya kendi WiFi bilgilerinizi girin
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) { // Ba
        attempts++;
    }
    if (WiFi.status() == WL_CONNECTED) {
        return "WiFi Bağlantısı kuruldu.";
    } else {
        return "WiFi Bağlantısı kurulamadı.";
    }
    return "WiFi Bağlantısı kuruldu.";
}

String WIFI::restart()
{
    ESP.restart();
    return "Cihaz yeniden başlatılıyor.";
}
#include "WIFI.h"
#include "SYSTEM.h" // SYSTEM sınıfını dahil ediyoruz, böylece burada kullanabiliriz.
#include "OLED.h"

WIFI::WIFI() {}

String WIFI::getIP() { return WiFi.localIP().toString(); }
String WIFI::getMAC() { return WiFi.macAddress(); }
String WIFI::getSSID() { return WiFi.SSID(); }
String WIFI::getPassword() { return WiFi.psk(); }
String WIFI::getStatus()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        return "Connected to " + WiFi.SSID() + " with IP: " + WiFi.localIP().toString();
    }
    else
    {
        return "Not connected to WiFi.";
    }
}

String WIFI::getStatusAll()
{
    String status = "<br/>MAC: " + getMAC() + "\n";
    status += "<br/>IP: " + getIP() + "\n";
    status += "<br/>SSID: " + getSSID() + "\n";
    status += "<br/>Password: " + getPassword() + "\n";
    status += "<br/>Connection Status: " + getStatus();
    return status;
}

String WIFI::setup()
{
    WiFiManager wm;
    sys.oled->write("WIFI bagli degilse...");
    sys.oled->write("AutoConnectAP-password");
    bool res = wm.autoConnect("AutoConnectAP", "password");

    if (!res)
    {
        Serial.println("Bağlantı başarısız veya zaman aşımı.");
        // ESP.restart(); // İstersen burada reset atabilirsin
        return "Bağlantı başarısız veya zaman aşımı.";
    }
    else
    {
        Serial.println("WiFi Bağlandı..!");
        Serial.print("IP: ");
        Serial.println(WiFi.localIP());
        return "IP: " + WiFi.localIP().toString();
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
    while (WiFi.status() != WL_CONNECTED && attempts < 20)
    { // Ba
        attempts++;
    }
    if (WiFi.status() == WL_CONNECTED)
    {
        return "WiFi Bağlantısı kuruldu.";
    }
    else
    {
        return "WiFi Bağlantısı kurulamadı.";
    }
    return "WiFi Bağlantısı kuruldu.";
}

String WIFI::restart()
{
    ESP.restart();
    return "Cihaz yeniden başlatılıyor.";
}
#ifndef SERVER_H
#define SERVER_H

#include <ESP8266WebServer.h>

class SERVER {
public:
    SERVER() : server(80) {} // Port 80'de başlat
    
    void setup();
    void loop();

private:
    ESP8266WebServer server;

    // Route Handler'lar (Özel fonksiyonlar)
    void handleRoot();
    void handleSensor();
    void handleLED();
    void handleResetWiFi();
    void handleExecute();
    void handleNotFound();
};

#endif
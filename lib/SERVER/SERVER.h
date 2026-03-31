#ifndef SERVER_H
#define SERVER_H
#include <map>
#include <functional>
#include <ESP8266WebServer.h>

class SERVER {
public:
    SERVER() : server(80) { registerCommands(); }// Port 80'de başlat
    
    void setup();
    void loop();
    void handleExecute();
    void commandParseAndExecute(String rawInput);
    void logger(String message);

private:
    ESP8266WebServer server;
    std::map<String, std::function<void(std::vector<String>)>> commandMap;

    // Route Handler'lar (Özel fonksiyonlar)
    void registerCommands();
    void handleRoot();
    void handleSensor();
    void handleLED();
    void handleResetWiFi();
    void handleNotFound();
};

#endif
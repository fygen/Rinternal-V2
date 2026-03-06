#ifndef WIFI_H
#define WIFI_H
#include <Arduino.h>
#include <WiFiManager.h>

class OLED; // Forward declaration

class WIFI {
public:
    String setup();
    String reset();
    String connect();
    String restart();
private:
    String mac_address[18];
    String ip_address[16];
    String ssid[32];
    String password[64];
};

#endif
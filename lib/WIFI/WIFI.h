#ifndef WIFI_H
#define WIFI_H
#include <Arduino.h>
#include <WiFiManager.h>

class WIFI {
public:
    WIFI() {} // Default constructor
    String setup();
    String reset();
    String connect();
    String restart();
    // getters for WiFi information
    String getIP() { return WiFi.localIP().toString(); }
    String getMAC() { return WiFi.macAddress(); }
    String getSSID() { return WiFi.SSID(); }
    String getPassword() { return WiFi.psk(); }
};

#endif
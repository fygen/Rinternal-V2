#ifndef WIFI_H
#define WIFI_H
#include <Arduino.h>
#include <WiFiManager.h>

class WIFI {
public:
    WIFI(); // Default constructor
    String setup();
    String reset();
    String connect(String ssid, String password);
    String restart();
    // getters for WiFi information
    String getIP();
    String getMAC();
    String getSSID();
    String getPassword();
    String getStatus();
    String getStatusAll();
};

#endif
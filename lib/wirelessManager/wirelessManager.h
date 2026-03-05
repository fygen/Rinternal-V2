#ifndef WIFI_H
#define WIFI_H

class OLED; // Forward declaration

class WiFi {
public:
    void setOLED(OLED* oledPtr);
    void connect();
    void restart();
private:
    OLED* _oled = nullptr; 
};

#endif
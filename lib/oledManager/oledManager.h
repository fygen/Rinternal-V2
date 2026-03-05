#ifndef OLED_H
#define OLED_H

class WiFi; // Forward declaration

class OLED {
public:
    void connect();   
    void setWiFi(WiFi* wifiPtr);
    void write(const char* message);
private:
    WiFi* _wifi = nullptr;
};

#endif
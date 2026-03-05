#ifndef SYSTEM_H
#define SYSTEM_H

// Forward declarations
class WiFi;
class OLED;
class Sensor;

struct System {
    WiFi* wifi;
    OLED* oled;
    Sensor* sensor;
};

// Declare that a global instance exists somewhere
extern System sys; 

#endif
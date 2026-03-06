#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H
#include "WIFI.h"
#include "OLED.h"
#include "SERVER.h"
#include "FSM.h"

class SYSTEM {
public:
    // This is the only way to get the "System"
    static SYSTEM& getInstance() {
        static SYSTEM instance; 
        return instance;
    }

    // Pointers to your modules
    WIFI wifi;
    OLED oled;
    SERVER server;
    FSM fsm;
    
    // Optional: A central "Emergency Stop" or "Init All"
    void beginAll();

private:
    // Private constructor: stops anyone from doing "SYSTEM mySys;"
    SYSTEM() {} 
    
    // Stop copying the manager
    SYSTEM(SYSTEM const&) = delete;
    void operator=(SYSTEM const&) = delete;
};

static SYSTEM& sys = SYSTEM::getInstance(); //Global bir takma ad olarak sys kullanabilirsiniz. sys.wifi->setup() gibi.

#endif
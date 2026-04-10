#ifndef SYSTEM_H
#define SYSTEM_H

#include <queue>
#include <vector>
#include <Arduino.h>

class OLED;
class WIFI;
class SERVER;
class FSM;
class HELPER;
class BATTERY;
class TIMER;

class SYSTEM {
public:
    // This is the only way to get the "System"
    static SYSTEM& getInstance() {
        static SYSTEM instance; 
        return instance;
    }

    // Pointers to your modules
    OLED* oled;
    WIFI* wifi;
    SERVER* server;
    FSM* fsm;
    HELPER* helper;
    BATTERY* battery;
    TIMER* timer;

    // Optional: A central "Emergency Stop" or "Init All"
    void beginAll();

    // Command Queue Methods
    void addToQueue(String script);
    void updateQueue();
    void stopQueue();
    void automate(String filename);
    void startQueue();
    std::queue<String> commandQueue;

    // The Global Response Catcher
    String lastResult = "";
    bool lastSuccess = false;

private:
    unsigned long _waitStartTime = 0;
    bool _isWaitingMillis = false;

    // Private constructor: stops anyone from doing "SYSTEM mySys;"
    SYSTEM() : oled(nullptr), wifi(nullptr), server(nullptr), fsm(nullptr), helper(nullptr), battery(nullptr), timer(nullptr) {
        // Constructor is empty because initialization happens in beginAll()
    }
    
    // Stop copying the manager
    SYSTEM(SYSTEM const&) = delete;
    void operator=(SYSTEM const&) = delete;
};

extern SYSTEM& sys;

#endif
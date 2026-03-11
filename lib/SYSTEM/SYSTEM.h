#ifndef SYSTEM_H
#define SYSTEM_H
class OLED;
class WIFI;
class SERVER;
class FSM;
class HELPER;

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
    
    // Optional: A central "Emergency Stop" or "Init All"
    void beginAll();

private:
    // Private constructor: stops anyone from doing "SYSTEM mySys;"
    SYSTEM() : oled(nullptr), wifi(nullptr), server(nullptr), fsm(nullptr) {
        // Constructor boş, çünkü beginAll()'de başlatacağız
    }
    
    // Stop copying the manager
    SYSTEM(SYSTEM const&) = delete;
    void operator=(SYSTEM const&) = delete;
};

extern SYSTEM& sys;

#endif
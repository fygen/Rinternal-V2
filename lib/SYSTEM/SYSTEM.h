#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

// Forward declarations
class WiFi;
class OLED;
class SERVER;

class SYSTEM {
public:
    // This is the only way to get the "System"
    static SYSTEM& getInstance() {
        static SYSTEM instance; 
        return instance;
    }

    // Pointers to your modules
    WiFi* wifi = nullptr;
    OLED* oled = nullptr;
    SERVER* server = nullptr;
    
    // Optional: A central "Emergency Stop" or "Init All"
    void beginAll();

private:
    // Private constructor: stops anyone from doing "SYSTEM mySys;"
    SYSTEM() {} 
    
    // Stop copying the manager
    SYSTEM(SYSTEM const&) = delete;
    void operator=(SYSTEM const&) = delete;
};

#endif
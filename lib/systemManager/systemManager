#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

// Forward declarations
class WiFi;
class OLED;

class SystemManager {
public:
    // This is the only way to get the "System"
    static SystemManager& getInstance() {
        static SystemManager instance; 
        return instance;
    }

    // Pointers to your modules
    WiFi* wifi = nullptr;
    OLED* oled = nullptr;

    // Optional: A central "Emergency Stop" or "Init All"
    void beginAll();

private:
    // Private constructor: stops anyone from doing "SystemManager mySys;"
    SystemManager() {} 
    
    // Stop copying the manager
    SystemManager(SystemManager const&) = delete;
    void operator=(SystemManager const&) = delete;
};

#endif
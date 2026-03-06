#include "WIFI.h"
#include "OLED.h"
#include "SERVER.h"
#include "SYSTEM.h"

void SYSTEM::beginAll() {
    // Initialize all modules
    wifi = new WIFI();
    oled = new OLED();
    server = new SERVER();
    // You can also call setup functions here if needed
}


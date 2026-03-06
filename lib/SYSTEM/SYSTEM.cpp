#include "SYSTEM.h"
#include "OLED.h"   // Gerçek dosyalar burada
#include "WIFI.h"
#include "SERVER.h"
#include "FSM.h"

void SYSTEM::beginAll() {
    // Nesneleri Heap üzerinde oluşturuyoruz (Pointer kullandığımız için)
    if(!oled)   oled = new OLED();
    if(!wifi)   wifi = new WIFI();
    if(!fsm)    fsm = new FSM();
    if(!server) server = new SERVER();

    // Başlatma sırası
    fsm->setup();
    oled->setup();
    wifi->setup();
    server->setup();
    
    oled->write("Sistem Hazir!");
}


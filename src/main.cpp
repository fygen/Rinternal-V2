#include <Arduino.h>
#include "SYSTEM.h"
#include "SERVER.h" // <--- BUNU EKLE (loop() kullanabilmek için)
#include "WIFI.h"

void setup() {
    // Seri portu debug için başlat
    Serial.begin(115200);
    delay(1000); 

    // Singleton örneğini al ve her şeyi ayağa kaldır
    // Bu fonksiyon; FSM, OLED, WIFI ve SERVER'ı sırayla başlatacak
    SYSTEM::getInstance().beginAll();

    Serial.println(">>> Sistem Tam Kapasite Calisiyor.");
}

void loop() {
    // Sadece server ve wifi gibi sürekli çalışması gereken modülleri döngüye sok
    sys.server->loop();
}
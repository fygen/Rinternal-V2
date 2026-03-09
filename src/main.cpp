#include <Arduino.h>
#include "SYSTEM.h"
#include "OLED.h"   
#include "WIFI.h"
#include "SERVER.h"
#include "FSM.h"

void setup() {
    // Seri portu debug için başlat
    Serial.begin(115200); 
    Serial.println(">>> Sistem Baslatiliyor...");
    // Singleton örneğini al ve her şeyi ayağa kaldır
    // Bu fonksiyon; FSM, OLED, WIFI ve SERVER'ı sırayla başlatacak
    sys.beginAll(); // Bu, SYSTEM sınıfında tanımladığımız beginAll() fonksiyonunu çağırır ve tüm modülleri başlatır

    Serial.println(">>> Sistem Tam Kapasite Calisiyor.");
    sys.oled->write(">>> Sistem Tam Kapasite Calisiyor.");
}

void loop() {
    // Sadece server ve wifi gibi sürekli çalışması gereken modülleri döngüye sok
    sys.server->loop();
}
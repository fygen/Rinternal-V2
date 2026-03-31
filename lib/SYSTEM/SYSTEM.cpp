#include "SYSTEM.h"
#include "OLED.h"   // Gerçek dosyalar burada
#include "WIFI.h"
#include "SERVER.h"
#include "FSM.h"
#include "HELPER.h"
#include "BATTERY.h"

void SYSTEM::beginAll() {
    float resistor = 4.0;
    // Nesneleri Heap üzerinde oluşturuyoruz (Pointer kullandığımız için)
    if(!oled)   oled = new OLED();
    if(!wifi)   wifi = new WIFI();
    if(!fsm)    fsm = new FSM();
    if(!server) server = new SERVER();
    if(!helper) helper = new HELPER();
    if(!battery) battery = new BATTERY(resistor);
    if(!timer) timer = new TIMER();
    

    // Başlatma sırası
    fsm->setup();
    oled->setup();
    String wifiStatus = wifi->setup();
    oled->write(wifiStatus);
    server->setup();
    
    oled->write(F("Sistem Hazir!"));

    // OTOMATİK BAŞLATMA: Eğer autorun dosyası varsa başlat
    if (fsm->fileexists("/autorun")) {
        automate(F("autorun"));
    }
}

void SYSTEM::addToQueue(String script) {
    // Both real \n and escaped \n handle
    script.replace("\\n", "\n");
    script.replace("\\r", "\r");
    
    std::vector<String> lines = HELPER::splitString(script, '\n');
    for (String line : lines) {
        line.trim();
        if (line.length() > 0 && !line.startsWith("#")) {
            commandQueue.push(line);
        }
    }
}

void SYSTEM::updateQueue() {
    if (commandQueue.empty()) return;

    String currentLine = commandQueue.front();
    
    // --- DURUM 1: ZAMANSAL BEKLEME (WAIT 2000) ---
    if (currentLine.startsWith("WAIT ")) {
        int ms = currentLine.substring(5).toInt();
        if (!_isWaitingMillis) {
            _waitStartTime = millis();
            _isWaitingMillis = true;
            server->logger("[QUEUE] Waiting " + String(ms) + "ms...");
        }
        if (millis() - _waitStartTime >= (unsigned long)ms) {
            _isWaitingMillis = false;
            server->logger("[QUEUE] Wait Done.");
            commandQueue.pop(); // Süre doldu, sıradakine geç
        }
        return;
    }

    // --- DURUM 2: ŞARTLI BEKLEME (WAIT_UNTIL MODUL KOMUT) ---
    if (currentLine.startsWith(F("WAIT_UNTIL "))) {
        String sub = currentLine.substring(11); // "WIFI isConnected"
        std::vector<String> tokens = HELPER::smartTokenize(sub);
        
        if (tokens.size() >= 2) {
            // Şartı kontrol etmek için dispatcher'ı çalıştır
            String result = HELPER::dispatchCommand(tokens[0], tokens[1], {});
            
            // Eğer cevap "true", "1", "OK" veya "Connected" ise geç
            if (result.equalsIgnoreCase(F("true")) || result == F("1") || result.equalsIgnoreCase(F("OK")) || result.equalsIgnoreCase(F("Connected"))) {
                server->logger(F("[QUEUE] Condition met: ") + tokens[1]);
                commandQueue.pop();
            } else if (result.startsWith(F("Error:"))) {
                // Eğer komut bulunamazsa veya hata varsa, kuyruğu kilitlememek için atla
                server->logger(F("[QUEUE] Condition Error: ") + result + F(" (Skipping)"));
                commandQueue.pop();
            }
        }
        return; // Şart sağlanana kadar burada takılı kalır (bloklamaz)
    }

    // --- DURUM 3: NORMAL KOMUT ÇALIŞTIRMA ---
    std::vector<String> tokens = HELPER::smartTokenize(currentLine);
    if (tokens.size() >= 2) {
        String mod = tokens[0];
        String cmd = tokens[1];
        std::vector<String> args;
        for(size_t i=2; i<tokens.size(); i++) args.push_back(tokens[i]);

        // Komutu çalıştır ve sonucunu al (Loglama dispatchCommand içinde yapılıyor)
        HELPER::dispatchCommand(mod, cmd, args);
        
        commandQueue.pop(); // Komut işlendi, kuyruktan at
    } else {
        // Hatalı komut formatı ise atla
        commandQueue.pop();
    }
}

void SYSTEM::stopQueue() {
    while (!commandQueue.empty()) {
        commandQueue.pop();
    }
    _isWaitingMillis = false;
    server->logger(F("[QUEUE] Stopped."));
}

void SYSTEM::automate(String filename) {
    String content = fsm->readfile(filename.c_str());
    if (content != "ERROR: File Not Found") {
        addToQueue(content);
        server->logger("Script yuklendi: " + filename);
    } else {
        server->logger("Hata: Script dosyasi bulunamadi: " + filename);
    }
}

SYSTEM& sys = SYSTEM::getInstance();

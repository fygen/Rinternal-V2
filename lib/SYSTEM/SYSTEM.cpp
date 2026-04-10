#include "SYSTEM.h"
#include "OLED.h" // Gerçek dosyalar burada
#include "WIFI.h"
#include "SERVER.h"
#include "FSM.h"
#include "HELPER.h"
#include "BATTERY.h"

void SYSTEM::beginAll()
{
    float resistor = 4.0;
    // Nesneleri Heap üzerinde oluşturuyoruz (Pointer kullandığımız için)
    if (!oled)
        oled = new OLED();
    if (!wifi)
        wifi = new WIFI();
    if (!fsm)
        fsm = new FSM();
    if (!server)
        server = new SERVER();
    if (!helper)
        helper = new HELPER();
    if (!battery)
        battery = new BATTERY(resistor);
    if (!timer)
        timer = new TIMER();

    // Başlatma sırası
    fsm->setup();
    oled->setup();
    String wifiStatus = wifi->setup();
    oled->write(wifiStatus);
    server->setup();

    oled->write(F("Sistem Hazir!"));

    // OTOMATİK BAŞLATMA: Eğer autorun dosyası varsa başlat
    if (fsm->fileexists("/start"))
    {
        automate(F("autorun"));
    }
}

void SYSTEM::addToQueue(String script)
{
    // Both real \n and escaped \n handle
    script.replace("\\n", "\n");
    script.replace("\\r", "\r");

    std::vector<String> lines = HELPER::splitString(script, '\n');
    for (String line : lines)
    {
        line.trim();
        if (line.length() > 0 && !line.startsWith("#"))
        {
            commandQueue.push(line);
        }
    }
}

void SYSTEM::updateQueue()
{
    if (commandQueue.empty())
        return;

    String currentLine = commandQueue.front();

    // --- DURUM 1: ZAMANSAL BEKLEME (WAIT 2000) ---
    if (currentLine.startsWith("WAIT "))
    {
        int ms = currentLine.substring(5).toInt();
        if (!_isWaitingMillis)
        {
            _waitStartTime = millis();
            _isWaitingMillis = true;
            server->logger("[QUEUE] Waiting " + String(ms) + "ms...");
        }
        if (millis() - _waitStartTime >= (unsigned long)ms)
        {
            _isWaitingMillis = false;
            server->logger("[QUEUE] Wait Done.");
            commandQueue.pop(); // Süre doldu, sıradakine geç
        }
        return;
    }

    // --- DURUM 2: ŞARTLI BEKLEME (WAIT_UNTIL MODUL KOMUT) ---
    if (currentLine.startsWith(F("WAIT_UNTIL ")))
    {
        String sub = currentLine.substring(11); // "WIFI isConnected"
        std::vector<String> tokens = HELPER::smartTokenize(sub);

        if (tokens.size() >= 2)
        {
            // Şartı kontrol etmek için dispatcher'ı çalıştır
            String result = HELPER::dispatchCommand(tokens[0], tokens[1], {});

            // Eğer cevap "true", "1", "OK" veya "Connected" ise geç
            if (result.equalsIgnoreCase(F("true")) || result == F("1") || result.equalsIgnoreCase(F("OK")) || result.equalsIgnoreCase(F("Connected")))
            {
                server->logger(F("[QUEUE] Condition met: ") + tokens[1]);
                commandQueue.pop();
            }
            else if (result.startsWith(F("Error:")))
            {
                // Eğer komut bulunamazsa veya hata varsa, kuyruğu kilitlememek için atla
                server->logger(F("[QUEUE] Condition Error: ") + result + F(" (Skipping)"));
                // commandQueue.pop();
            }
        }
        return; // Şart sağlanana kadar burada takılı kalır (bloklamaz)
    }

    // --- DURUM 3: NORMAL KOMUT ÇALIŞTIRMA (POPPING NOW) ---
    commandQueue.pop(); // Take it out of the queue

    // 1. HANDLE CONDITIONAL LOGIC (IF_SUCCESS / IF_FAIL)
    if (currentLine.startsWith(F("IF_SUCCESS "))) {
        if (!lastSuccess) {
            server->logger(F("[QUEUE] Skipping IF_SUCCESS (Last command failed)"));
            return; 
        }
        currentLine = currentLine.substring(11);
    } 
    else if (currentLine.startsWith(F("IF_FAIL "))) {
        if (lastSuccess) {
            server->logger(F("[QUEUE] Skipping IF_FAIL (Last command succeeded)"));
            return; 
        }
        currentLine = currentLine.substring(8);
    }

    // 2. HANDLE PIPING (|)
    if (currentLine.indexOf('|') != -1) {
        int pipeIdx = currentLine.indexOf('|');
        String leftSide = currentLine.substring(0, pipeIdx);
        String rightSide = currentLine.substring(pipeIdx + 1);
        
        leftSide.trim();
        rightSide.trim();

        // Execute Left Side first
        std::vector<String> leftTokens = HELPER::smartTokenize(leftSide);
        if (leftTokens.size() >= 2) {
            String mod = leftTokens[0];
            String cmd = leftTokens[1];
            std::vector<String> args;
            for (size_t i = 2; i < leftTokens.size(); i++) args.push_back(leftTokens[i]);
            
            String result = HELPER::dispatchCommand(mod, cmd, args);
            
            // Now "Pipe" that result into the right side
            // We basically treat it as: RightSideCommand + result
            currentLine = rightSide + " " + result;
        }
    }

    // 3. EXECUTE FINAL COMMAND
    std::vector<String> tokens = HELPER::smartTokenize(currentLine);
    if (tokens.size() >= 2)
    {
        String mod = tokens[0];
        String cmd = tokens[1];
        std::vector<String> args;
        for (size_t i = 2; i < tokens.size(); i++)
            args.push_back(tokens[i]);

        // Komutu çalıştır ve sonucunu al (Loglama dispatchCommand içinde yapılıyor)
        HELPER::dispatchCommand(mod, cmd, args);
    }
}

void SYSTEM::stopQueue()
{
    while (!commandQueue.empty())
    {
        commandQueue.pop();
    }
    _isWaitingMillis = false;
    server->logger(F("[QUEUE] Stopped."));
}

void SYSTEM::automate(String filename)
{
    String content = fsm->readfile(filename.c_str());
    if (content != "ERROR: File Not Found")
    {
        addToQueue(content);
        server->logger("Script yuklendi: " + filename);
    }
    else
    {
        server->logger("Hata: Script dosyasi bulunamadi: " + filename);
    }
}

void SYSTEM::startQueue()
{
    if (commandQueue.empty())
    {
        server->logger(F("[QUEUE] No commands to start."));
        return;
    }
    server->logger(F("[QUEUE] Starting execution..."));
}

SYSTEM &sys = SYSTEM::getInstance();

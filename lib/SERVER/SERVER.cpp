#include <WebSocketsServer.h>
#include "SYSTEM.h" // Diğer modüllere erişmek için
#include "SERVER.h"
#include "OLED.h" // <--- BUNU EKLE (oled->write kullanabilmek için)
#include "WIFI.h"
#include "FSM.h"
#include "HELPER.h" // String split fonksiyonu için

WebSocketsServer webSocket = WebSocketsServer(81);

void SERVER::logger(String message)
{
    // 1. Standart Serial'e yaz
    Serial.println(message);

    // 2. Bağlı olan tüm web istemcilerine gönder (HTMX için)
    // HTML'de alt satıra geçmek için \n -> <br> yapıyoruz
    String webMessage = message;
    webMessage.replace("\n", "<br>");
    
    String htmxMessage = "<div hx-swap-oob='beforeend:#ws-logs'>" + webMessage + "<br></div>";
    webSocket.broadcastTXT(htmxMessage);
}

// HTML'i PROGMEM (Flash) içinde tutarak RAM tasarrufu sağlıyoruz
const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>ESP8266 Control</title>
    <script src="https://unpkg.com/htmx.org@1.9.10"></script>
    <script src="https://unpkg.com/htmx.org@1.9.10/dist/ext/ws.js"></script>
    <style>
        body { font-family: sans-serif; text-align: center; padding: 20px; background: #121212; color: #e0e0e0; }
        #terminal-section { margin-top:20px; border:1px solid #444; padding:15px; background: #1e1e1e; border-radius: 8px; }
        textarea { width: 95%; height: 120px; background: #222; color: #fff; border: 1px solid #555; padding: 10px; border-radius: 4px; font-family: monospace; }
        button { background: #2e7d32; color: white; border: none; padding: 10px 20px; border-radius: 4px; cursor: pointer; margin-top: 10px; }
        button:hover { background: #388e3c; }
        #log-container { height: 400px; overflow-y: auto; background: #000; color: #00ff00; padding: 15px; border-radius: 8px; margin-top: 20px; text-align: left; font-family: 'Courier New', Courier, monospace; border: 1px solid #333; }
        #terminal-res { color: #81d4fa; font-style: italic; margin-top: 10px; }
    </style>
</head>
<body>
    <h1>Rinternal V2 Dashboard</h1>
    <div id="sensor-data" hx-get="/components/sensor" hx-trigger="every 5s">Loading sensors...</div>
    <hr style="border: 0; border-top: 1px solid #333;">
    
    <div id="terminal-section">
        <h3>System Terminal</h3>
        <input list="cmd-options" id="cmd-autocomplete" placeholder="Hizli komut sec..." style="width: 95%; background: #333; color: #fff; border: 1px solid #555; padding: 8px; margin-bottom: 5px; border-radius: 4px;">
        <datalist id="cmd-options"></datalist>
        <textarea name="cmd" placeholder="Komut veya Script yaz..." id="cmd-input"></textarea>
        <br>
        <button id="send-btn" hx-post="/execute" 
                hx-vals='js:{val: document.getElementById("cmd-input").value}'
                hx-trigger="click, submit-script from:body"
                hx-target="#terminal-res">
            Gonder
        </button>
        <div id="terminal-res"></div>
    </div>

    <div id="log-container" hx-ext="ws">
         <div id="ws-logs"></div>
    </div>

<script>
    // Dinamik WebSocket URL ayari
    document.querySelector('[hx-ext="ws"]').setAttribute('ws-connect', 'ws://' + window.location.hostname + ':81');

    // System Terminal Datalist Population
    async function populateCommands() {
        try {
            const response = await fetch('/execute?val=HELPER getCommandsJSON');
            const data = await response.json();
            const datalist = document.getElementById('cmd-options');
            datalist.innerHTML = '';
            const commandSet = new Set();
            data.forEach(item => {
                const cmdStr = item.module + ' ' + item.name;
                if (!commandSet.has(cmdStr)) {
                    commandSet.add(cmdStr);
                    const option = document.createElement('option');
                    option.value = cmdStr;
                    datalist.appendChild(option);
                }
            });
        } catch (error) { console.error('Error loading commands:', error); }
    }

    // Autocomplete'den textarea'ya aktarim (Sadece secim yapildiginda veya Enter'a basildiginda)
    document.getElementById('cmd-autocomplete').addEventListener('change', function(e) {
        if(e.target.value) {
            const area = document.getElementById('cmd-input');
            if(area.value.length > 0 && !area.value.endsWith('\n')) area.value += '\n';
            area.value += e.target.value;
            e.target.value = ''; // Reset autocomplete input
            area.focus();
        }
    });

    // Textarea icinde Ctrl+Enter ile gonderim
    document.getElementById('cmd-input').addEventListener('keydown', function(e) {
        if (e.key === 'Enter' && e.ctrlKey) {
            e.preventDefault();
            htmx.trigger("#cmd-input", "submit-script");
        }
    });

    // WebSocket Log Scroll
    const container = document.getElementById('log-container');
    const observer = new MutationObserver(() => {
        container.scrollTop = container.scrollHeight;
    });
    observer.observe(container, { childList: true, subtree: true });

    window.addEventListener('load', populateCommands);
</script>
</body>
</html>
)rawliteral";

void SERVER::setup()
{
    server.on("/", HTTP_GET, std::bind(&SERVER::handleRoot, this));
    // server.on("/execute", HTTP_POST, std::bind(&SERVER::handleExecute, this));
    server.on("/execute", std::bind(&SERVER::handleExecute, this));    
    server.on("/components/sensor", HTTP_GET, std::bind(&SERVER::handleSensor, this));
    server.on("/update/led", HTTP_POST, std::bind(&SERVER::handleLED, this));
    server.on("/resetwifi", HTTP_POST, std::bind(&SERVER::handleResetWiFi, this));
    server.onNotFound(std::bind(&SERVER::handleNotFound, this));

    server.begin();
    webSocket.begin();
    Serial.println("HTMX Server & WebSocket Started");
}

void SERVER::loop()
{
    server.handleClient();
    webSocket.loop();
}

void SERVER::handleRoot()
{
    server.send_P(200, "text/html", INDEX_HTML);
}

void SERVER::handleSensor()
{
    // Burada SYSTEM üzerinden sensör verisi çekebilirsin
    String html = "<div>";
    html += "<strong>Temp:</strong> 24°C | <strong>Hum:</strong> 45%";
    html += "</div>";
    server.send(200, "text/html", html);
}

void SERVER::handleLED()
{
    // Örnek: OLED'e yazdırıyoruz!
    sys.oled->write("LED Toggled!");

    // Rastgele bir durum dönelim (Sen burada gerçek pin durumuna bakarsın)
    server.send(200, "text/html", "<b style='color:green'>ON</b>");
}

void SERVER::handleResetWiFi()
{
    server.send(200, "text/plain", "WiFi Resetleniyor... Cihaz kapanacak.");
    sys.oled->write("WiFi Resetleniyor... cihaz kapanacak.");
    sys.wifi->reset(); // WiFi sınıfındaki reset metodunu çağırır
}

void SERVER::registerCommands()
{
    // 1. Parametresiz komut (args boş olacak)
    commandMap["ls"] = [this](std::vector<String> args)
    {
        server.send(200, "text/html", sys.fsm->getfilelist());
    };

    commandMap["fsm"] = [this](std::vector<String> args)
    {
        if (args.size() > 0 && args[0] == "clear")
        {
            sys.fsm->deletefile("/config.txt");
            server.send(200, "text/html", "FSM Config Silindi");
            return;
        }
        else if (args.size() > 0 && args[0] == "reset")
        {
            sys.fsm->writefile("/config.txt", "default_config");
            server.send(200, "text/html", "FSM Config Sifirlandi");
            return;
        }
        else if (args.size() > 0 && args[0] == "read")
        {
            String content = sys.fsm->readfile("/config.txt");
            server.send(200, "text/html", "FSM Config Icerigi: " + content);
            return;
        }
        String status = "FSM Durumu: " + String(sys.fsm->fileexists("/config.txt") ? "Config Var" : "Config Yok");
        server.send(200, "text/html", status);
    };

    commandMap["clear"] = [this](std::vector<String> args)
    {
        sys.oled->clear();
        server.send(200, "text/html", "OLED Temizlendi");
    };

    commandMap["help"] = [this](std::vector<String> args)
    {
        String helpText = "Komutlar: ls <br> clear <br> print [mesaj] <br> wifi [option] [ssid] [pass]";
        server.send(200, "text/html", helpText);
    };

    // 2. Tek parametreli komut: "print merhaba"
    commandMap["print"] = [this](std::vector<String> args)
    {
        if (args.size() > 0)
        {
            String msg = "";
            for (const auto &s : args)
                msg += s + " "; // Tüm parçaları birleştir
            sys.oled->write(msg.c_str());
            server.send(200, "text/html", "OLED: " + msg);
        }
    };

    // 3. Çok parametreli komut: "wifi set ssid password"
    commandMap["wifi"] = [this](std::vector<String> args)
    {
        if (args.size() >= 2 && args[0] == "set")
        {
            String ssid = args[1];
            String pass = args[2];
            server.send(200, "text/html", "WiFi Ayarlandi: " + ssid);
            sys.wifi->connect(ssid, pass);
        }
        else if (args.size() >= 1 && args[0] == "reset")
        {
            sys.wifi->reset();
            server.send(200, "text/html", "WiFi Ayarları Sıfırlandı.<br> Cihazı yeniden başlatın.");
        }
        else if (args.size() >= 1 && args[0] == "restart")
        {
            sys.wifi->restart();
            server.send(200, "text/html", "Cihaz yeniden başlatılıyor.");
        }
        else if (args.size() >= 1 && args[0] == "status")
        {
            String status = "MAC: " + sys.wifi->getMAC() + "<br>, IP: " + sys.wifi->getIP() + "<br>, SSID: " + sys.wifi->getSSID() + "<br>, Password: " + sys.wifi->getPassword();
            server.send(200, "text/html", status);
        }
        else if (args.size() >= 1 && args[0] == "connect")
        {
            if (args.size() >= 3)
            {
                String ssid = args[1];
                String pass = args[2];
                String result = sys.wifi->connect(ssid, pass);
                server.send(200, "text/html", result);
            }
            else
            {
                server.send(200, "text/html", "Kullanim: wifi connect [ssid] [pass]");
            }
        }
        else
        {
            server.send(200, "text/html", "Kullanim: wifi set [ssid] [pass] <br> wifi reset <br> wifi restart <br> wifi status <br> wifi connect [ssid] [pass]");
        }
    };
}

void SERVER::commandParseAndExecute(String rawInput)
{
    rawInput.trim();
    std::vector<String> tokens = HELPER::smartTokenize(rawInput);

    if (tokens.empty())
        return;

    String cmd = tokens[0];       // İlk kelime komut
    tokens.erase(tokens.begin()); // Komutu listeden at, geriye sadece argümanlar kalsın

    auto it = commandMap.find(cmd);
    if (it != commandMap.end())
    {
        it->second(tokens); // Argüman vektörünü fonksiyona yolla
    }
    else
    {
        sys.oled->write(rawInput.c_str());
        server.send(200, "text/html", "Bilinmeyen komut, OLED'e basildi.");
    }
}

void SERVER::handleExecute() {
    String input = "";
    
    // Check both POST body and GET query parameters
    if (server.hasArg("val")) {
        input = server.arg("val");
    }

    if (input != "") {
        input.trim();
        std::vector<String> tokens = HELPER::smartTokenize(input);
        
        if(tokens.size() >= 2) {
            String module = tokens[0];
            String command = tokens[1];
            
            std::vector<String> args;
            for(size_t i = 2; i < tokens.size(); i++) {
                args.push_back(tokens[i]);
            }

            String response = HELPER::dispatchCommand(module, command, args);
            
            if (module.equalsIgnoreCase("HELPER") && command.equalsIgnoreCase("getCommandsJSON")) {
                server.send(200, "application/json", response);
            } else {
                // CRITICAL: If the response contains HTML (like getHelp), 
                // send it with "text/html" so the browser renders it.
                server.send(200, "text/html", response);
            }
            
            logger("Cmd: " + input);
        } else {
            server.send(400, "text/plain", "Invalid Command Format");
        }
    } else {
        server.send(400, "text/plain", "No 'val' argument found");
    }
}

// void SERVER::handleExecute()
// {
//     if (server.hasArg("val"))
//     {
//         String input = server.arg("val");
//         std::vector<String> tokens = HELPER::splitString(input, ' ');

//         if (tokens.size() >= 2)
//         {
//             String module = tokens[0];
//             String command = tokens[1];

//             // Extract remaining arguments efficiently
//             std::vector<String> args;
//             for (size_t i = 2; i < tokens.size(); i++)
//             {
//                 args.push_back(tokens[i]);
//             }

//             String response = HELPER::dispatchCommand(module, command, args);
//             logger("Cmd: " + input + " | Res: " + response);

//             // Send a response back to the HTMX target
//             server.send(200, "text/html", "Success: " + response);
//         }
//         else
//         {
//             server.send(200, "text/html", "Hata: Eksik parametre");
//         }
//     }
// }

// void SERVER::handleExecute()
// {
//     if (server.hasArg("val"))
//     {
//         auto Response = HELPER::dispatchCommand(HELPER::splitString(server.arg("val"), ' ')[0], // Modül adı (örneğin "OLED")
//                     HELPER::splitString(server.arg("val"), ' ')[1], // Komut adı (örneğin "write")
//                     std::vector<String>(HELPER::splitString(server.arg("val"), ' ').begin() + 2, HELPER::splitString(server.arg("val"), ' ').end())); // Geri kalan argümanlar
//         // Alternatif olarak doğrudan tüm komutu da gönderebilirsin:
//         logger("Komut alindi: " + server.arg("val") + " | Response: " + Response);
//         // commandParseAndExecute(server.arg("val"));
//     }
// }

void SERVER::handleNotFound()
{
    server.send(404, "text/plain", "Sayfa Bulunamadi");
}
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
    webMessage.replace(F("\n"), F("<br>"));
    
    String htmxMessage = F("<div hx-swap-oob='beforeend:#ws-logs'>") + webMessage + F("<br></div>");
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
    server.send(200, F("text/plain"), F("WiFi Resetleniyor... Cihaz kapanacak."));
    sys.oled->write(F("WiFi Resetleniyor... cihaz kapanacak."));
    sys.wifi->reset(); // WiFi sınıfındaki reset metodunu çağırır
}

void SERVER::handleExecute() {
    String input = F("");
    
    if (server.hasArg(F("val"))) {
        input = server.arg(F("val"));
    }

    if (input == F("")) {
        server.send(400, F("text/plain"), F("No 'val' argument found"));
        return;
    }

    input.trim();
    
    // If the input contains newlines AND is not a single `writefile` command,
    // treat it as a script to be queued. This preserves existing behavior for multi-line scripts.
    bool isLikelyWriteFile = input.substring(0, 14).equalsIgnoreCase(F("FSM WRITEFILE "));
    if (input.indexOf('\n') != -1 && !isLikelyWriteFile) {
        sys.addToQueue(input);
        server.send(200, F("text/html"), F("Script added to queue..."));
        logger(F("Script Queued"));
        return;
    }

    // Process the input, which may contain one or more commands.
    String remainingInput = input;
    String fullResponse = "";

    while (remainingInput.length() > 0) {
        remainingInput.trim();
        if (remainingInput.length() == 0) break;

        String currentCommand;
        int endOfCommandIdx = -1;

        // Special case: FSM writefile <filename> "content" defines its own end.
        if (remainingInput.substring(0, 14).equalsIgnoreCase(F("FSM WRITEFILE "))) {
            // Find the start of the quoted content
            int firstSpace = remainingInput.indexOf(' ');
            int secondSpace = (firstSpace != -1) ? remainingInput.indexOf(' ', firstSpace + 1) : -1;
            int quoteStart = (secondSpace != -1) ? remainingInput.indexOf('"', secondSpace + 1) : -1;

            // Check if we have the pattern: FSM writefile filename "
            if (quoteStart > secondSpace) {
                // Find the matching closing quote. This simple search doesn't handle escaped quotes.
                int quoteEnd = remainingInput.indexOf('"', quoteStart + 1);
                if (quoteEnd != -1) {
                    // We found a complete writefile command. Its end is the closing quote.
                    endOfCommandIdx = quoteEnd;
                }
            }
        }

        // If it's not a special writefile command, or if the writefile command was malformed,
        // we treat commands as being separated by newlines.
        if (endOfCommandIdx == -1) {
            int newlineIdx = remainingInput.indexOf('\n');
            if (newlineIdx != -1) {
                endOfCommandIdx = newlineIdx - 1; // The command ends before the newline
            } else {
                // No more newlines, the rest of the string is the command
                endOfCommandIdx = remainingInput.length() - 1;
            }
        }
        
        currentCommand = remainingInput.substring(0, endOfCommandIdx + 1);
        remainingInput = remainingInput.substring(endOfCommandIdx + 1);

        currentCommand.trim();
        if (currentCommand.length() == 0) continue;

        // --- Execute currentCommand ---
        if (currentCommand.startsWith(F("WAIT ")) || currentCommand.startsWith(F("WAIT_UNTIL "))) {
            sys.addToQueue(currentCommand);
            fullResponse += "Command Queued: " + currentCommand + "<br>";
            continue;
        }

        std::vector<String> tokens;
        // Manual tokenization for the special writefile case to handle the quoted content.
        if (currentCommand.substring(0, 14).equalsIgnoreCase(F("FSM WRITEFILE "))) {
            int firstSpace = currentCommand.indexOf(' ');
            int secondSpace = currentCommand.indexOf(' ', firstSpace + 1);
            int quoteStart = currentCommand.indexOf('"', secondSpace + 1);
            // Check for the full pattern including the closing quote
            if (quoteStart > secondSpace && currentCommand.endsWith("\"")) {
                tokens.push_back(F("FSM"));
                tokens.push_back(F("writefile"));
                String filename = currentCommand.substring(secondSpace + 1, quoteStart);
                filename.trim();
                tokens.push_back(filename);
                tokens.push_back(currentCommand.substring(quoteStart)); // The rest is the content, with quotes
            } else {
                // If pattern is broken, fall back to standard tokenizing
                tokens = HELPER::smartTokenize(currentCommand);
            }
        } else {
            tokens = HELPER::smartTokenize(currentCommand);
        }

        if (tokens.size() >= 2) {
            String module = tokens[0];
            String command = tokens[1];
            std::vector<String> args;
            for (size_t i = 2; i < tokens.size(); i++) args.push_back(tokens[i]);
            
            String response = HELPER::dispatchCommand(module, command, args);
            
            if (module.equalsIgnoreCase(F("HELPER")) && command.equalsIgnoreCase(F("getCommandsJSON"))) {
                server.send(200, F("application/json"), response);
                return; // This command should be sent alone.
            }
            fullResponse += response + "<br>";
        } else {
            fullResponse += "Invalid Command Format: " + currentCommand + "<br>";
        }
    }

    server.send(200, F("text/html"), fullResponse);
}

void SERVER::handleNotFound()
{
    server.send(404, F("text/plain"), F("Sayfa Bulunamadi"));
}
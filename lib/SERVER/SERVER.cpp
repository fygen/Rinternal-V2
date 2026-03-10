#include "SYSTEM.h" // Diğer modüllere erişmek için
#include "SERVER.h"
#include "OLED.h" // <--- BUNU EKLE (oled->write kullanabilmek için)
#include "WIFI.h"
#include "FSM.h"
#include <WebSocketsServer.h>

WebSocketsServer webSocket = WebSocketsServer(81);

void logger(String message) {
    // 1. Standart Serial'e yaz
    Serial.println(message);
    
    // 2. Bağlı olan tüm web istemcilerine gönder (HTMX için)
    // Mesajı bir HTML parçası olarak gönderiyoruz ki HTMX doğrudan ekrana basabilsin
    String htmxMessage = "<div hx-swap-oob='beforeend:#log-container'>" + message + "<br></div>";
    webSocket.broadcastTXT(htmxMessage);
}

// HTML'i PROGMEM (Flash) içinde tutarak RAM tasarrufu sağlıyoruz
const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>ESP8266 Control</title>
    <script src="https://unpkg.com/htmx.org@1.9.10"></script>
    <style>body { font-family: sans-serif; text-align: center; padding: 20px; }</style>
</head>
<body>
    <h1>Smart Home Dashboard</h1>
    <div id="sensor-data" hx-get="/components/sensor" hx-trigger="every 2s">Loading...</div>
    <hr>
    <div id="led-control">
        <button hx-post="/update/led" hx-target="#led-status">Toggle Light</button>
        Status: <span id="led-status">OFF</span>
    </div>
    <hr>
    <button hx-post="/resetwifi" hx-confirm="Emin misiniz?">WiFi Reset</button>
    <div id="terminal-section" style="margin-top:20px; border:1px solid #ccc; padding:10px;">
    <h3>System Terminal</h3>
    <input type="text" name="cmd" placeholder="Mesaj yaz..." id="cmd-input">
    <button hx-post="/execute" 
            hx-vals='js:{val: document.getElementById("cmd-input").value}'
            hx-target="#terminal-res">
        Gönder
    </button>
    <div id="terminal-res" style="color: blue; font-style: italic;"></div>
</div>
<script src="https://unpkg.com/htmx.org@1.9.10/dist/ext/ws.js"></script>
<div id="log-container" 
     style="height: 300px; overflow-y: auto; background: black; color: lime;"
     hx-ext="ws" ws-connect="/ws"
     onlineadded="this.scrollTop = this.scrollHeight">
    </div>

<script>
    // MutationObserver ile yeni log geldiğinde kaydırma yapabiliriz
    const container = document.getElementById('log-container');
    const observer = new MutationObserver(() => {
        container.scrollTop = container.scrollHeight;
    });
    observer.observe(container, { childList: true });
</script>
</body>
</html>
)rawliteral";

void SERVER::setup()
{
    server.on("/", HTTP_GET, std::bind(&SERVER::handleRoot, this));
    server.on("/execute", HTTP_POST, std::bind(&SERVER::handleExecute, this));
    server.on("/components/sensor", HTTP_GET, std::bind(&SERVER::handleSensor, this));
    server.on("/update/led", HTTP_POST, std::bind(&SERVER::handleLED, this));
    server.on("/resetwifi", HTTP_POST, std::bind(&SERVER::handleResetWiFi, this));
    server.onNotFound(std::bind(&SERVER::handleNotFound, this));

    server.begin();
    Serial.println("HTMX Server Started");
}

void SERVER::loop()
{
    server.handleClient();
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

// String'i parçalara ayıran yardımcı fonksiyon
std::vector<String> SERVER::splitString(String str, char delimiter)
{
    std::vector<String> internal;
    int start = 0;
    int end = str.indexOf(delimiter);
    while (end != -1)
    {
        internal.push_back(str.substring(start, end));
        start = end + 1;
        end = str.indexOf(delimiter, start);
    }
    internal.push_back(str.substring(start));
    return internal;
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
        if(args.size() > 0 && args[0] == "clear")
        {
            sys.fsm->deletefile("/config.txt");
            server.send(200, "text/html", "FSM Config Silindi");
            return;
        }
        else if(args.size() > 0 && args[0] == "reset")
        {
            sys.fsm->writefile("/config.txt", "default_config");
            server.send(200, "text/html", "FSM Config Sifirlandi");
            return;
        }
        else if(args.size() > 0 && args[0] == "read")
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
        else if(args.size() >= 1 && args[0] == "reset")
        {
            sys.wifi->reset();
            server.send(200, "text/html", "WiFi Ayarları Sıfırlandı.<br> Cihazı yeniden başlatın.");
        }else if(args.size() >= 1 && args[0] == "restart")
        {
            sys.wifi->restart();
            server.send(200, "text/html", "Cihaz yeniden başlatılıyor.");
        }
        else if(args.size() >= 1 && args[0] == "status")
        {
            String status = "MAC: " + sys.wifi->getMAC() + "<br>, IP: " + sys.wifi->getIP() + "<br>, SSID: " + sys.wifi->getSSID() + "<br>, Password: " + sys.wifi->getPassword();
            server.send(200, "text/html", status);
        }   
        else if(args.size() >= 1 && args[0] == "connect")
        {
            if(args.size() >= 3)
            {
                String ssid = args[1];
                String pass = args[2];
                String result = sys.wifi->connect(ssid, pass);
                server.send(200, "text/html", result);
            } else {
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
    std::vector<String> tokens = splitString(rawInput, ' ');

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

void SERVER::handleExecute()
{
    if (server.hasArg("val"))
    {
        commandParseAndExecute(server.arg("val"));
    }
}

void SERVER::handleNotFound()
{
    server.send(404, "text/plain", "Sayfa Bulunamadi");
}
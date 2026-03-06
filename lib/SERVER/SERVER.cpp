#include "SERVER.h"
#include "SYSTEM.h" // Diğer modüllere erişmek için

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
    SYSTEM::getInstance().oled.write("LED Toggled!");

    // Rastgele bir durum dönelim (Sen burada gerçek pin durumuna bakarsın)
    server.send(200, "text/html", "<b style='color:green'>ON</b>");
}

void SERVER::handleResetWiFi()
{
    server.send(200, "text/plain", "WiFi Resetleniyor... Cihaz kapanacak.");
    delay(1000);
    SYSTEM::getInstance().wifi.reset(); // WiFi sınıfındaki reset metodunu çağırır
}

void SERVER::handleExecute() {
    // Input'tan gelen "val" parametresini alıyoruz
    if (server.hasArg("val")) {
        String command = server.arg("val");
        
        // Komut boş değilse işle
        if (command.length() > 0) {
            // OLED'e erişip ekrana yazdırıyoruz!
            // SYSTEM Singleton yapısı sayesinde her yerden erişebilirsin
            SYSTEM::getInstance().oled.write(command.c_str());
            
            // Kullanıcıya geri bildirim gönder (HTMX target #terminal-res içine basar)
            server.send(200, "text/html", "Komut Gönderildi: " + command);
        } else {
            server.send(200, "text/html", "Hata: Boş komut!");
        }
    } else {
        server.send(400, "text/plain", "Parametre hatasi");
    }
}

void SERVER::handleNotFound()
{
    server.send(404, "text/plain", "Sayfa Bulunamadi");
}
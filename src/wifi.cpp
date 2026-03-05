#include "wifi.h"
#include <string.h>
#include <WiFiManager.h>


String INDEX_HTML = R"rawliteral( <!DOCTYPE html>
<html>
<head>
    <title>ESP8266 Control</title>
    <script src="https://unpkg.com/htmx.org@1.9.10"></script>
</head>
<body>
    <h1>Smart Home Dashboard</h1>

    <div id="sensor-data" hx-get="/components/sensor" hx-trigger="every 2s">
        Loading sensors...
    </div>

    <div id="led-control">
        <button hx-post="/update/led" hx-target="#led-status">
            Toggle Light
        </button>
        <span id="led-status">Unknown</span>
    </div>

    <div id="Reset-control">
        <button hx-post="/resetwifi" hx-target="#reset-status">
            Reset WiFi
        </button>
        <span id="reset-status">Unknown</span>
    </div>
</body>
</html>)rawliteral";

ESP8266WebServer server(80); // ESP8266WebServer nesnesi oluşturuyoruz.

/*Put your SSID & Password*/
// const char *ssid = "FiberHGW_HUNFQ5";  // Wifi adınız
// const char *password = "KXtXqRgpg3mV"; // wifi şifreniz

// put any globals or helper routines here, in an anonymous namespace
// so that they don't collide with other translation units.

// // Handler for the wifi setup
// void handle_ResetWifi() {
//     wp.resetSettings();
//     server.send(200, "text/html", INDEX_HTML);
// }


// Handler for /components/sensor
void handle_SensorComponent() {
    // We only send the inner content
    String html = "<div>";
    html += "<strong>Temperature:</strong> " + String(0) + "°C<br>";
    html += "<strong>Humidity:</strong> " + String(0) + "%";
    html += "</div>";
    
    server.send(200, "text/html", html);
}

// Handler for /update/led
void handle_LEDUpdate() {
    // Toggle LED
    // digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    
    // Return the new status fragment
    // String status = digitalRead(LED_PIN) ? "ON" : "OFF";
    // String color = digitalRead(LED_PIN) ? "green" : "red";
    String color = "green";
    String status = "ON";
    
    String html = "<b style='color:" + color + "'>" + status + "</b>";
    server.send(200, "text/html", html);
}

void wifi::handle_NotFound()
{
    server.send(404, "text/plain", "Not found");
}

String wifi::handle_Receive(){
    String message = "Message Received: ";
    message += server.arg   ("message");
    return message;
}

String wifi::setup()
{
    Serial.begin(115200);
    WiFiManager wm;
    delay(100);

    bool res = wm.autoConnect("AutoConnectAP","password"); 

    if(!res) {
        Serial.println("Bağlantı başarısız veya zaman aşımı.");
        // ESP.restart(); // İstersen burada reset atabilirsin
    } else {
        Serial.println("WiFi Bağlandı..!");
        Serial.print("IP Adresiniz: ");
        Serial.println(WiFi.localIP());
    }

    // Main Page
    server.on("/", HTTP_GET, []() {
        server.send(200, "text/html", INDEX_HTML); // INDEX_HTML is your skeleton
    });

    // CRUD - READ (The Component)
    server.on("/components/sensor", HTTP_GET, handle_SensorComponent);

    // CRUD - UPDATE
    server.on("/update/led", HTTP_POST, handle_LEDUpdate);

// Reset WiFi Handler'ını güncellemen gerekecek:
    server.on("/resetwifi", HTTP_POST, [](){
        WiFiManager wm;
        wm.resetSettings(); // Hafızayı siler
        server.send(200, "text/html", "WiFi Ayarları Sıfırlandı. Cihazı yeniden başlatın.");
        delay(1000);
        ESP.restart();
    });

    server.begin();

    Serial.println("HTTP Sunucusu Başladı");
    return WiFi.localIP().toString();
}

void wifi::loop()
{

    server.handleClient();
}

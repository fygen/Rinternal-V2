#pragma once
#ifndef WIFI_H
#define WIFI_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// A small namespace encapsulating the networking/webserver
// logic.  Only the two top-level entrypoints (setup and loop)
// are exposed to the rest of the program; all of the globals
// and helper routines live in the .cpp file.

namespace wifi {
    /**
     * Initialize the ESP8266 Wi‑Fi connection, start the HTTP
     * server and configure all route handlers.  Call this in
     * Arduino `setup()` from your main program.
     */
    String setup();
    String SendHTML(float Temperaturestat, float Humiditystat, uint8_t led1stat, uint8_t led2stat);
    String handle_Receive();
    void handle_led2off();
    void handle_led2on();
    void handle_led1off();
    void handle_led1on();
    void handle_OnConnect();
    void handle_NotFound();
    /**
     * Perform any per‑loop work required by the Wi‑Fi/webserver
     * logic.  The implementation simply forwards to
     * `server.handleClient()` and updates the LED outputs, but
     * the caller need only invoke this once every iteration of
     * `loop()`.
     */
    void loop();
}


#endif // WIFI_H
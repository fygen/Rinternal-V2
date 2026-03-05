#include <Arduino.h>
#include <Ticker.h>
#include "oledControlFromU8glib2.hpp"
#include "wifi.h"

Ticker oledTicker;
int c = 0;
String ipaddr;
bool updateReady = false;

// This function is called by the timer interrupt
void setUpdateFlag() {
  updateReady = true;
}


void setup() {
  u8g2.begin();
  ipaddr = wifi::setup();

  // Call 'setUpdateFlag' every 1.0 seconds
  oledTicker.attach(1.0, setUpdateFlag);
}

void loop() {
  wifi::loop();

  if(updateReady) {
    updateReady = false; // Reset the flag
    c++;
    handle_oled(c);
    write_to_oled(ipaddr.c_str());
  }
  // delay(1000);
}

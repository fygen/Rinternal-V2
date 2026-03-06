#ifndef SERVER_MANAGER_H
#define SERVER_MANAGER_H
#include <ESP8266WebServer.h>

class SERVER
{
    private:
        ESP8266WebServer* server(int port); 
    public:
        void setup();
        void loop();
        void handle_NotFound();
        String handle_Receive();

        void handle_SensorComponent();
        void handle_LEDUpdate();
};


#endif
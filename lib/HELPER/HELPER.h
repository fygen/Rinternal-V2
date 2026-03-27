#ifndef HELPER_H
#define HELPER_H

#include <vector>
#include <Arduino.h>

class HELPER {
public:
    static std::vector<String> splitString(String str, char delimiter);
    static String dispatchCommand(String mod, String cmd, std::vector<String> args);
    static String wtf();
    bool copyto(char *response, const char* format, ...);
    static String getHelp();
    static String getCommandsJSON();
private:
    char _response[255];

};

#endif
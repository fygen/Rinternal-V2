#ifndef HELPER_H
#define HELPER_H

#include <vector>
#include <Arduino.h>

class HELPER {
public:
    static std::vector<String> splitString(String str, char delimiter);
    static std::vector<String> smartTokenize(String input);
    static String dispatchCommand(String mod, String cmd, std::vector<String> args);
    static String wtf();
    static String getFreeHeap();
    bool copyto(char *response, size_t size, const char* format, ...);
    static String getHelp();
    static String getCommandsJSON();
private:
    char _response[255];

};

#endif
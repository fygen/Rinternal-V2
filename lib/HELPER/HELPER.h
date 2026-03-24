#ifndef HELPER_H
#define HELPER_H

#include <vector>
#include <Arduino.h>

class HELPER {
public:
    static std::vector<String> splitString(String str, char delimiter);
    static String dispatchCommand(String mod, String cmd, std::vector<String> args);
    bool copyto(char *response, const char* format, ...);
    static String getHelp(); // Add this line
private:

};

#endif
#include <Arduino.h>
#include <LittleFS.h>
// #include <ArduinoJson.h>

class FSM
{
public:
    void setup();
    String readFile(const char *path);
    bool writeFile(const char *path, const String &content);
    bool deleteFile(const char *path);
    bool fileExists(const char *path);
    String getFileList();          // Function to get the list of files (for internal use)

private:
    String *files[10] = {nullptr}; // Dynamic array to hold file names
    size_t fileCount = 0;          // Number of files currently stored
};
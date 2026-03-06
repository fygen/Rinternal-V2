#include "FSM.h"

void FSM::setup()
{
    if (!LittleFS.begin())
    {
        Serial.println("Failed to mount file system");
        return;
    }
    Serial.println("File system mounted successfully");
}

String FSM::readFile(const char *path)
{
    if (!LittleFS.exists(path))
    {
        Serial.println("File not found: " + String(path));
        return "";
    }
    File file = LittleFS.open(path, "r");
    if (!file)
    {
        Serial.println("Failed to open file: " + String(path));
        return "";
    }
    String content = file.readString();
    file.close();
    return content;
}

bool FSM::writeFile(const char *path, const String &content)
{
    File file = LittleFS.open(path, "w");
    if (!file)
    {
        Serial.println("Failed to open file for writing: " + String(path));
        return false;
    }
    file.print(content); 
    file.close();
    *files[fileCount++] =  String(path); // Add to file list
    return true;
}

bool FSM::deleteFile(const char *path)
{
    if (LittleFS.exists(path))
    {
        return LittleFS.remove(path);
    }
    return false; // File doesn't exist
}

bool FSM::fileExists(const char *path)
{
    return LittleFS.exists(path);
}

String FSM::getFileList()
{
    String list = "";
    for (size_t i = 0; i < fileCount; i++)
    {
        list += files[i] + '\n';
    }
    return list;
}
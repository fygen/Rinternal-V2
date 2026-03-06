#ifndef FSM_H
#define FSM_H

#include <Arduino.h>
#include <LittleFS.h>
// #include <ArduinoJson.h>

class FSM
{
public:
    FSM() {} // FS'i başlatır, mount edilemezse formatlar
    bool setup(); 
    String readFile(const char *path); // Dosyayı oku
    bool writeFile(const char *path, const String &content); // Dosyaya yaz (üzerine yazar)
    bool deleteFile(const char *path);
    String getFileList(); // Dosya listesini ANLIK olarak oluştur (RAM tasarrufu)
    bool fileExists(const char *path);
};

#endif
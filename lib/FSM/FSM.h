#ifndef FSM_H
#define FSM_H

#include <Arduino.h>
#include <LittleFS.h>
// #include <ArduinoJson.h>

class FSM
{
public:
    FSM(); // FS'i başlatır, mount edilemezse formatlar
    bool setup();
    // @shell: readfile (dosyayolu)
    String readfile(const char *path);                       // Dosyayı oku
    bool writefile(const char *path, const String &content); // Dosyaya yaz (üzerine yazar)
    bool deletefile(const char *path);
    String getfilelist(); // Dosya listesini ANLIK olarak oluştur (RAM tasarrufu)
    bool fileexists(const char *path);
};

#endif
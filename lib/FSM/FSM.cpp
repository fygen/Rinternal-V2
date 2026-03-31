#include "FSM.h"

FSM::FSM() {}

// FS'i başlatır, mount edilemezse formatlar
bool FSM::setup()
{
    if (!LittleFS.begin())
    {
        Serial.println("LittleFS Mount Failed");
        return false;
    }
    Serial.println("LittleFS Success");
    return true;
}

// Dosyayı oku
// @shell: readfile (dosyayolu)
String FSM::readfile(const char *path)
{
    String safePath = path;
    if (!safePath.startsWith(F("/"))) safePath = F("/") + safePath;
    
    File file = LittleFS.open(safePath, "r");
    if (!file || file.isDirectory())
        return F("ERROR: File Not Found");
    String content = file.readString();
    file.close();
    return content;
}

// Dosyaya yaz (üzerine yazar)
bool FSM::writefile(const char *path, const String &content)
{
    String safePath = path;
    if (!safePath.startsWith("/")) safePath = "/" + safePath;

    File file = LittleFS.open(safePath, "w");
    if (!file)
        return false;
    bool success = file.print(content);
    file.close();
    return success;
}

// Dosyayı sil
bool FSM::deletefile(const char *path)
{
    String safePath = path;
    if (!safePath.startsWith("/")) safePath = "/" + safePath;
    return LittleFS.remove(safePath);
}

// Dosya listesini ANLIK olarak oluştur (RAM tasarrufu)
String FSM::getfilelist()
{
    String list = F("Files:\n");
    Dir dir = LittleFS.openDir(F("/")); // ESP8266'da openDir kullanılır
    while (dir.next())
    {
        yield();
        list += dir.fileName() + F(" (") + String(dir.fileSize()) + F(" bytes)\n");
    }
    return list;
}

bool FSM::fileexists(const char *path)
{
    String safePath = path;
    if (!safePath.startsWith("/")) safePath = "/" + safePath;
    return LittleFS.exists(safePath);
}
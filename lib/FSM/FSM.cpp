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
    File file = LittleFS.open(path, "r");
    if (!file || file.isDirectory())
        return "";
    String content = file.readString();
    file.close();
    return content;
}

// Dosyaya yaz (üzerine yazar)
bool FSM::writefile(const char *path, const String &content)
{
    File file = LittleFS.open(path, "w");
    if (!file)
        return false;
    bool success = file.print(content);
    file.close();
    return success;
}

// Dosyayı sil
bool FSM::deletefile(const char *path)
{
    return LittleFS.remove(path);
}

// Dosya listesini ANLIK olarak oluştur (RAM tasarrufu)
String FSM::getfilelist()
{
    String list = "Files:\n";
    Dir dir = LittleFS.openDir("/"); // ESP8266'da openDir kullanılır
    while (dir.next())
    {
        list += dir.fileName() + " (" + String(dir.fileSize()) + " bytes)\n";
    }
    return list;
}

bool FSM::fileexists(const char *path)
{
    return LittleFS.exists(path);
}
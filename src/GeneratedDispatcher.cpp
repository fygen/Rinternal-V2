#include <Arduino.h>
#include "SYSTEM.h"
#include "WIFI.h"
#include "OLED.h"
#include "SERVER.h"
#include "FSM.h"

String dispatchCommand(String mod, String cmd, std::vector<String> args) {
    if (mod.equalsIgnoreCase("OLED") && cmd.equalsIgnoreCase("setup")) {
        if (args.size() < 0) return "Hata: En az 0 parametre gerekli!";
        sys.oled->setup();
        return "OK";
    }
    if (mod.equalsIgnoreCase("OLED") && cmd.equalsIgnoreCase("write")) {
        if (args.size() < 1) return "Hata: En az 1 parametre gerekli!";
        return String(sys.oled->write(args[0]));
    }
    if (mod.equalsIgnoreCase("OLED") && cmd.equalsIgnoreCase("write")) {
        if (args.size() < 1) return "Hata: En az 1 parametre gerekli!";
        return String(sys.oled->write(args[0].c_str()));
    }
    if (mod.equalsIgnoreCase("OLED") && cmd.equalsIgnoreCase("clear")) {
        if (args.size() < 0) return "Hata: En az 0 parametre gerekli!";
        sys.oled->clear();
        return "OK";
    }
    if (mod.equalsIgnoreCase("OLED") && cmd.equalsIgnoreCase("setBrightness")) {
        if (args.size() < 1) return "Hata: En az 1 parametre gerekli!";
        return String(sys.oled->setBrightness(args[0].toInt()));
    }
    if (mod.equalsIgnoreCase("OLED") && cmd.equalsIgnoreCase("getOledStatus")) {
        if (args.size() < 0) return "Hata: En az 0 parametre gerekli!";
        return String(sys.oled->getOledStatus());
    }
    if (mod.equalsIgnoreCase("OLED") && cmd.equalsIgnoreCase("setCursor")) {
        if (args.size() < 2) return "Hata: En az 2 parametre gerekli!";
        return String(sys.oled->setCursor(args[0].toInt(), args[1].toInt()));
    }
    if (mod.equalsIgnoreCase("OLED") && cmd.equalsIgnoreCase("setLineHeight")) {
        if (args.size() < 1) return "Hata: En az 1 parametre gerekli!";
        return String(sys.oled->setLineHeight(args[0].toInt()));
    }
    if (mod.equalsIgnoreCase("OLED") && cmd.equalsIgnoreCase("setScreenSize")) {
        if (args.size() < 2) return "Hata: En az 2 parametre gerekli!";
        return String(sys.oled->setScreenSize(args[0].toInt(), args[1].toInt()));
    }
    if (mod.equalsIgnoreCase("SERVER") && cmd.equalsIgnoreCase("setup")) {
        if (args.size() < 0) return "Hata: En az 0 parametre gerekli!";
        sys.server->setup();
        return "OK";
    }
    if (mod.equalsIgnoreCase("SERVER") && cmd.equalsIgnoreCase("loop")) {
        if (args.size() < 0) return "Hata: En az 0 parametre gerekli!";
        sys.server->loop();
        return "OK";
    }
    if (mod.equalsIgnoreCase("SERVER") && cmd.equalsIgnoreCase("handleExecute")) {
        if (args.size() < 0) return "Hata: En az 0 parametre gerekli!";
        sys.server->handleExecute();
        return "OK";
    }
    if (mod.equalsIgnoreCase("SERVER") && cmd.equalsIgnoreCase("commandParseAndExecute")) {
        if (args.size() < 1) return "Hata: En az 1 parametre gerekli!";
        sys.server->commandParseAndExecute(args[0]);
        return "OK";
    }
    if (mod.equalsIgnoreCase("WIFI") && cmd.equalsIgnoreCase("setup")) {
        if (args.size() < 0) return "Hata: En az 0 parametre gerekli!";
        return String(sys.wifi->setup());
    }
    if (mod.equalsIgnoreCase("WIFI") && cmd.equalsIgnoreCase("reset")) {
        if (args.size() < 0) return "Hata: En az 0 parametre gerekli!";
        return String(sys.wifi->reset());
    }
    if (mod.equalsIgnoreCase("WIFI") && cmd.equalsIgnoreCase("connect")) {
        if (args.size() < 2) return "Hata: En az 2 parametre gerekli!";
        return String(sys.wifi->connect(args[0], args[1]));
    }
    if (mod.equalsIgnoreCase("WIFI") && cmd.equalsIgnoreCase("restart")) {
        if (args.size() < 0) return "Hata: En az 0 parametre gerekli!";
        return String(sys.wifi->restart());
    }
    if (mod.equalsIgnoreCase("WIFI") && cmd.equalsIgnoreCase("getIP")) {
        if (args.size() < 0) return "Hata: En az 0 parametre gerekli!";
        return String(sys.wifi->getIP());
    }
    if (mod.equalsIgnoreCase("WIFI") && cmd.equalsIgnoreCase("getMAC")) {
        if (args.size() < 0) return "Hata: En az 0 parametre gerekli!";
        return String(sys.wifi->getMAC());
    }
    if (mod.equalsIgnoreCase("WIFI") && cmd.equalsIgnoreCase("getSSID")) {
        if (args.size() < 0) return "Hata: En az 0 parametre gerekli!";
        return String(sys.wifi->getSSID());
    }
    if (mod.equalsIgnoreCase("WIFI") && cmd.equalsIgnoreCase("getPassword")) {
        if (args.size() < 0) return "Hata: En az 0 parametre gerekli!";
        return String(sys.wifi->getPassword());
    }
    if (mod.equalsIgnoreCase("FSM") && cmd.equalsIgnoreCase("setup")) {
        if (args.size() < 0) return "Hata: En az 0 parametre gerekli!";
        return sys.fsm->setup() ? "true" : "false";
    }
    if (mod.equalsIgnoreCase("FSM") && cmd.equalsIgnoreCase("readfile")) {
        if (args.size() < 1) return "Hata: En az 1 parametre gerekli!";
        return String(sys.fsm->readfile(args[0].c_str()));
    }
    if (mod.equalsIgnoreCase("FSM") && cmd.equalsIgnoreCase("writefile")) {
        if (args.size() < 2) return "Hata: En az 2 parametre gerekli!";
        return sys.fsm->writefile(args[0].c_str(), args[1]) ? "true" : "false";
    }
    if (mod.equalsIgnoreCase("FSM") && cmd.equalsIgnoreCase("deletefile")) {
        if (args.size() < 1) return "Hata: En az 1 parametre gerekli!";
        return sys.fsm->deletefile(args[0].c_str()) ? "true" : "false";
    }
    if (mod.equalsIgnoreCase("FSM") && cmd.equalsIgnoreCase("getfilelist")) {
        if (args.size() < 0) return "Hata: En az 0 parametre gerekli!";
        return String(sys.fsm->getfilelist());
    }
    if (mod.equalsIgnoreCase("FSM") && cmd.equalsIgnoreCase("fileexists")) {
        if (args.size() < 1) return "Hata: En az 1 parametre gerekli!";
        return sys.fsm->fileexists(args[0].c_str()) ? "true" : "false";
    }

    return "Error: Command not found!";
}

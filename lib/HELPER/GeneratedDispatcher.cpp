// AUTO-GENERATED FILE - DO NOT EDIT
#include <Arduino.h>
#include "SYSTEM.h"
#include "HELPER.h"
#include "FSM.h"
#include "HELPER.h"
#include "OLED.h"
#include "SERVER.h"
#include "WIFI.h"

String HELPER::dispatchCommand(String mod, String cmd, std::vector<String> args) {
    if (mod.equalsIgnoreCase("SERVER") && cmd.equalsIgnoreCase("handleExecute")) {
        if (args.size() < 0) return "Error: 0 params required!";
        sys.server->handleExecute();
        return "OK";
    }
    if (mod.equalsIgnoreCase("SERVER") && cmd.equalsIgnoreCase("commandParseAndExecute")) {
        if (args.size() < 1) return "Error: 1 params required!";
        sys.server->commandParseAndExecute(args[0]);
        return "OK";
    }
    if (mod.equalsIgnoreCase("FSM") && cmd.equalsIgnoreCase("readfile")) {
        if (args.size() < 1) return "Error: 1 params required!";
        return String(sys.fsm->readfile(args[0].c_str()));
    }
    if (mod.equalsIgnoreCase("FSM") && cmd.equalsIgnoreCase("writefile")) {
        if (args.size() < 2) return "Error: 2 params required!";
        return sys.fsm->writefile(args[0].c_str(), args[1]) ? "true" : "false";
    }
    if (mod.equalsIgnoreCase("FSM") && cmd.equalsIgnoreCase("deletefile")) {
        if (args.size() < 1) return "Error: 1 params required!";
        return sys.fsm->deletefile(args[0].c_str()) ? "true" : "false";
    }
    if (mod.equalsIgnoreCase("FSM") && cmd.equalsIgnoreCase("getfilelist")) {
        if (args.size() < 0) return "Error: 0 params required!";
        return String(sys.fsm->getfilelist());
    }
    if (mod.equalsIgnoreCase("FSM") && cmd.equalsIgnoreCase("fileexists")) {
        if (args.size() < 1) return "Error: 1 params required!";
        return sys.fsm->fileexists(args[0].c_str()) ? "true" : "false";
    }
    if (mod.equalsIgnoreCase("HELPER") && cmd.equalsIgnoreCase("getHelp")) {
        if (args.size() < 0) return "Error: 0 params required!";
        return String(sys.helper->getHelp());
    }
    if (mod.equalsIgnoreCase("OLED") && cmd.equalsIgnoreCase("write")) {
        if (args.size() < 1) return "Error: 1 params required!";
        return String(sys.oled->write(args[0]));
    }
    if (mod.equalsIgnoreCase("OLED") && cmd.equalsIgnoreCase("write")) {
        if (args.size() < 1) return "Error: 1 params required!";
        return String(sys.oled->write(args[0].c_str()));
    }
    if (mod.equalsIgnoreCase("OLED") && cmd.equalsIgnoreCase("clear")) {
        if (args.size() < 0) return "Error: 0 params required!";
        sys.oled->clear();
        return "OK";
    }
    if (mod.equalsIgnoreCase("OLED") && cmd.equalsIgnoreCase("setBrightness")) {
        if (args.size() < 1) return "Error: 1 params required!";
        return String(sys.oled->setBrightness(args[0].toInt()));
    }
    if (mod.equalsIgnoreCase("OLED") && cmd.equalsIgnoreCase("getStatus")) {
        if (args.size() < 0) return "Error: 0 params required!";
        return String(sys.oled->getStatus());
    }
    if (mod.equalsIgnoreCase("OLED") && cmd.equalsIgnoreCase("setCursor")) {
        if (args.size() < 2) return "Error: 2 params required!";
        return String(sys.oled->setCursor(args[0].toInt(), args[1].toInt()));
    }
    if (mod.equalsIgnoreCase("OLED") && cmd.equalsIgnoreCase("setLineHeight")) {
        if (args.size() < 1) return "Error: 1 params required!";
        return String(sys.oled->setLineHeight(args[0].toInt()));
    }
    if (mod.equalsIgnoreCase("OLED") && cmd.equalsIgnoreCase("setScreenSize")) {
        if (args.size() < 2) return "Error: 2 params required!";
        return String(sys.oled->setScreenSize(args[0].toInt(), args[1].toInt()));
    }
    if (mod.equalsIgnoreCase("WIFI") && cmd.equalsIgnoreCase("reset")) {
        if (args.size() < 0) return "Error: 0 params required!";
        return String(sys.wifi->reset());
    }
    if (mod.equalsIgnoreCase("WIFI") && cmd.equalsIgnoreCase("connect")) {
        if (args.size() < 2) return "Error: 2 params required!";
        return String(sys.wifi->connect(args[0], args[1]));
    }
    if (mod.equalsIgnoreCase("WIFI") && cmd.equalsIgnoreCase("restart")) {
        if (args.size() < 0) return "Error: 0 params required!";
        return String(sys.wifi->restart());
    }
    if (mod.equalsIgnoreCase("WIFI") && cmd.equalsIgnoreCase("getIP")) {
        if (args.size() < 0) return "Error: 0 params required!";
        return String(sys.wifi->getIP());
    }
    if (mod.equalsIgnoreCase("WIFI") && cmd.equalsIgnoreCase("getMAC")) {
        if (args.size() < 0) return "Error: 0 params required!";
        return String(sys.wifi->getMAC());
    }
    if (mod.equalsIgnoreCase("WIFI") && cmd.equalsIgnoreCase("getSSID")) {
        if (args.size() < 0) return "Error: 0 params required!";
        return String(sys.wifi->getSSID());
    }
    if (mod.equalsIgnoreCase("WIFI") && cmd.equalsIgnoreCase("getPassword")) {
        if (args.size() < 0) return "Error: 0 params required!";
        return String(sys.wifi->getPassword());
    }

    return "Error: Command not found!";
}

String HELPER::getHelp() {
    String h = "<div style='text-align:left; font-family:monospace; font-size:12px;'>";
    h += "<b style='color:#00ff00'>--- SYSTEM HELP ---</b><br>";
    h += "<br><b style='color:#ffcc00'>[FSM]</b><br>";
    h += " - readfile(const char)<br>";
    h += " - writefile(const char, const String)<br>";
    h += " - deletefile(const char)<br>";
    h += " - getfilelist()<br>";
    h += " - fileexists(const char)<br>";
    h += "<br><b style='color:#ffcc00'>[HELPER]</b><br>";
    h += " - getHelp()<br>";
    h += "<br><b style='color:#ffcc00'>[OLED]</b><br>";
    h += " - write(const String)<br>";
    h += " - write(const char)<br>";
    h += " - clear()<br>";
    h += " - setBrightness(int)<br>";
    h += " - getStatus()<br>";
    h += " - setCursor(int, int)<br>";
    h += " - setLineHeight(int)<br>";
    h += " - setScreenSize(int, int)<br>";
    h += "<br><b style='color:#ffcc00'>[SERVER]</b><br>";
    h += " - handleExecute()<br>";
    h += " - commandParseAndExecute(String)<br>";
    h += "<br><b style='color:#ffcc00'>[WIFI]</b><br>";
    h += " - reset()<br>";
    h += " - connect(String, String)<br>";
    h += " - restart()<br>";
    h += " - getIP()<br>";
    h += " - getMAC()<br>";
    h += " - getSSID()<br>";
    h += " - getPassword()<br>";
    h += "</div>";
    return h;
}

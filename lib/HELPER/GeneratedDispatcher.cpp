// AUTO-GENERATED FILE - DO NOT EDIT
#include <Arduino.h>
#include "SYSTEM.h"
#include "HELPER.h"
#include "BATTERY.h"
#include "FSM.h"
#include "HELPER.h"
#include "OLED.h"
#include "SERVER.h"
#include "SYSTEM.h"
#include "TIMER.h"
#include "WIFI.h"

String HELPER::dispatchCommand(String mod, String cmd, std::vector<String> args) {
    if (mod.equalsIgnoreCase("HELPER") && cmd.equalsIgnoreCase("getHelp")) return getHelp();
    if (mod.equalsIgnoreCase("HELPER") && cmd.equalsIgnoreCase("getCommandsJSON")) return getCommandsJSON();
    if (mod.equalsIgnoreCase("SERVER") && cmd.equalsIgnoreCase("logger")) {
        if (args.size() < 1) return "Error: 1 params required!";
        sys.server->logger(args[0]);
        return "OK";
    }
    if (mod.equalsIgnoreCase("SYSTEM") && cmd.equalsIgnoreCase("addToQueue")) {
        if (args.size() < 1) return "Error: 1 params required!";
        sys.addToQueue(args[0]);
        return "OK";
    }
    if (mod.equalsIgnoreCase("SYSTEM") && cmd.equalsIgnoreCase("updateQueue")) {
        if (args.size() < 0) return "Error: 0 params required!";
        sys.updateQueue();
        return "OK";
    }
    if (mod.equalsIgnoreCase("SYSTEM") && cmd.equalsIgnoreCase("automate")) {
        if (args.size() < 1) return "Error: 1 params required!";
        sys.automate(args[0]);
        return "OK";
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
    if (mod.equalsIgnoreCase("OLED") && cmd.equalsIgnoreCase("setInverse")) {
        if (args.size() < 1) return "Error: 1 params required!";
        return String(sys.oled->setInverse((args[0].equalsIgnoreCase("true") || args[0] == "1")));
    }
    if (mod.equalsIgnoreCase("OLED") && cmd.equalsIgnoreCase("drawProgressBar")) {
        if (args.size() < 5) return "Error: 5 params required!";
        return String(sys.oled->drawProgressBar(args[0].toInt(), args[1].toInt(), args[2].toInt(), args[3].toInt(), args[4].toInt()));
    }
    if (mod.equalsIgnoreCase("OLED") && cmd.equalsIgnoreCase("drawCentered")) {
        if (args.size() < 2) return "Error: 2 params required!";
        return String(sys.oled->drawCentered(args[0].toInt(), args[1].c_str()));
    }
    if (mod.equalsIgnoreCase("BATTERY") && cmd.equalsIgnoreCase("begin")) {
        if (args.size() < 0) return "Error: 0 params required!";
        sys.battery->begin();
        return "OK";
    }
    if (mod.equalsIgnoreCase("BATTERY") && cmd.equalsIgnoreCase("getVoltage")) {
        if (args.size() < 0) return "Error: 0 params required!";
        return String(sys.battery->getVoltage());
    }
    if (mod.equalsIgnoreCase("BATTERY") && cmd.equalsIgnoreCase("updateMeasurement")) {
        if (args.size() < 0) return "Error: 0 params required!";
        return String(sys.battery->updateMeasurement());
    }
    if (mod.equalsIgnoreCase("BATTERY") && cmd.equalsIgnoreCase("getLastResult")) {
        if (args.size() < 0) return "Error: 0 params required!";
        return String(sys.battery->getLastResult());
    }
    if (mod.equalsIgnoreCase("BATTERY") && cmd.equalsIgnoreCase("baslatTest")) {
        if (args.size() < 2) return "Error: 2 params required!";
        sys.battery->baslatTest(args[0].toInt(), args[1].toFloat());
        return "OK";
    }
    if (mod.equalsIgnoreCase("BATTERY") && cmd.equalsIgnoreCase("testUpdate")) {
        if (args.size() < 0) return "Error: 0 params required!";
        return String(sys.battery->testUpdate());
    }
    if (mod.equalsIgnoreCase("BATTERY") && cmd.equalsIgnoreCase("getInstantReport")) {
        if (args.size() < 0) return "Error: 0 params required!";
        return String(sys.battery->getInstantReport());
    }
    if (mod.equalsIgnoreCase("BATTERY") && cmd.equalsIgnoreCase("testRaporu")) {
        if (args.size() < 0) return "Error: 0 params required!";
        return String(sys.battery->testRaporu());
    }
    if (mod.equalsIgnoreCase("HELPER") && cmd.equalsIgnoreCase("wtf")) {
        if (args.size() < 0) return "Error: 0 params required!";
        return String(sys.helper->wtf());
    }
    if (mod.equalsIgnoreCase("HELPER") && cmd.equalsIgnoreCase("getHelp")) {
        if (args.size() < 0) return "Error: 0 params required!";
        return String(sys.helper->getHelp());
    }
    if (mod.equalsIgnoreCase("HELPER") && cmd.equalsIgnoreCase("getCommandsJSON")) {
        if (args.size() < 0) return "Error: 0 params required!";
        return String(sys.helper->getCommandsJSON());
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
    if (mod.equalsIgnoreCase("WIFI") && cmd.equalsIgnoreCase("getStatus")) {
        if (args.size() < 0) return "Error: 0 params required!";
        return String(sys.wifi->getStatus());
    }
    if (mod.equalsIgnoreCase("WIFI") && cmd.equalsIgnoreCase("getStatusAll")) {
        if (args.size() < 0) return "Error: 0 params required!";
        return String(sys.wifi->getStatusAll());
    }
    if (mod.equalsIgnoreCase("TIMER") && cmd.equalsIgnoreCase("start")) {
        if (args.size() < 0) return "Error: 0 params required!";
        return String(sys.timer->start());
    }
    if (mod.equalsIgnoreCase("TIMER") && cmd.equalsIgnoreCase("isExpired")) {
        if (args.size() < 1) return "Error: 1 params required!";
        return String(sys.timer->isExpired(args[0].toInt()));
    }
    if (mod.equalsIgnoreCase("TIMER") && cmd.equalsIgnoreCase("getElapsedMillis")) {
        if (args.size() < 0) return "Error: 0 params required!";
        return String(sys.timer->getElapsedMillis());
    }
    if (mod.equalsIgnoreCase("TIMER") && cmd.equalsIgnoreCase("stop")) {
        if (args.size() < 0) return "Error: 0 params required!";
        return String(sys.timer->stop());
    }
    if (mod.equalsIgnoreCase("TIMER") && cmd.equalsIgnoreCase("reset")) {
        if (args.size() < 0) return "Error: 0 params required!";
        return String(sys.timer->reset());
    }
    if (mod.equalsIgnoreCase("FSM") && cmd.equalsIgnoreCase("readfile")) {
        if (args.size() < 1) return "Error: 1 params required!";
        return String(sys.fsm->readfile(args[0].c_str()));
    }
    if (mod.equalsIgnoreCase("FSM") && cmd.equalsIgnoreCase("writefile")) {
        if (args.size() < 2) return "Error: 2 params required!";
        return String(sys.fsm->writefile(args[0].c_str(), args[1]));
    }
    if (mod.equalsIgnoreCase("FSM") && cmd.equalsIgnoreCase("deletefile")) {
        if (args.size() < 1) return "Error: 1 params required!";
        return String(sys.fsm->deletefile(args[0].c_str()));
    }
    if (mod.equalsIgnoreCase("FSM") && cmd.equalsIgnoreCase("getfilelist")) {
        if (args.size() < 0) return "Error: 0 params required!";
        return String(sys.fsm->getfilelist());
    }
    if (mod.equalsIgnoreCase("FSM") && cmd.equalsIgnoreCase("fileexists")) {
        if (args.size() < 1) return "Error: 1 params required!";
        return String(sys.fsm->fileexists(args[0].c_str()));
    }

    return "Error: Command not found!";
}

String HELPER::getCommandsJSON() {
    String j = "[";
    j += "{";
    j += "\"module\": \"SERVER\", ";
    j += "\"name\": \"logger\", ";
    j += "\"params\": [";
    j += "\"String\"";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"SYSTEM\", ";
    j += "\"name\": \"addToQueue\", ";
    j += "\"params\": [";
    j += "\"String\"";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"SYSTEM\", ";
    j += "\"name\": \"updateQueue\", ";
    j += "\"params\": [";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"SYSTEM\", ";
    j += "\"name\": \"automate\", ";
    j += "\"params\": [";
    j += "\"String\"";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"OLED\", ";
    j += "\"name\": \"write\", ";
    j += "\"params\": [";
    j += "\"const String\"";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"OLED\", ";
    j += "\"name\": \"write\", ";
    j += "\"params\": [";
    j += "\"const char\"";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"OLED\", ";
    j += "\"name\": \"clear\", ";
    j += "\"params\": [";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"OLED\", ";
    j += "\"name\": \"setBrightness\", ";
    j += "\"params\": [";
    j += "\"int\"";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"OLED\", ";
    j += "\"name\": \"getStatus\", ";
    j += "\"params\": [";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"OLED\", ";
    j += "\"name\": \"setCursor\", ";
    j += "\"params\": [";
    j += "\"int\"";
    j += ", ";
    j += "\"int\"";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"OLED\", ";
    j += "\"name\": \"setLineHeight\", ";
    j += "\"params\": [";
    j += "\"int\"";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"OLED\", ";
    j += "\"name\": \"setScreenSize\", ";
    j += "\"params\": [";
    j += "\"int\"";
    j += ", ";
    j += "\"int\"";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"OLED\", ";
    j += "\"name\": \"setInverse\", ";
    j += "\"params\": [";
    j += "\"bool\"";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"OLED\", ";
    j += "\"name\": \"drawProgressBar\", ";
    j += "\"params\": [";
    j += "\"int\"";
    j += ", ";
    j += "\"int\"";
    j += ", ";
    j += "\"int\"";
    j += ", ";
    j += "\"int\"";
    j += ", ";
    j += "\"int\"";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"OLED\", ";
    j += "\"name\": \"drawCentered\", ";
    j += "\"params\": [";
    j += "\"int\"";
    j += ", ";
    j += "\"const char*\"";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"BATTERY\", ";
    j += "\"name\": \"begin\", ";
    j += "\"params\": [";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"BATTERY\", ";
    j += "\"name\": \"getVoltage\", ";
    j += "\"params\": [";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"BATTERY\", ";
    j += "\"name\": \"updateMeasurement\", ";
    j += "\"params\": [";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"BATTERY\", ";
    j += "\"name\": \"getLastResult\", ";
    j += "\"params\": [";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"BATTERY\", ";
    j += "\"name\": \"baslatTest\", ";
    j += "\"params\": [";
    j += "\"int\"";
    j += ", ";
    j += "\"float\"";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"BATTERY\", ";
    j += "\"name\": \"testUpdate\", ";
    j += "\"params\": [";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"BATTERY\", ";
    j += "\"name\": \"getInstantReport\", ";
    j += "\"params\": [";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"BATTERY\", ";
    j += "\"name\": \"testRaporu\", ";
    j += "\"params\": [";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"HELPER\", ";
    j += "\"name\": \"wtf\", ";
    j += "\"params\": [";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"HELPER\", ";
    j += "\"name\": \"getHelp\", ";
    j += "\"params\": [";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"HELPER\", ";
    j += "\"name\": \"getCommandsJSON\", ";
    j += "\"params\": [";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"WIFI\", ";
    j += "\"name\": \"reset\", ";
    j += "\"params\": [";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"WIFI\", ";
    j += "\"name\": \"connect\", ";
    j += "\"params\": [";
    j += "\"String\"";
    j += ", ";
    j += "\"String\"";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"WIFI\", ";
    j += "\"name\": \"restart\", ";
    j += "\"params\": [";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"WIFI\", ";
    j += "\"name\": \"getIP\", ";
    j += "\"params\": [";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"WIFI\", ";
    j += "\"name\": \"getMAC\", ";
    j += "\"params\": [";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"WIFI\", ";
    j += "\"name\": \"getSSID\", ";
    j += "\"params\": [";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"WIFI\", ";
    j += "\"name\": \"getPassword\", ";
    j += "\"params\": [";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"WIFI\", ";
    j += "\"name\": \"getStatus\", ";
    j += "\"params\": [";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"WIFI\", ";
    j += "\"name\": \"getStatusAll\", ";
    j += "\"params\": [";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"TIMER\", ";
    j += "\"name\": \"start\", ";
    j += "\"params\": [";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"TIMER\", ";
    j += "\"name\": \"isExpired\", ";
    j += "\"params\": [";
    j += "\"unsigned long\"";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"TIMER\", ";
    j += "\"name\": \"getElapsedMillis\", ";
    j += "\"params\": [";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"TIMER\", ";
    j += "\"name\": \"stop\", ";
    j += "\"params\": [";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"TIMER\", ";
    j += "\"name\": \"reset\", ";
    j += "\"params\": [";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"FSM\", ";
    j += "\"name\": \"readfile\", ";
    j += "\"params\": [";
    j += "\"const char\"";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"FSM\", ";
    j += "\"name\": \"writefile\", ";
    j += "\"params\": [";
    j += "\"const char\"";
    j += ", ";
    j += "\"const String\"";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"FSM\", ";
    j += "\"name\": \"deletefile\", ";
    j += "\"params\": [";
    j += "\"const char\"";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"FSM\", ";
    j += "\"name\": \"getfilelist\", ";
    j += "\"params\": [";
    j += "]";
    j += "}";
    j += ", ";
    j += "{";
    j += "\"module\": \"FSM\", ";
    j += "\"name\": \"fileexists\", ";
    j += "\"params\": [";
    j += "\"const char\"";
    j += "]";
    j += "}";
    j += "]";
    return j;
}

String HELPER::getHelp() {
    String h = "<div style='text-align:left; font-family:sans-serif; background:#1e1e1e; padding:15px; border-radius:8px; color:#ddd; border:1px solid #333;'>";
    h += "<h2 style='color:#4CAF50; margin-top:0;'>Remote Control Panel</h2>";
    h += "<h3 style='color:#FF9800; border-bottom:1px solid #444; margin-bottom:10px;'>BATTERY</h3>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>begin</strong><br>";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'BATTERY begin'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>getVoltage</strong><br>";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'BATTERY getVoltage'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>updateMeasurement</strong><br>";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'BATTERY updateMeasurement'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>getLastResult</strong><br>";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'BATTERY getLastResult'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>baslatTest</strong><br>";
    h += "<input id='input_BATTERY_baslatTest_4_0' placeholder='int' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ";
    h += "<input id='input_BATTERY_baslatTest_4_1' placeholder='float' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'BATTERY baslatTest ' + document.getElementById('input_BATTERY_baslatTest_4_0').value + ' ' + document.getElementById('input_BATTERY_baslatTest_4_1').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>testUpdate</strong><br>";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'BATTERY testUpdate'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>getInstantReport</strong><br>";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'BATTERY getInstantReport'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>testRaporu</strong><br>";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'BATTERY testRaporu'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<h3 style='color:#FF9800; border-bottom:1px solid #444; margin-bottom:10px;'>FSM</h3>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>readfile</strong><br>";
    h += "<input id='input_FSM_readfile_8_0' placeholder='const char' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'FSM readfile ' + document.getElementById('input_FSM_readfile_8_0').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>writefile</strong><br>";
    h += "<input id='input_FSM_writefile_9_0' placeholder='const char' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ";
    h += "<input id='input_FSM_writefile_9_1' placeholder='const String' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'FSM writefile ' + document.getElementById('input_FSM_writefile_9_0').value + ' ' + document.getElementById('input_FSM_writefile_9_1').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>deletefile</strong><br>";
    h += "<input id='input_FSM_deletefile_10_0' placeholder='const char' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'FSM deletefile ' + document.getElementById('input_FSM_deletefile_10_0').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>getfilelist</strong><br>";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'FSM getfilelist'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>fileexists</strong><br>";
    h += "<input id='input_FSM_fileexists_12_0' placeholder='const char' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'FSM fileexists ' + document.getElementById('input_FSM_fileexists_12_0').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<h3 style='color:#FF9800; border-bottom:1px solid #444; margin-bottom:10px;'>HELPER</h3>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>wtf</strong><br>";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'HELPER wtf'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>getHelp</strong><br>";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'HELPER getHelp'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>getCommandsJSON</strong><br>";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'HELPER getCommandsJSON'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<h3 style='color:#FF9800; border-bottom:1px solid #444; margin-bottom:10px;'>OLED</h3>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>write</strong><br>";
    h += "<input id='input_OLED_write_16_0' placeholder='const String' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'OLED write ' + document.getElementById('input_OLED_write_16_0').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>write</strong><br>";
    h += "<input id='input_OLED_write_17_0' placeholder='const char' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'OLED write ' + document.getElementById('input_OLED_write_17_0').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>clear</strong><br>";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'OLED clear'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>setBrightness</strong><br>";
    h += "<input id='input_OLED_setBrightness_19_0' placeholder='int' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'OLED setBrightness ' + document.getElementById('input_OLED_setBrightness_19_0').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>getStatus</strong><br>";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'OLED getStatus'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>setCursor</strong><br>";
    h += "<input id='input_OLED_setCursor_21_0' placeholder='int' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ";
    h += "<input id='input_OLED_setCursor_21_1' placeholder='int' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'OLED setCursor ' + document.getElementById('input_OLED_setCursor_21_0').value + ' ' + document.getElementById('input_OLED_setCursor_21_1').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>setLineHeight</strong><br>";
    h += "<input id='input_OLED_setLineHeight_22_0' placeholder='int' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'OLED setLineHeight ' + document.getElementById('input_OLED_setLineHeight_22_0').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>setScreenSize</strong><br>";
    h += "<input id='input_OLED_setScreenSize_23_0' placeholder='int' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ";
    h += "<input id='input_OLED_setScreenSize_23_1' placeholder='int' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'OLED setScreenSize ' + document.getElementById('input_OLED_setScreenSize_23_0').value + ' ' + document.getElementById('input_OLED_setScreenSize_23_1').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>setInverse</strong><br>";
    h += "<input id='input_OLED_setInverse_24_0' placeholder='bool' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'OLED setInverse ' + document.getElementById('input_OLED_setInverse_24_0').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>drawProgressBar</strong><br>";
    h += "<input id='input_OLED_drawProgressBar_25_0' placeholder='int' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ";
    h += "<input id='input_OLED_drawProgressBar_25_1' placeholder='int' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ";
    h += "<input id='input_OLED_drawProgressBar_25_2' placeholder='int' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ";
    h += "<input id='input_OLED_drawProgressBar_25_3' placeholder='int' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ";
    h += "<input id='input_OLED_drawProgressBar_25_4' placeholder='int' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'OLED drawProgressBar ' + document.getElementById('input_OLED_drawProgressBar_25_0').value + ' ' + document.getElementById('input_OLED_drawProgressBar_25_1').value + ' ' + document.getElementById('input_OLED_drawProgressBar_25_2').value + ' ' + document.getElementById('input_OLED_drawProgressBar_25_3').value + ' ' + document.getElementById('input_OLED_drawProgressBar_25_4').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>drawCentered</strong><br>";
    h += "<input id='input_OLED_drawCentered_26_0' placeholder='int' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ";
    h += "<input id='input_OLED_drawCentered_26_1' placeholder='const char*' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'OLED drawCentered ' + document.getElementById('input_OLED_drawCentered_26_0').value + ' ' + document.getElementById('input_OLED_drawCentered_26_1').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<h3 style='color:#FF9800; border-bottom:1px solid #444; margin-bottom:10px;'>SERVER</h3>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>logger</strong><br>";
    h += "<input id='input_SERVER_logger_27_0' placeholder='String' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'SERVER logger ' + document.getElementById('input_SERVER_logger_27_0').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<h3 style='color:#FF9800; border-bottom:1px solid #444; margin-bottom:10px;'>SYSTEM</h3>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>addToQueue</strong><br>";
    h += "<input id='input_SYSTEM_addToQueue_28_0' placeholder='String' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'SYSTEM addToQueue ' + document.getElementById('input_SYSTEM_addToQueue_28_0').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>updateQueue</strong><br>";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'SYSTEM updateQueue'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>automate</strong><br>";
    h += "<input id='input_SYSTEM_automate_30_0' placeholder='String' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'SYSTEM automate ' + document.getElementById('input_SYSTEM_automate_30_0').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<h3 style='color:#FF9800; border-bottom:1px solid #444; margin-bottom:10px;'>TIMER</h3>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>start</strong><br>";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'TIMER start'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>isExpired</strong><br>";
    h += "<input id='input_TIMER_isExpired_32_0' placeholder='unsigned long' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'TIMER isExpired ' + document.getElementById('input_TIMER_isExpired_32_0').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>getElapsedMillis</strong><br>";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'TIMER getElapsedMillis'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>stop</strong><br>";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'TIMER stop'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>reset</strong><br>";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'TIMER reset'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<h3 style='color:#FF9800; border-bottom:1px solid #444; margin-bottom:10px;'>WIFI</h3>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>reset</strong><br>";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'WIFI reset'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>connect</strong><br>";
    h += "<input id='input_WIFI_connect_37_0' placeholder='String' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ";
    h += "<input id='input_WIFI_connect_37_1' placeholder='String' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'WIFI connect ' + document.getElementById('input_WIFI_connect_37_0').value + ' ' + document.getElementById('input_WIFI_connect_37_1').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>restart</strong><br>";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'WIFI restart'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>getIP</strong><br>";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'WIFI getIP'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>getMAC</strong><br>";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'WIFI getMAC'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>getSSID</strong><br>";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'WIFI getSSID'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>getPassword</strong><br>";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'WIFI getPassword'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>getStatus</strong><br>";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'WIFI getStatus'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>";
    h += "<strong>getStatusAll</strong><br>";
    h += "<button hx-post='/execute' hx-vals=\"js:{val: 'WIFI getStatusAll'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>";
    h += "</div>";
    h += "</div>";
    return h;
}

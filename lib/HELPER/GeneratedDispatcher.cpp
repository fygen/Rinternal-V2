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
    String logMsg = F("[CMD] ") + mod + F(" ") + cmd;
    for(const auto& a : args) logMsg += F(" '") + a + F("'");
    sys.server->logger(logMsg);

    if (mod.equalsIgnoreCase(F("HELPER")) && cmd.equalsIgnoreCase(F("getHelp"))) return getHelp();
    if (mod.equalsIgnoreCase(F("HELPER")) && cmd.equalsIgnoreCase(F("getCommandsJSON"))) return getCommandsJSON();
    if (mod.equalsIgnoreCase(F("HELPER")) && cmd.equalsIgnoreCase(F("getFreeHeap"))) return getFreeHeap();
    if (mod.equalsIgnoreCase(F("SERVER")) && cmd.equalsIgnoreCase(F("logger"))) {
        if (args.size() < 1) {
            String err = F("Error: 1 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String joinedArgs0 = F("");
        for(size_t j = 0; j < args.size(); j++) {
            joinedArgs0 += args[j] + (j < args.size() - 1 ? F(" ") : F(""));
        }
        sys.server->logger(joinedArgs0);
        sys.server->logger(F("[RES] OK"));
        return F("OK");
    }
    if (mod.equalsIgnoreCase(F("SYSTEM")) && cmd.equalsIgnoreCase(F("addToQueue"))) {
        if (args.size() < 1) {
            String err = F("Error: 1 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String joinedArgs0 = F("");
        for(size_t j = 0; j < args.size(); j++) {
            joinedArgs0 += args[j] + (j < args.size() - 1 ? F(" ") : F(""));
        }
        sys.addToQueue(joinedArgs0);
        sys.server->logger(F("[RES] OK"));
        return F("OK");
    }
    if (mod.equalsIgnoreCase(F("SYSTEM")) && cmd.equalsIgnoreCase(F("updateQueue"))) {
        if (args.size() < 0) {
            String err = F("Error: 0 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        sys.updateQueue();
        sys.server->logger(F("[RES] OK"));
        return F("OK");
    }
    if (mod.equalsIgnoreCase(F("SYSTEM")) && cmd.equalsIgnoreCase(F("stopQueue"))) {
        if (args.size() < 0) {
            String err = F("Error: 0 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        sys.stopQueue();
        sys.server->logger(F("[RES] OK"));
        return F("OK");
    }
    if (mod.equalsIgnoreCase(F("SYSTEM")) && cmd.equalsIgnoreCase(F("automate"))) {
        if (args.size() < 1) {
            String err = F("Error: 1 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String joinedArgs0 = F("");
        for(size_t j = 0; j < args.size(); j++) {
            joinedArgs0 += args[j] + (j < args.size() - 1 ? F(" ") : F(""));
        }
        sys.automate(joinedArgs0);
        sys.server->logger(F("[RES] OK"));
        return F("OK");
    }
    if (mod.equalsIgnoreCase(F("OLED")) && cmd.equalsIgnoreCase(F("write"))) {
        if (args.size() < 1) {
            String err = F("Error: 1 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String joinedArgs0 = F("");
        for(size_t j = 0; j < args.size(); j++) {
            joinedArgs0 += args[j] + (j < args.size() - 1 ? F(" ") : F(""));
        }
        String res = String(sys.oled->write(joinedArgs0));
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("OLED")) && cmd.equalsIgnoreCase(F("write"))) {
        if (args.size() < 1) {
            String err = F("Error: 1 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String res = String(sys.oled->write(args[0].c_str()));
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("OLED")) && cmd.equalsIgnoreCase(F("clear"))) {
        if (args.size() < 0) {
            String err = F("Error: 0 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        sys.oled->clear();
        sys.server->logger(F("[RES] OK"));
        return F("OK");
    }
    if (mod.equalsIgnoreCase(F("OLED")) && cmd.equalsIgnoreCase(F("setBrightness"))) {
        if (args.size() < 1) {
            String err = F("Error: 1 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String res = String(sys.oled->setBrightness(args[0].toInt()));
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("OLED")) && cmd.equalsIgnoreCase(F("getStatus"))) {
        if (args.size() < 0) {
            String err = F("Error: 0 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String res = String(sys.oled->getStatus());
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("OLED")) && cmd.equalsIgnoreCase(F("setCursor"))) {
        if (args.size() < 2) {
            String err = F("Error: 2 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String res = String(sys.oled->setCursor(args[0].toInt(), args[1].toInt()));
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("OLED")) && cmd.equalsIgnoreCase(F("setLineHeight"))) {
        if (args.size() < 1) {
            String err = F("Error: 1 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String res = String(sys.oled->setLineHeight(args[0].toInt()));
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("OLED")) && cmd.equalsIgnoreCase(F("setScreenSize"))) {
        if (args.size() < 2) {
            String err = F("Error: 2 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String res = String(sys.oled->setScreenSize(args[0].toInt(), args[1].toInt()));
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("OLED")) && cmd.equalsIgnoreCase(F("setInverse"))) {
        if (args.size() < 1) {
            String err = F("Error: 1 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String res = String(sys.oled->setInverse((args[0].equalsIgnoreCase(F("true")) || args[0] == F("1"))));
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("OLED")) && cmd.equalsIgnoreCase(F("drawProgressBar"))) {
        if (args.size() < 5) {
            String err = F("Error: 5 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String res = String(sys.oled->drawProgressBar(args[0].toInt(), args[1].toInt(), args[2].toInt(), args[3].toInt(), args[4].toInt()));
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("OLED")) && cmd.equalsIgnoreCase(F("drawCentered"))) {
        if (args.size() < 2) {
            String err = F("Error: 2 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String joinedArgs1 = F("");
        for(size_t j = 1; j < args.size(); j++) {
            joinedArgs1 += args[j] + (j < args.size() - 1 ? F(" ") : F(""));
        }
        String res = String(sys.oled->drawCentered(args[0].toInt(), joinedArgs1.c_str()));
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("BATTERY")) && cmd.equalsIgnoreCase(F("begin"))) {
        if (args.size() < 0) {
            String err = F("Error: 0 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        sys.battery->begin();
        sys.server->logger(F("[RES] OK"));
        return F("OK");
    }
    if (mod.equalsIgnoreCase(F("BATTERY")) && cmd.equalsIgnoreCase(F("getVoltage"))) {
        if (args.size() < 0) {
            String err = F("Error: 0 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String res = String(sys.battery->getVoltage());
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("BATTERY")) && cmd.equalsIgnoreCase(F("updateMeasurement"))) {
        if (args.size() < 0) {
            String err = F("Error: 0 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String res = String(sys.battery->updateMeasurement());
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("BATTERY")) && cmd.equalsIgnoreCase(F("getLastResult"))) {
        if (args.size() < 0) {
            String err = F("Error: 0 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String res = String(sys.battery->getLastResult());
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("BATTERY")) && cmd.equalsIgnoreCase(F("baslatTest"))) {
        if (args.size() < 2) {
            String err = F("Error: 2 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        sys.battery->baslatTest(args[0].toInt(), args[1].toFloat());
        sys.server->logger(F("[RES] OK"));
        return F("OK");
    }
    if (mod.equalsIgnoreCase(F("BATTERY")) && cmd.equalsIgnoreCase(F("testUpdate"))) {
        if (args.size() < 0) {
            String err = F("Error: 0 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String res = String(sys.battery->testUpdate());
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("BATTERY")) && cmd.equalsIgnoreCase(F("getInstantReport"))) {
        if (args.size() < 0) {
            String err = F("Error: 0 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String res = String(sys.battery->getInstantReport());
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("BATTERY")) && cmd.equalsIgnoreCase(F("testRaporu"))) {
        if (args.size() < 0) {
            String err = F("Error: 0 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String res = String(sys.battery->testRaporu());
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("HELPER")) && cmd.equalsIgnoreCase(F("wtf"))) {
        if (args.size() < 0) {
            String err = F("Error: 0 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String res = String(sys.helper->wtf());
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("HELPER")) && cmd.equalsIgnoreCase(F("getFreeHeap"))) {
        if (args.size() < 0) {
            String err = F("Error: 0 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String res = String(sys.helper->getFreeHeap());
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("HELPER")) && cmd.equalsIgnoreCase(F("getHelp"))) {
        if (args.size() < 0) {
            String err = F("Error: 0 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String res = String(sys.helper->getHelp());
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("HELPER")) && cmd.equalsIgnoreCase(F("getCommandsJSON"))) {
        if (args.size() < 0) {
            String err = F("Error: 0 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String res = String(sys.helper->getCommandsJSON());
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("WIFI")) && cmd.equalsIgnoreCase(F("reset"))) {
        if (args.size() < 0) {
            String err = F("Error: 0 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String res = String(sys.wifi->reset());
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("WIFI")) && cmd.equalsIgnoreCase(F("connect"))) {
        if (args.size() < 2) {
            String err = F("Error: 2 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String joinedArgs1 = F("");
        for(size_t j = 1; j < args.size(); j++) {
            joinedArgs1 += args[j] + (j < args.size() - 1 ? F(" ") : F(""));
        }
        String res = String(sys.wifi->connect(args[0], joinedArgs1));
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("WIFI")) && cmd.equalsIgnoreCase(F("restart"))) {
        if (args.size() < 0) {
            String err = F("Error: 0 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String res = String(sys.wifi->restart());
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("WIFI")) && cmd.equalsIgnoreCase(F("getIP"))) {
        if (args.size() < 0) {
            String err = F("Error: 0 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String res = String(sys.wifi->getIP());
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("WIFI")) && cmd.equalsIgnoreCase(F("getMAC"))) {
        if (args.size() < 0) {
            String err = F("Error: 0 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String res = String(sys.wifi->getMAC());
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("WIFI")) && cmd.equalsIgnoreCase(F("getSSID"))) {
        if (args.size() < 0) {
            String err = F("Error: 0 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String res = String(sys.wifi->getSSID());
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("WIFI")) && cmd.equalsIgnoreCase(F("getPassword"))) {
        if (args.size() < 0) {
            String err = F("Error: 0 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String res = String(sys.wifi->getPassword());
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("WIFI")) && cmd.equalsIgnoreCase(F("getStatus"))) {
        if (args.size() < 0) {
            String err = F("Error: 0 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String res = String(sys.wifi->getStatus());
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("WIFI")) && cmd.equalsIgnoreCase(F("getStatusAll"))) {
        if (args.size() < 0) {
            String err = F("Error: 0 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String res = String(sys.wifi->getStatusAll());
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("WIFI")) && cmd.equalsIgnoreCase(F("isConnected"))) {
        if (args.size() < 0) {
            String err = F("Error: 0 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String res = String(sys.wifi->isConnected());
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("TIMER")) && cmd.equalsIgnoreCase(F("start"))) {
        if (args.size() < 0) {
            String err = F("Error: 0 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String res = String(sys.timer->start());
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("TIMER")) && cmd.equalsIgnoreCase(F("isExpired"))) {
        if (args.size() < 1) {
            String err = F("Error: 1 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String res = String(sys.timer->isExpired(args[0].toInt()));
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("TIMER")) && cmd.equalsIgnoreCase(F("getElapsedMillis"))) {
        if (args.size() < 0) {
            String err = F("Error: 0 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String res = String(sys.timer->getElapsedMillis());
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("TIMER")) && cmd.equalsIgnoreCase(F("stop"))) {
        if (args.size() < 0) {
            String err = F("Error: 0 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String res = String(sys.timer->stop());
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("TIMER")) && cmd.equalsIgnoreCase(F("reset"))) {
        if (args.size() < 0) {
            String err = F("Error: 0 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String res = String(sys.timer->reset());
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("FSM")) && cmd.equalsIgnoreCase(F("readfile"))) {
        if (args.size() < 1) {
            String err = F("Error: 1 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String res = String(sys.fsm->readfile(args[0].c_str()));
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("FSM")) && cmd.equalsIgnoreCase(F("writefile"))) {
        if (args.size() < 2) {
            String err = F("Error: 2 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String joinedArgs1 = F("");
        for(size_t j = 1; j < args.size(); j++) {
            joinedArgs1 += args[j] + (j < args.size() - 1 ? F(" ") : F(""));
        }
        String res = String(sys.fsm->writefile(args[0].c_str(), joinedArgs1));
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("FSM")) && cmd.equalsIgnoreCase(F("deletefile"))) {
        if (args.size() < 1) {
            String err = F("Error: 1 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String res = String(sys.fsm->deletefile(args[0].c_str()));
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("FSM")) && cmd.equalsIgnoreCase(F("getfilelist"))) {
        if (args.size() < 0) {
            String err = F("Error: 0 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String res = String(sys.fsm->getfilelist());
        sys.server->logger(F("[RES] ") + res);
        return res;
    }
    if (mod.equalsIgnoreCase(F("FSM")) && cmd.equalsIgnoreCase(F("fileexists"))) {
        if (args.size() < 1) {
            String err = F("Error: 1 params required!");
            sys.server->logger(F("[RES] ") + err);
            return err;
        }
        String res = String(sys.fsm->fileexists(args[0].c_str()));
        sys.server->logger(F("[RES] ") + res);
        return res;
    }

    String finalErr = F("Error: Command not found!");
    sys.server->logger(F("[RES] ") + finalErr);
    return finalErr;
}

String HELPER::getCommandsJSON() {
    String j = F("[");
    j += F("{");
    j += F("\"module\": \"SERVER\", ");
    j += F("\"name\": \"logger\", ");
    j += F("\"params\": [");
    j += F("\"String\"");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"SYSTEM\", ");
    j += F("\"name\": \"addToQueue\", ");
    j += F("\"params\": [");
    j += F("\"String\"");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"SYSTEM\", ");
    j += F("\"name\": \"updateQueue\", ");
    j += F("\"params\": [");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"SYSTEM\", ");
    j += F("\"name\": \"stopQueue\", ");
    j += F("\"params\": [");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"SYSTEM\", ");
    j += F("\"name\": \"automate\", ");
    j += F("\"params\": [");
    j += F("\"String\"");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"OLED\", ");
    j += F("\"name\": \"write\", ");
    j += F("\"params\": [");
    j += F("\"const String\"");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"OLED\", ");
    j += F("\"name\": \"write\", ");
    j += F("\"params\": [");
    j += F("\"const char\"");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"OLED\", ");
    j += F("\"name\": \"clear\", ");
    j += F("\"params\": [");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"OLED\", ");
    j += F("\"name\": \"setBrightness\", ");
    j += F("\"params\": [");
    j += F("\"int\"");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"OLED\", ");
    j += F("\"name\": \"getStatus\", ");
    j += F("\"params\": [");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"OLED\", ");
    j += F("\"name\": \"setCursor\", ");
    j += F("\"params\": [");
    j += F("\"int\"");
    j += F(", ");
    j += F("\"int\"");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"OLED\", ");
    j += F("\"name\": \"setLineHeight\", ");
    j += F("\"params\": [");
    j += F("\"int\"");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"OLED\", ");
    j += F("\"name\": \"setScreenSize\", ");
    j += F("\"params\": [");
    j += F("\"int\"");
    j += F(", ");
    j += F("\"int\"");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"OLED\", ");
    j += F("\"name\": \"setInverse\", ");
    j += F("\"params\": [");
    j += F("\"bool\"");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"OLED\", ");
    j += F("\"name\": \"drawProgressBar\", ");
    j += F("\"params\": [");
    j += F("\"int\"");
    j += F(", ");
    j += F("\"int\"");
    j += F(", ");
    j += F("\"int\"");
    j += F(", ");
    j += F("\"int\"");
    j += F(", ");
    j += F("\"int\"");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"OLED\", ");
    j += F("\"name\": \"drawCentered\", ");
    j += F("\"params\": [");
    j += F("\"int\"");
    j += F(", ");
    j += F("\"const char*\"");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"BATTERY\", ");
    j += F("\"name\": \"begin\", ");
    j += F("\"params\": [");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"BATTERY\", ");
    j += F("\"name\": \"getVoltage\", ");
    j += F("\"params\": [");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"BATTERY\", ");
    j += F("\"name\": \"updateMeasurement\", ");
    j += F("\"params\": [");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"BATTERY\", ");
    j += F("\"name\": \"getLastResult\", ");
    j += F("\"params\": [");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"BATTERY\", ");
    j += F("\"name\": \"baslatTest\", ");
    j += F("\"params\": [");
    j += F("\"int\"");
    j += F(", ");
    j += F("\"float\"");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"BATTERY\", ");
    j += F("\"name\": \"testUpdate\", ");
    j += F("\"params\": [");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"BATTERY\", ");
    j += F("\"name\": \"getInstantReport\", ");
    j += F("\"params\": [");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"BATTERY\", ");
    j += F("\"name\": \"testRaporu\", ");
    j += F("\"params\": [");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"HELPER\", ");
    j += F("\"name\": \"wtf\", ");
    j += F("\"params\": [");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"HELPER\", ");
    j += F("\"name\": \"getFreeHeap\", ");
    j += F("\"params\": [");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"HELPER\", ");
    j += F("\"name\": \"getHelp\", ");
    j += F("\"params\": [");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"HELPER\", ");
    j += F("\"name\": \"getCommandsJSON\", ");
    j += F("\"params\": [");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"WIFI\", ");
    j += F("\"name\": \"reset\", ");
    j += F("\"params\": [");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"WIFI\", ");
    j += F("\"name\": \"connect\", ");
    j += F("\"params\": [");
    j += F("\"String\"");
    j += F(", ");
    j += F("\"String\"");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"WIFI\", ");
    j += F("\"name\": \"restart\", ");
    j += F("\"params\": [");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"WIFI\", ");
    j += F("\"name\": \"getIP\", ");
    j += F("\"params\": [");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"WIFI\", ");
    j += F("\"name\": \"getMAC\", ");
    j += F("\"params\": [");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"WIFI\", ");
    j += F("\"name\": \"getSSID\", ");
    j += F("\"params\": [");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"WIFI\", ");
    j += F("\"name\": \"getPassword\", ");
    j += F("\"params\": [");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"WIFI\", ");
    j += F("\"name\": \"getStatus\", ");
    j += F("\"params\": [");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"WIFI\", ");
    j += F("\"name\": \"getStatusAll\", ");
    j += F("\"params\": [");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"WIFI\", ");
    j += F("\"name\": \"isConnected\", ");
    j += F("\"params\": [");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"TIMER\", ");
    j += F("\"name\": \"start\", ");
    j += F("\"params\": [");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"TIMER\", ");
    j += F("\"name\": \"isExpired\", ");
    j += F("\"params\": [");
    j += F("\"unsigned long\"");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"TIMER\", ");
    j += F("\"name\": \"getElapsedMillis\", ");
    j += F("\"params\": [");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"TIMER\", ");
    j += F("\"name\": \"stop\", ");
    j += F("\"params\": [");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"TIMER\", ");
    j += F("\"name\": \"reset\", ");
    j += F("\"params\": [");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"FSM\", ");
    j += F("\"name\": \"readfile\", ");
    j += F("\"params\": [");
    j += F("\"const char\"");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"FSM\", ");
    j += F("\"name\": \"writefile\", ");
    j += F("\"params\": [");
    j += F("\"const char\"");
    j += F(", ");
    j += F("\"const String\"");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"FSM\", ");
    j += F("\"name\": \"deletefile\", ");
    j += F("\"params\": [");
    j += F("\"const char\"");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"FSM\", ");
    j += F("\"name\": \"getfilelist\", ");
    j += F("\"params\": [");
    j += F("]");
    j += F("}");
    j += F(", ");
    j += F("{");
    j += F("\"module\": \"FSM\", ");
    j += F("\"name\": \"fileexists\", ");
    j += F("\"params\": [");
    j += F("\"const char\"");
    j += F("]");
    j += F("}");
    j += F("]");
    return j;
}

String HELPER::getHelp() {
    String h = F("<div style='text-align:left; font-family:sans-serif; background:#1e1e1e; padding:15px; border-radius:8px; color:#ddd; border:1px solid #333;'>");
    h += F("<h2 style='color:#4CAF50; margin-top:0;'>Remote Control Panel</h2>");
    h += F("<h3 style='color:#FF9800; border-bottom:1px solid #444; margin-bottom:10px;'>BATTERY</h3>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>begin</strong><br>");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'BATTERY begin'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>getVoltage</strong><br>");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'BATTERY getVoltage'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>updateMeasurement</strong><br>");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'BATTERY updateMeasurement'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>getLastResult</strong><br>");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'BATTERY getLastResult'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>baslatTest</strong><br>");
    h += F("<input id='input_BATTERY_baslatTest_4_0' placeholder='int' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ");
    h += F("<input id='input_BATTERY_baslatTest_4_1' placeholder='float' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'BATTERY baslatTest ' + document.getElementById('input_BATTERY_baslatTest_4_0').value + ' ' + document.getElementById('input_BATTERY_baslatTest_4_1').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>testUpdate</strong><br>");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'BATTERY testUpdate'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>getInstantReport</strong><br>");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'BATTERY getInstantReport'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>testRaporu</strong><br>");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'BATTERY testRaporu'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<h3 style='color:#FF9800; border-bottom:1px solid #444; margin-bottom:10px;'>FSM</h3>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>readfile</strong><br>");
    h += F("<input id='input_FSM_readfile_8_0' placeholder='const char' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'FSM readfile ' + document.getElementById('input_FSM_readfile_8_0').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>writefile</strong><br>");
    h += F("<input id='input_FSM_writefile_9_0' placeholder='const char' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ");
    h += F("<input id='input_FSM_writefile_9_1' placeholder='const String' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'FSM writefile ' + document.getElementById('input_FSM_writefile_9_0').value + ' ' + document.getElementById('input_FSM_writefile_9_1').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>deletefile</strong><br>");
    h += F("<input id='input_FSM_deletefile_10_0' placeholder='const char' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'FSM deletefile ' + document.getElementById('input_FSM_deletefile_10_0').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>getfilelist</strong><br>");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'FSM getfilelist'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>fileexists</strong><br>");
    h += F("<input id='input_FSM_fileexists_12_0' placeholder='const char' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'FSM fileexists ' + document.getElementById('input_FSM_fileexists_12_0').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<h3 style='color:#FF9800; border-bottom:1px solid #444; margin-bottom:10px;'>HELPER</h3>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>wtf</strong><br>");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'HELPER wtf'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>getFreeHeap</strong><br>");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'HELPER getFreeHeap'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>getHelp</strong><br>");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'HELPER getHelp'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>getCommandsJSON</strong><br>");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'HELPER getCommandsJSON'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<h3 style='color:#FF9800; border-bottom:1px solid #444; margin-bottom:10px;'>OLED</h3>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>write</strong><br>");
    h += F("<input id='input_OLED_write_17_0' placeholder='const String' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'OLED write ' + document.getElementById('input_OLED_write_17_0').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>write</strong><br>");
    h += F("<input id='input_OLED_write_18_0' placeholder='const char' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'OLED write ' + document.getElementById('input_OLED_write_18_0').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>clear</strong><br>");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'OLED clear'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>setBrightness</strong><br>");
    h += F("<input id='input_OLED_setBrightness_20_0' placeholder='int' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'OLED setBrightness ' + document.getElementById('input_OLED_setBrightness_20_0').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>getStatus</strong><br>");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'OLED getStatus'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>setCursor</strong><br>");
    h += F("<input id='input_OLED_setCursor_22_0' placeholder='int' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ");
    h += F("<input id='input_OLED_setCursor_22_1' placeholder='int' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'OLED setCursor ' + document.getElementById('input_OLED_setCursor_22_0').value + ' ' + document.getElementById('input_OLED_setCursor_22_1').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>setLineHeight</strong><br>");
    h += F("<input id='input_OLED_setLineHeight_23_0' placeholder='int' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'OLED setLineHeight ' + document.getElementById('input_OLED_setLineHeight_23_0').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>setScreenSize</strong><br>");
    h += F("<input id='input_OLED_setScreenSize_24_0' placeholder='int' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ");
    h += F("<input id='input_OLED_setScreenSize_24_1' placeholder='int' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'OLED setScreenSize ' + document.getElementById('input_OLED_setScreenSize_24_0').value + ' ' + document.getElementById('input_OLED_setScreenSize_24_1').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>setInverse</strong><br>");
    h += F("<input id='input_OLED_setInverse_25_0' placeholder='bool' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'OLED setInverse ' + document.getElementById('input_OLED_setInverse_25_0').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>drawProgressBar</strong><br>");
    h += F("<input id='input_OLED_drawProgressBar_26_0' placeholder='int' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ");
    h += F("<input id='input_OLED_drawProgressBar_26_1' placeholder='int' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ");
    h += F("<input id='input_OLED_drawProgressBar_26_2' placeholder='int' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ");
    h += F("<input id='input_OLED_drawProgressBar_26_3' placeholder='int' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ");
    h += F("<input id='input_OLED_drawProgressBar_26_4' placeholder='int' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'OLED drawProgressBar ' + document.getElementById('input_OLED_drawProgressBar_26_0').value + ' ' + document.getElementById('input_OLED_drawProgressBar_26_1').value + ' ' + document.getElementById('input_OLED_drawProgressBar_26_2').value + ' ' + document.getElementById('input_OLED_drawProgressBar_26_3').value + ' ' + document.getElementById('input_OLED_drawProgressBar_26_4').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>drawCentered</strong><br>");
    h += F("<input id='input_OLED_drawCentered_27_0' placeholder='int' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ");
    h += F("<input id='input_OLED_drawCentered_27_1' placeholder='const char*' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'OLED drawCentered ' + document.getElementById('input_OLED_drawCentered_27_0').value + ' ' + document.getElementById('input_OLED_drawCentered_27_1').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<h3 style='color:#FF9800; border-bottom:1px solid #444; margin-bottom:10px;'>SERVER</h3>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>logger</strong><br>");
    h += F("<input id='input_SERVER_logger_28_0' placeholder='String' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'SERVER logger ' + document.getElementById('input_SERVER_logger_28_0').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<h3 style='color:#FF9800; border-bottom:1px solid #444; margin-bottom:10px;'>SYSTEM</h3>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>addToQueue</strong><br>");
    h += F("<input id='input_SYSTEM_addToQueue_29_0' placeholder='String' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'SYSTEM addToQueue ' + document.getElementById('input_SYSTEM_addToQueue_29_0').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>updateQueue</strong><br>");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'SYSTEM updateQueue'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>stopQueue</strong><br>");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'SYSTEM stopQueue'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>automate</strong><br>");
    h += F("<input id='input_SYSTEM_automate_32_0' placeholder='String' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'SYSTEM automate ' + document.getElementById('input_SYSTEM_automate_32_0').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<h3 style='color:#FF9800; border-bottom:1px solid #444; margin-bottom:10px;'>TIMER</h3>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>start</strong><br>");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'TIMER start'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>isExpired</strong><br>");
    h += F("<input id='input_TIMER_isExpired_34_0' placeholder='unsigned long' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'TIMER isExpired ' + document.getElementById('input_TIMER_isExpired_34_0').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>getElapsedMillis</strong><br>");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'TIMER getElapsedMillis'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>stop</strong><br>");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'TIMER stop'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>reset</strong><br>");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'TIMER reset'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<h3 style='color:#FF9800; border-bottom:1px solid #444; margin-bottom:10px;'>WIFI</h3>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>reset</strong><br>");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'WIFI reset'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>connect</strong><br>");
    h += F("<input id='input_WIFI_connect_39_0' placeholder='String' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ");
    h += F("<input id='input_WIFI_connect_39_1' placeholder='String' style='width:80px; margin:4px; padding:4px; background:#3d3d3d; color:white; border:1px solid #555;'> ");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'WIFI connect ' + document.getElementById('input_WIFI_connect_39_0').value + ' ' + document.getElementById('input_WIFI_connect_39_1').value + ''}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>restart</strong><br>");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'WIFI restart'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>getIP</strong><br>");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'WIFI getIP'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>getMAC</strong><br>");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'WIFI getMAC'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>getSSID</strong><br>");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'WIFI getSSID'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>getPassword</strong><br>");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'WIFI getPassword'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>getStatus</strong><br>");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'WIFI getStatus'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>getStatusAll</strong><br>");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'WIFI getStatusAll'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("<div style='margin-bottom:12px; padding:8px; background:#2d2d2d; border-radius:4px;'>");
    h += F("<strong>isConnected</strong><br>");
    h += F("<button hx-post='/execute' hx-vals=\"js:{val: 'WIFI isConnected'}\" hx-target='#terminal-res' style='background:#2e7d32; color:white; border:none; padding:5px 12px; border-radius:3px; cursor:pointer;'>Run</button>");
    h += F("</div>");
    h += F("</div>");
    return h;
}

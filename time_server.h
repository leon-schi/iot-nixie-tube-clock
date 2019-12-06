#include <ESP8266WebServer.h>
#include "time_html.h"
#include "wifi_credentials.h"

#ifndef SERVER_H
#define SERVER_H

class ClockServer {
    private:
        ESP8266WebServer* server;
        ClockController* controller;

        int mode = clockMode;
    public:
        ClockServer(ClockController* c) {
            server = new ESP8266WebServer(80);
            controller = c;

            server->on("/", [this](){
                server->send(200, "text/html", steering_html);
            });

            // Mode switches
            server->on("/switch/clock", [this](){
                controller->setMode(clockMode);
                server->send(200, "text/plain", "Switched to clock mode");
            });
            server->on("/switch/stopwatch", [this](){
                controller->setMode(stopwatchMode);
                server->send(200, "text/plain", "Switched to stopwatch mode");
            });
            server->on("/switch/random", [this](){
                controller->setMode(randomMode);
                server->send(200, "text/plain", "Switched to random mode");
            });
            server->on("/switch/off", [this](){
                controller->setMode(off);
                server->send(200, "text/plain", "Switched to off mode");
            });

            // General Info
            server->on("/timezone", [this](){
                timezone_rep timezone = controller->getTimezone();
                server->send(200, "application/json", "{\"utcOffset\": " + String(timezone.utcOffset) + ", \"name\": \"" + String(timezone.name) + "\"}");
            });
            server->on("/mode", [this](){
                Mode mode = controller->getMode();
                if (mode == clockMode)
                    server->send(200, "text/plain", "clock");
                else if (mode == stopwatchMode)
                    server->send(200, "text/plain", "stopwatch"); 
                else if (mode == randomMode)
                    server->send(200, "text/plain", "random"); 
                else
                    server->send(200, "text/plain", "off");
            });
            server->on("/network", [this]() {
                server->send(200, "text/plain", SSID);
            });
            server->on("/time", [this]() {
                server->send(200, "text/plain", controller->getCurrentTime());
            });
            server->on("/sync-interval", [this]() {
                String value = String(controller->getUpdateInterval());
                server->send(200, "text/plain", value);
            });

            // Set Parameters
            server->on("/set/timezone/name", [this](){
                if (server->hasArg("plain")) {
                    timezone_rep timezone = controller->getTimezone();
                    timezone.name = server->arg("plain");
                    controller->setTimezone(timezone);
                    server->send(200, "text/plain", "success");
                }
                server->send(400, "text/plain", "value not supplied");
            });
            server->on("/set/timezone/utcOffset", [this](){
                if (server->hasArg("plain")) {
                    timezone_rep timezone = controller->getTimezone();
                    timezone.utcOffset = server->arg("plain").toInt();
                    controller->setTimezone(timezone);
                    server->send(200, "text/plain", "success");
                }
                server->send(400, "text/plain", "value not supplied");
            });
            server->on("/set/sync-interval", [this](){
                if (server->hasArg("plain")) {
                    controller->setUpdateInterval(server->arg("plain").toInt());
                    server->send(200, "text/plain", "success");
                }
                server->send(400, "text/plain", "value not supplied");
            });
            server->on("/set/random-seed", [this](){
                controller->getRandomStrategy()->init();
                server->send(200, "text/plain", "success");
            });

            // Stopwatch steering
            server->on("/stopwatch/reset", [this](){
                controller->getStopwatchStrategy()->reset();
                server->send(200, "text/plain", "stopwatch resetted");
            });
            server->on("/stopwatch/start", [this](){
                controller->getStopwatchStrategy()->start();
                server->send(200, "text/plain", "stopwatch started");
            });
            server->on("/stopwatch/stop", [this](){
                controller->getStopwatchStrategy()->stop();
                server->send(200, "text/plain", "stopwatch stopped");
            });
            server->on("/stopwatch/round", [this](){
                server->send(200, "text/plain", controller->getStopwatchStrategy()->getCurrentTime());
            });

            server->begin();
        }

        void handleClient() {
            server->handleClient();
        }
};

#endif
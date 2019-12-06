#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ShiftRegisterWriter.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <string.h>

#include "time_display.h"
#include "time_strategy.h"
#include "time_transition.h"

#ifndef CONTROLLER_H
#define CONTROLLER_H

WiFiUDP Udp;
enum Mode {clockMode, stopwatchMode, randomMode, off};

struct timezone_rep {
    int utcOffset;
    String name;
};

timezone_rep getUTCOffset() {
    // use the world time API to get the UTC offset based on the ip
    HTTPClient http;
    timezone_rep timezone;
    timezone.utcOffset = 0;
    timezone.name = "Europe/London";

    http.begin("http://worldtimeapi.org/api/ip");
    int status = http.GET();
    if (status == 200) {
        String payload = http.getString();
        StaticJsonDocument<1000> doc;
        DeserializationError error = deserializeJson(doc, payload);
        if (error) {
            Serial.println(error.c_str());    
            return timezone;
        }
        
        timezone.utcOffset = (int)doc["raw_offset"];
        timezone.name = String((const char*)doc["timezone"]);
    }

    return timezone;
}

class ClockController {
    private:
        int bitsPerDigit = 4;

        NTPClient* timeClient;
        ShiftRegisterWriter* writer;
        Display display;

        OffStrategy offStrategy;
        ClockStrategy clockStrategy;
        StopwatchStrategy stopwatchStrategy;
        RandomStrategy randomStrategy;
        Strategy* activeStrategy;

        FiveTransition fiveTransition;
        SingularFiveTransition singularFiveTransition;
        Transition* activeTransition;

        Mode mode;
        timezone_rep timezone;
        unsigned long updateInterval;

        void writeCurrentDisplayState() {
            for (int i = 0; i < 6; i++)
                writer->setBinary(display.getDigit(i), 8 + 4*i, bitsPerDigit);
            writer->setBit(6, display.separators[0]);
            writer->setBit(7, display.separators[1]);
            writer->write();
        }

        void changeStrategy(Strategy* strategy) {
            activeStrategy = strategy;
            activeTransition->switchToStrategy(activeStrategy, timeClient);
        }
    public:
    
        ClockController(int dataPin, int clockPin, int confirmPin, int bitsAvailable) {
            updateInterval = 30000;
            timezone = getUTCOffset();
            timeClient = new NTPClient(Udp, "de.pool.ntp.org", timezone.utcOffset, updateInterval);
            writer = new ShiftRegisterWriter(dataPin, clockPin, confirmPin, bitsAvailable);
            timeClient->begin();
            
            mode = clockMode;
            activeStrategy = &clockStrategy;
            activeTransition = &fiveTransition;

            activeTransition->setStrategy(activeStrategy);
        }

        void update() {
            timeClient->update();
            activeTransition->update(timeClient, &display);
            writeCurrentDisplayState();
        }

        Mode getMode() {return mode;}
        void setMode(Mode newMode) {
            if (mode != newMode) {
                mode = newMode;
                switch (newMode) {
                    case clockMode:
                        clockStrategy.init();
                        changeStrategy(&clockStrategy);
                        break;
                    case stopwatchMode:
                        changeStrategy(&stopwatchStrategy);
                        break;
                    case randomMode:
                        changeStrategy(&randomStrategy);
                        break;
                    case off:
                        changeStrategy(&offStrategy);
                        break;
                }
            }
        }

        StopwatchStrategy* getStopwatchStrategy() {return &stopwatchStrategy;}
        RandomStrategy* getRandomStrategy() {return &randomStrategy;}

        timezone_rep getTimezone() {return timezone;}
        void setTimezone(timezone_rep timezone) {
            this->timezone = timezone;
            timeClient->setTimeOffset(timezone.utcOffset);
        }

        unsigned long getUpdateInterval() {return updateInterval;}
        void setUpdateInterval(unsigned long updateInterval) {
            this->updateInterval = updateInterval;
            timeClient->setUpdateInterval(updateInterval);
        }

        String getCurrentTime() {
            return String(timeClient->getHours()) + ":" + String(timeClient->getMinutes()) + ":" + String(timeClient->getSeconds());
        }
};

#endif
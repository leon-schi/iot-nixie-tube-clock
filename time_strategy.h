#include <Arduino.h>
#include <NTPClient.h>
#include "time_display.h"

#ifndef STRATEGY_H
#define STRATEGY_H

class Strategy {
    public:
        virtual void update(NTPClient* timeClient, Display* display) = 0;
};

class OffStrategy: public Strategy {
    public:
        virtual void update(NTPClient* timeClient, Display* display) {
            for (int i = 0; i < 6; i++)
                display->setDigit(i, 10);
            display->separatorsOn(0);
        }
};

class RandomStrategy: public Strategy {
    private:
        int ticks = 0;
        int speed[6];
        int interval[6];
        int leftSeparatorSpeed, rightSeparatorSpeed;
    public:
        RandomStrategy() {
            init();
        }

        void init() {
            for (int i = 0; i < 6; i++) {
                speed[i] = random(1, 10);
                interval[i] = random(-4, 4);
            }
            leftSeparatorSpeed = random(5, 30);
            rightSeparatorSpeed = random(5, 30);
        }
    
        virtual void update(NTPClient* timeClient, Display* display) {
            for (int i = 0; i < 6; i++) {
                if (ticks % speed[i] == 0) {
                    int value = display->getDigit(i);
                    display->setDigit(i, (value + interval[i]) % 10);
                }
            }

            if (ticks % leftSeparatorSpeed == 0)
                display->toggleLeftSeparator();

            if (ticks % rightSeparatorSpeed == 0)
                display->toggleRightSeparator();

            ticks++;
        }
};

class ClockStrategy: public Strategy {
    private:
        int ticks = 0;
    public:
        void init() {ticks = 30;}
        virtual void update(NTPClient* timeClient, Display* display) {
            if (display->getSeconds() != timeClient->getSeconds())
                ticks = 0;

            display->setSeconds(timeClient->getSeconds());
            display->setMinutes(timeClient->getMinutes());
            display->setHours(timeClient->getHours());

            if (ticks < 16)
                display->separatorsOn(1);
            else
                display->separatorsOn(0);
            ticks += 1;
        }
};

class StopwatchStrategy: public Strategy {
    private:
        bool running = false;
        _time_t started, elapsed = 0;
        int minutes_ = 0, seconds_ = 0, milliseconds_ = 0;
    public:
        virtual void update(NTPClient* timeClient, Display* display) {
            if (running) {
                elapsed = millis() - started;

                if (display->getSeconds() < 30)
                    display->separatorsOn(1);
                else
                    display->separatorsOn(0);
            } else {
                display->separatorsOn(0);
            }

            minutes_ = minutes(elapsed);
            seconds_ = seconds(elapsed);
            milliseconds_ = milliseconds(elapsed)/10;

            display->setSeconds(milliseconds_);
            display->setMinutes(seconds_);
            display->setHours(minutes_);
        }

        void reset() {
            elapsed = 0;
            started = millis();
        }
 
        void start() {
            running = true;
            started = millis() - elapsed;
        }

        void stop() {
            running = false;
        }

        String getCurrentTime() {
            return String(minutes_) + ":" + String(seconds_) + ":" + String(milliseconds_);
        }
};

#endif
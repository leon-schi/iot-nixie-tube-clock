
#ifndef DISPLAY_H
#define DISPLAY_H

class Display {
    private:
        int firstDigit(int value) {return value / 10;}
        int secondDigit(int value) {return value % 10;}
        int digitsToValue(int index) {
            if (index < 5 && index >= 0)
                return digits[index]*10 + digits[index + 1];
            return 0;
        }
    public:
        int digits[6] = {0};
        int separators[2];
        int seconds, minutes, hours;

        Display() {
            seconds = 0;
            minutes = 0;
            hours = 0;
            separatorsOn(0);
        }

        void separatorsOn(int state) {
            separators[0] = state;
            separators[1] = state;
        }

        void toggleLeftSeparator() {
            separators[0] = !separators[0];
        }

        void toggleRightSeparator() {
            separators[1] = !separators[1];
        }

        void setDigit(int index, int value) {
            if (index < 6)
                digits[index] = value;
        }

        int getDigit(int index) {
            if (index < 6)
                return digits[index];
            return 0;
        }

        void setSeconds(int value) {
            setDigit(4, firstDigit(value));
            setDigit(5, secondDigit(value));
        }

        void setMinutes(int value) {
            setDigit(2, firstDigit(value));
            setDigit(3, secondDigit(value));
        }

        void setHours(int value) {
            setDigit(0, firstDigit(value));
            setDigit(1, secondDigit(value));
        }

        int getSeconds() {
            return digitsToValue(4);
        }

        int getMinutes() {
            return digitsToValue(2);
        }

        int getHours() {
            return digitsToValue(0);
        }
};

#define MILLIS_PER_SEC (1000UL)
#define SECS_PER_MIN   (60UL)
#define SECS_PER_HOUR  (3600UL)

typedef unsigned long _time_t;
int milliseconds(_time_t t) {return (int)(t % MILLIS_PER_SEC);}
int seconds(_time_t t) {return (int)(t / MILLIS_PER_SEC % SECS_PER_MIN);}
int minutes(_time_t t) {return (int)(t / (MILLIS_PER_SEC * SECS_PER_MIN) % SECS_PER_MIN);}

#endif
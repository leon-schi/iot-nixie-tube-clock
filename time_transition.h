#ifndef TRANSITION_H
#define TRANSITION_H

class Transition: public Strategy {
    protected:
        Strategy* strategy;
        Display strategyDisplay;
        bool isActive = false;
    public:
        virtual void transition(Display* display) {};

        virtual void update(NTPClient* timeClient, Display* display) {
            if (isActive) {
                transition(display);
            } else {
                strategy->update(timeClient, display);
            }
        }

        virtual void setStrategy(Strategy* s) {
            strategy = s;
        }

        virtual void switchToStrategy(Strategy* s, NTPClient* timeClient) {
            strategy = s;
            strategy->update(timeClient, &strategyDisplay);
            isActive = true;
        }
};

#define FORWARD  0
#define BACKWARD 1

class FiveTransition: public Transition {
    private:
        int mode, ticks;

        int stepDigitTowardsTarget(int i, int target, Display* display) {
            int digitValue = display->getDigit(i);
            int newValue = digitValue;
            
            if (digitValue < target)
                newValue = digitValue + 1;
            else if (digitValue > target)
                newValue = digitValue - 1;

            display->setDigit(i, newValue);
            return newValue;
        }

        void forward(Display* display) {
            int doneDigits = 0;
            for (int i = 0; i < 6; i++) {
                if (stepDigitTowardsTarget(i, 5, display) == 5)
                    doneDigits++;
            }
            if (doneDigits == 6)
                mode = BACKWARD;
        }

        void backward(Display* display) {
            int doneDigits = 0;
            for (int i = 0; i < 6; i++) {
                int targetValue = strategyDisplay.getDigit(i);
                if (stepDigitTowardsTarget(i, targetValue, display) == targetValue)
                    doneDigits++;
            }
            if (doneDigits == 6)
                isActive = false;
        }
    public:
        virtual void transition(Display* display) {
            switch (mode) {
                case FORWARD:
                    forward(display);
                    break;
                case BACKWARD:
                    backward(display);
                    break;
            }

            ticks++;
        }

        virtual void switchToStrategy(Strategy* s, NTPClient* timeClient) {
            Transition::switchToStrategy(s, timeClient);
            mode = FORWARD;
            ticks = 0;
        }
};

class SingularFiveTransition: public Transition {
    private:
        bool digitForward[6];
        int stepDigitTowardsTarget(int i, int target, Display* display) {
            int digitValue = display->getDigit(i);
            int newValue = digitValue;
            
            if (digitValue < target)
                newValue = digitValue + 1;
            else if (digitValue > target)
                newValue = digitValue - 1;

            display->setDigit(i, newValue);
            return newValue;
        }
    public:
        virtual void transition(Display* display) {
            int doneDigits = 0;

            for (int i = 0; i < 6; i++) {
                if (digitForward[i]) {
                    if (stepDigitTowardsTarget(i, 5, display) == 5)
                        digitForward[i] = false;
                }
                else {
                    int targetValue = strategyDisplay.getDigit(i);
                    if (stepDigitTowardsTarget(i, targetValue, display) == targetValue)
                        doneDigits++;
                }
            }
            
            if (doneDigits >= 6)
                isActive = false;
        }

        virtual void switchToStrategy(Strategy* s, NTPClient* timeClient) {
            Transition::switchToStrategy(s, timeClient);
            for (int i = 0; i < 6; i++)
                digitForward[i] = true;
        }
};

#endif
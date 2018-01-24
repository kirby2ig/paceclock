#ifndef PACECLOCK_H
#define PACECLOCK_H

#include "Arduino.h"
#include "clockface.h"

    typedef enum paceclockstate
    {
        PACE,
        MEET
    } paceclockstate;

    class paceclock
    {
        private:
            paceclockstate state; 
            int seconds;
            int minutes;
            int event;
            int heat;
            int modeSwitchPin;
            int evtUpPin;
            int evtDwnPin;
            int heatUpPin;
            int heatDwnPin;
            int paceclockPin;
            int dataPin;
            int latchPin;
            bool evtUp;
            bool evtDwn;
            bool heatUp;
            bool heatDwn;
            bool lastEvtUp;
            bool lastEvtDwn;
            bool lastHeatUp;
            bool lastHeatDwn;
            void checkState();
            void checkButtons();
            clockface face;
        public:
            paceclock(int modeSwitchPin, int evtUpPin, int evtDwnPin, int heatUpPin, int heatDwnPin, int latchPin, int paceclockPin, int dataPin);
            ~paceclock();
            void update();
    };

#endif
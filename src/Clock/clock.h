#ifndef CLOCK_H
#define CLOCK_H

#include "Arduino.h"
#include "clockface.h"

    typedef enum clockstate
    {
        PACE,
        MEET
    } clockstate;

    class clock
    {
        private:
            clockstate state; 
            int seconds;
            int minutes;
            int event;
            int heat;
            int modeSwitchPin;
            int evtUpPin;
            int evtDwnPin;
            int heatUpPin;
            int heatDwnPin;
            int clockPin;
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
            clock(int modeSwitchPin, int evtUpPin, int evtDwnPin, int heatUpPin, int heatDwnPin, int latchPin, int clockPin, int dataPin);
            ~clock();
            void update();
    };

#endif
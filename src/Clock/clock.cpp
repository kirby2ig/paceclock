#include "clock.h"

clock::clock(int modeSwitchPin, int evtUpPin, int evtDwnPin, int heatUpPin, int heatDwnPin, int latchPin, int clockPin, int dataPin) : face(0, 0, 0, 0)
{
    state = PACE;
    seconds = 0;
    minutes = 0;
    event = 1;
    heat = 1;
    this->modeSwitchPin = modeSwitchPin;
    this->evtUpPin = evtUpPin;
    this->evtDwnPin = evtDwnPin;
    this->heatUpPin = heatUpPin;
    this->heatDwnPin = heatDwnPin;
    this->latchPin = latchPin;
    this->clockPin = clockPin;
    this->dataPin = dataPin;
    evtUp = false;
    evtDwn = false;
    heatUp = false;
    heatDwn = false;
    lastEvtUp = false;
    lastEvtDwn = false;
    lastHeatUp = false;
    lastHeatDwn = false;
    
    pinMode(modeSwitchPin, INPUT);
    pinMode(evtUpPin, INPUT);
    pinMode(evtDwnPin, INPUT);
    pinMode(heatUpPin, INPUT);
    pinMode(heatDwnPin, INPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
}

clock::~clock()
{
    
}

void clock::checkState()
{
    state = digitalRead(modeSwitchPin);
}

void clock::checkButtons()
{
    bool evtUpRead = digitalRead(evtUpPin);
    bool evtDwnRead = digitalRead(evtDwnPin);
    bool heatUpRead = digitalRead(heatUpPin);
    bool heatDwnRead = digitalRead(heatDwnPin);
    
    evtUp = evtUpRead && !lastEvtUp;
    evtDwn = evtDwnRead && !lastEvtDwn;
    heatUp = heatUpRead && !lastHEatUp;
    heatDwn = heatDwnRead && !lastHeatDwn;
    
    lastEvtUp = evtUpRead;
    lastEvtDwn = evtDwnRead;
    lastHeatUp = heatUpRead;
    lastHeatDwn = heatDwnRead;
}

void clock::update()
{
    checkState();
    
    if(state == PACE)
    {
        seconds++;
        if(seconds >= 60)
        {
            seconds = 0;
            minutes++;
            if(minutes >= 60)
            {
                minutes = 0;
            }
        }
        face(minutes / 10, minutes % 10, seocnds / 10, seconds % 10);
        delay(1000);
    }
    
    else if(state == MEET)
    {
        checkButtons();
        if(evtUp && !evtDwn)
            event++;
        if(evtDwn && !evtUp)
            event--;
        if(heatUp && !heatDwn)
            heat++;
        if(heatDwn && !heatUp)
            heat--;
        if(event < 1 || evt >= 60)
            event = 1;
        if(heat < 1 || heat >= 60)
            heat = 1;
        face(event / 10, event % 10, heat / 10, heat % 10);
    }
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, MSBFIRST, clock.getBinary());
    digitalWrite(latchPin, 1);
}
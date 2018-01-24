#include "paceclock.h"

paceclock::paceclock(int modeSwitchPin, int evtUpPin, int evtDwnPin, int heatUpPin, int heatDwnPin, int latchPin, int paceclockPin, int dataPin) : face(0, 0, 0, 0)
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
    this->paceclockPin = paceclockPin;
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
    pinMode(paceclockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
}

paceclock::~paceclock()
{
    
}

void paceclock::checkState()
{
    state = digitalRead(modeSwitchPin);
}

void paceclock::checkButtons()
{
    bool evtUpRead = digitalRead(evtUpPin);
    bool evtDwnRead = digitalRead(evtDwnPin);
    bool heatUpRead = digitalRead(heatUpPin);
    bool heatDwnRead = digitalRead(heatDwnPin);
    
    evtUp = evtUpRead && !lastEvtUp;
    evtDwn = evtDwnRead && !lastEvtDwn;
    heatUp = heatUpRead && !lastHeatUp;
    heatDwn = heatDwnRead && !lastHeatDwn;
    
    lastEvtUp = evtUpRead;
    lastEvtDwn = evtDwnRead;
    lastHeatUp = heatUpRead;
    lastHeatDwn = heatDwnRead;
}

void paceclock::update()
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
        face.setDigit(0, minutes / 10);
        face.setDigit(1, minutes % 10);
        face.setDigit(2, seconds / 10);
        face.setDigit(3, seconds % 10);
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
        if(event < 1 || event >= 60)
            event = 1;
        if(heat < 1 || heat >= 60)
            heat = 1;
        face.setDigit(0, event / 10);
        face.setDigit(1, event % 10);
        face.setDigit(2, heat / 10);
        face.setDigit(3, heat % 10);
    }
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, paceclockPin, MSBFIRST, face.getBinary());
    digitalWrite(latchPin, 1);
}
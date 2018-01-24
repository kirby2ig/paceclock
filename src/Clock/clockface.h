#ifndef CLOCKFACE_H
#define CLOCKFACE_H

#include "Arduino.h"

    class clockface
    {
        private:
            byte digits[4];
        public:
            clockface(byte digit1, byte digit2, byte digit3, byte digit4);
            unsigned long getBinary();
    };

#endif
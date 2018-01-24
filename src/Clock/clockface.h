#ifndef CLOCKFACE_H
#define CLOCKFACE_H

#include "Arduino.h"

    class clockface
    {
        private:
            int digits[4];
        public:
            clockface(int digit1, int digit2, int digit3, int digit4);
            unsigned long getBinary();
    };

#endif
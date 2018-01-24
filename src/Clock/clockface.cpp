#include "clockface.h"

clockface::clockface(byte digit1, byte digit2, byte digit3, byte digit4)
{
    digits[0] = digit1;
    digits[1] = digit2;
    digits[2] = digit3;
    digits[3] = digit4;
}

unsigned long clockface::getBinary()
{
    unsigned long digtBins[] = {119, 18, 93, 91, 58, 107, 111, 82, 127, 122};
    unsigned long result = 0;
    for(int i = 0; i < 4; i++)
    {
        int shift = 4 + 7 * (3 - i);
        unsigned long digitBin;
        int digit = digits[i];
        digitBin = digitBins[digit];
        digitBin << shift;
        result |= digitBin;
    }
    return ~ result;
}
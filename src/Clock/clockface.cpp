#include "clockface.h"

clockface::clockface(int digit1, int digit2, int digit3, int digit4)
{
    digits[0] = digit1;
    digits[1] = digit2;
    digits[2] = digit3;
    digits[3] = digit4;
}

unsigned long clockface::getBinary()
{
    unsigned long digitBins[] = {119, 18, 93, 91, 58, 107, 111, 82, 127, 122};
    unsigned long result = 0;
    for(int i = 0; i < 4; i++)
    {
        int shift = 4 + 7 * (3 - i);
        unsigned long digitBin;
        int digit = digits[i];
        digitBin = digitBins[digit];
        result |= digitBin << shift;
    }
    return ~ result;
}

void clockface::setDigit(int index, int value)
{
    if(index < 0 || index > 3)
        return;
    digits[index] = value;
}
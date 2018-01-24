#include "paceclock.h"

paceclock pc(2, 3, 4, 5, 6, 8, 12, 11);

void setup()
{
    
}

void loop()
{
    pc.update();
}
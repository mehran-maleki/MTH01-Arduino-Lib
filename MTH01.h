#ifndef MTH01_H
#define MTH01_H

#include "Arduino.h"

class MTH01
{
private:

public:
    MTH01(/* args */);
    float getTemperature();
    byte getHumidity();
    void begin(int cs_pin);
};

#endif
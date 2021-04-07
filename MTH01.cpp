#include "Arduino.h"
#include "MTH01.h"
#include "pins_arduino.h"


unsigned char buf[7];
volatile byte pos;
volatile boolean process_it;
float MTH_temperature;
byte MTH_humidity;

MTH01::MTH01()
{
    SPCR |= _BV(SPE); // turn on SPI in slave mode - get ready for an interrupt
    pos = 0;          // empty buffer
    process_it = false;
    SPCR |= _BV(SPIE); // now turn on interrupts
}

void MTH01::begin(int cs_pin){
    pinMode(cs_pin, OUTPUT);
    digitalWrite(cs_pin, LOW);
    delay(2000);
}

// SPI interrupt routine
ISR(SPI_STC_vect)
{
    byte c = SPDR;        // grab byte from SPI Data Register
    if (pos < sizeof buf) // add to buffer if room
    {
        buf[pos++] = c;
        if (pos >= 4) // when all 4 bytes received
        {
            process_it = true; // signal ready to main loop
        }
    }

    if (process_it)
    {
        MTH_temperature = ((256 * buf[0]) + buf[1]) - 400;
        MTH_temperature = MTH_temperature / 10;
        MTH_humidity = buf[2];

        pos = 0;            // reset buffer index
        process_it = false; // preset buffer not ready
    }
}

float MTH01::getTemperature()
{
    return MTH_temperature;
}

byte MTH01::getHumidity()
{
    return MTH_humidity;
}
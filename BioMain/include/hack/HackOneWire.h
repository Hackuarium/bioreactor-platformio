#include <Arduino.h>
//#include <OneWire.h>
#include "libraries/onewire/OneWire.h"

#include "Params.h"

#ifdef THR_ONEWIRE

/*******************************************
    THREAD TEMPERATURE
    This module reads the temperature of the different temperature sensors.
    The sensor is a dallas 1-wire ds18b20.

    There is only one device per plug. Instead of searching for the
    adresses of the devices, we use the skip rom command which allow
    us to directly ask any device on the line without address.

    The sequence is as follow:
    We ask the sensor to update its value :
    1. Issue a Reset pulse and observe the Presence of the thermometer
    2. Issue the Skip Rom command (0xCC)
    3. Issue the Convert T command (0×44)

    The conversion in 12 bits take 750ms, so we actually read the previous value
 :
    1. Issue a Reset pulse and observe the Presence of the thermometer
    2. Issue the Skip Rom command (0xCC)
    3. Issue the Read Scratchpad command (0xBE)
    4. Read the next two bytes which represent the temperature
 *********************************************/

void getTemperature(OneWire& ow, int, char);
void oneWireInfoSS(OneWire& ow, Print*);
// bus info function
void oneWireInfo(Print*);

#endif
#include <Arduino.h>
#include <Params.h>
#include <ChNil.h>

#if defined(I2C)

THD_WORKING_AREA(waThreadWire, 88);  // min of 64 when pH present
THD_FUNCTION(ThreadWire, arg);

#endif
#include <Arduino.h>
#include <ChNil.h>

#include "hack/Params.h"

#ifdef THR_STEPS

uint8_t getMinute();
void printBits(int);

THD_WORKING_AREA(waThreadSteps, 120);
THD_FUNCTION(ThreadSteps, arg);

#endif
#include <Arduino.h>
#include <ChNil.h>

#include "hack/BioParams.h"

#ifdef THR_STEPS

uint8_t getMinute();
void printBits( int );

THD_WORKING_AREA( waThreadSteps, 100 );
THD_FUNCTION(ThreadSteps, arg);

#endif
#include <Arduino.h>
#include <ChNil.h>

#include "hack/Params.h"

#ifdef THR_WEIGHT

THD_WORKING_AREA(waThreadWeight, 56);  // minimum of 32 !
THD_FUNCTION(ThreadWeight, arg);

#endif
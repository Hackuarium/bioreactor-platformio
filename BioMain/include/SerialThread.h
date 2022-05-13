#include <Arduino.h>
#include <ChNil.h>

#include "hack/Params.h"

#ifdef THR_SERIAL

THD_WORKING_AREA(waThreadSerial, 96);  // minimum 96
THD_FUNCTION(ThreadSerial, arg);

#endif
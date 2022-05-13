#include <ChNil.h>

#include "hack/HackOneWire.h"

#ifdef THR_ONEWIRE

THD_WORKING_AREA(waThreadOneWire, 150);  // should be 50 without Serial.println
THD_FUNCTION(ThreadOneWire, arg);

#endif
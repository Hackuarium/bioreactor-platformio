#include <ChNil.h>

#include "hack/BioOneWire.h"

#ifdef THR_ONEWIRE

THD_WORKING_AREA( waThreadOneWire, 170 );  // should be 50 without Serial.println
THD_FUNCTION( ThreadOneWire, arg );

#endif
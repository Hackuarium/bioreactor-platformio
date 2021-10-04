#include <ChNil.h>

#include "BioOneWire.h"

#ifdef THR_ONEWIRE

THD_WORKING_AREA( waThreadOneWire, 180 );  // should be 50 without Serial.println
THD_FUNCTION( ThreadOneWire, arg );

#endif
#include <Arduino.h>
#include <ChNil.h>

#include "BioParams.h"

#ifdef THR_OUTPUTS

THD_WORKING_AREA(waThreadOutputs, 0); 
THD_FUNCTION( ThreadOutputs, arg );

#endif
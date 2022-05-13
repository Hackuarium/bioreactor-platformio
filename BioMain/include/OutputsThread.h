#include <Arduino.h>
#include <ChNil.h>

#include "hack/Params.h"

#ifdef THR_OUTPUTS

THD_WORKING_AREA(waThreadOutputs, 0);
THD_FUNCTION(ThreadOutputs, arg);

#endif
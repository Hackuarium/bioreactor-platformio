#include <Arduino.h>
#include <ChNil.h>

//#include "BioParams.h"
#include "hack/BioParams.h"

#ifdef THR_ERROR

THD_WORKING_AREA(waThreadError,
                 0);  // tune the allocated mem (here extra is provided)
THD_FUNCTION(ThreadError, arg);

#endif
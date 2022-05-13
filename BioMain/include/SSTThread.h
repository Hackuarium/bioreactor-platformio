#include "hack/Params.h"

#ifdef THR_SST_LOGGER

#include <ChNil.h>
#ifdef LOG_INTERVAL

#ifdef DEBUG_LOGS
THD_WORKING_AREA(waThreadLogger, 128);
#else
THD_WORKING_AREA(waThreadLogger, 64);
#endif

THD_FUNCTION(ThreadLogger, arg);

#endif

#endif
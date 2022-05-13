
/***********************************************************
                Watchdog, Autoreboot Thread
Monitor the activity. Should be the lower priority process
If the led is "stable" (blinks 500 times per seconds),
there are not too many activities on the microcontroler
************************************************************/
#include <Arduino.h>
#include <ChNil.h>

#include "Params.h"

#ifdef THR_MONITORING

THD_WORKING_AREA(waThreadMonitoring, 0);
THD_FUNCTION(ThreadMonitoring, arg);

#endif
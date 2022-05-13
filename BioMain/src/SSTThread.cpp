#include <Arduino.h>
#include <ChNil.h>

#include "Params.h"

#ifdef THR_SST_LOGGER

//#include "SSTLogger.h"
#include <hack/SSTLogger.h>
#ifdef LOG_INTERVAL

THD_FUNCTION(ThreadLogger, arg) {
  chThdSleep(5000);
  writeLog(EVENT_ARDUINO_BOOT, 0);
  chThdSleepSeconds((long)LOG_INTERVAL - (long)(millis() / 1000UL) + 5UL);
  while (TRUE) {
    // avoids logging during the second x+1, ensure x+LOG_INTERVAL
    // because epoch is only precise to the second so the logging is evenly
    // spaced
    // unsigned long waiting = (unsigned long)LOG_INTERVAL - (millis() % 1000UL);
    // chThdSleep((long)LOG_INTERVAL * 1000UL - millis() % 1000UL + 100UL);
    writeLog(0, 0);
    chThdSleepSeconds(LOG_INTERVAL);
  }
}

#endif

#endif
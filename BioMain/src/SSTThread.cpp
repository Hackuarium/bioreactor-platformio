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
  while (TRUE) {
    // avoids logging during the second x+1, ensure x+LOG_INTERVAL
    // because epoch is only precise to the second so the logging is evenly
    // spaced
    chThdSleep(LOG_INTERVAL * 1000 - millis() % 1000 + 100);
    writeLog(0, 0);
  }
}

#endif

#endif
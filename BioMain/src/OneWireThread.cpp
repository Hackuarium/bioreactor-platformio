#include <Arduino.h>
#include <ChNil.h>

#include "HackOneWire.h"
#include "Params.h"

#ifdef THR_ONEWIRE

#ifdef TEMP_EXT1
OneWire oneWire1T(TEMP_EXT1);
#endif

#ifdef TEMP_EXT2
OneWire oneWire2T(TEMP_EXT2);
#endif

#ifdef TEMP_PCB
OneWire oneWire3T(TEMP_PCB);
#endif

THD_FUNCTION(ThreadOneWire, arg) {
  chThdSleep(200);

  while (true) {
#ifdef TEMP_EXT1
    getTemperature(oneWire1T, PARAM_TEMP_EXT1, FLAG_TEMP_EXT1_PROBE_ERROR);
#endif

#ifdef TEMP_EXT2
    getTemperature(oneWire2T, PARAM_TEMP_EXT2, FLAG_TEMP_EXT2_PROBE_ERROR);
#endif

#ifdef TEMP_PCB
    getTemperature(oneWire3T, PARAM_TEMP_PCB, FLAG_TEMP_PCB_PROBE_ERROR);
#endif
    chThdSleep(200);
  }
}

#endif
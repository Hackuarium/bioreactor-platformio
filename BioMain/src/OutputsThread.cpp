#include <Arduino.h>
#include <ChNil.h>

#include "Params.h"
#include "Status.h"

#if defined(THR_OUTPUTS)

THD_FUNCTION(ThreadOutputs, arg) {
  chThdSleep(2234);  // wait a little bit not everything starts at once

  while (true) {
    chThdSleep(1000);

#ifdef OUT_1
    pinMode(OUT_1, OUTPUT);
    digitalWrite(OUT_1, isEnabled(FLAG_OUTPUT_1) && getStatus(FLAG_OUTPUT_1));
    // digitalWrite(OUT_1, getStatus(FLAG_FOOD_CONTROL) &&
    // isEnabled(FLAG_OUTPUT_1) && getStatus(FLAG_RELAY_FILLING));
#endif
#ifdef OUT_2
    pinMode(OUT_2, OUTPUT);
    digitalWrite(OUT_2, getStatus(FLAG_OUTPUT_2) && isEnabled(FLAG_OUTPUT_2));
    // digitalWrite(OUT_2, getStatus(FLAG_FOOD_CONTROL) &&
    // isEnabled(FLAG_OUTPUT_2) && getStatus(FLAG_RELAY_EMPTYING));
#endif
#ifdef OUT_3
    pinMode(OUT_3, OUTPUT);
    digitalWrite(OUT_3, getStatus(FLAG_OUTPUT_3) && isEnabled(FLAG_OUTPUT_3));
#endif
#ifdef OUT_4
    pinMode(OUT_4, OUTPUT);
    digitalWrite(OUT_4, getStatus(FLAG_OUTPUT_4) && isEnabled(FLAG_OUTPUT_4));
#endif
  }
}

#endif
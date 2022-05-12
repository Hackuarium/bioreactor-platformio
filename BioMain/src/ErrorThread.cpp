#include <Arduino.h>
#include <ChNil.h>

#include "Params.h"
#include "Funcs.h"

#ifdef THR_ERROR

THD_FUNCTION(ThreadError, arg) {
  chThdSleep(4520);
  pinMode(OUT_ERROR, OUTPUT);
  uint8_t errorCounter = 0;
  while (true) {
    if (getParameter(PARAM_ERROR) && errorCounter % 2) {
      digitalWrite(OUT_ERROR, HIGH);
    } else {
      digitalWrite(OUT_ERROR, LOW);
    }
    errorCounter++;
    chThdSleep(1000);
  }
}

#endif
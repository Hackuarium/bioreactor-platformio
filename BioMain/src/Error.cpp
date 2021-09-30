#include <ChNil.h>

#include "BioMain.h"

THD_FUNCTION(ThreadError, arg)
{
  chThdSleep(4520);
  pinMode(OUT_ERROR, OUTPUT);
  byte errorCounter = 0;
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

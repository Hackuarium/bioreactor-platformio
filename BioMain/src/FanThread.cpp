#include <Arduino.h>
#include <Params.h>
#include <ChNil.h>
#include <Funcs.h>

#ifdef THR_FAN

/*Temperature PID Control addressing relay*/

void setFan() {
  int temperature = getParameter(PARAM_TEMP_PCB);
  if (temperature > TEMP_FAN_ON) {
    analogWrite(OUT_FAN, 255);
  } else {
    analogWrite(OUT_FAN, 0);
  }
}

THD_FUNCTION(ThreadFan, arg) {
  chThdSleep(1000);
  pinMode(OUT_FAN, OUTPUT);

  while (true) {
    setFan();
    chThdSleep(2000);
  }
}

#endif
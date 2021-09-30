#include <ChNil.h>
#include "BioMain.h"
#include "params.h"

THD_FUNCTION(ThreadFan, arg)
{
  chThdSleep(1000);
  pinMode(OUT_FAN, OUTPUT);

  while (true) {
    setFan();
    chThdSleep(2000); 
  }
}

/*Temperature PID Control addressing relay*/

void setFan() {
  int temperature = getParameter(PARAM_TEMP_PCB);
  if (temperature > 3500) {
    analogWrite(OUT_FAN, 255);
  } else {
    analogWrite(OUT_FAN, 0);
  }

}

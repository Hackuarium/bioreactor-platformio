#include <Arduino.h>
#include <Params.h>
#include <ChNil.h>

#if defined(I2C)

#include "BioI2C.h"

THD_FUNCTION(ThreadWire, arg) {
  chThdSleep(1000);

  uint8_t aByte = 0;
  uint8_t* wireFlag32 = &aByte;
  unsigned int wireEventStatus = 0;
  Wire.begin();

  chThdSleep(10000);  // wait for probe warm-up

  while (true) {
    if (wireEventStatus % 25 == 0) {
      wireUpdateList();
    }
    wireEventStatus++;

    /*********
     *  pH
     *********/

#ifdef GAS_CTRL
    getAnemometer(gas_wire_write);
#endif

#ifdef MODE_CALIBRATE  // update faster in calibration mode
    chThdSleep(100);
#else
    chThdSleep(500);
#endif
  }
}

#endif
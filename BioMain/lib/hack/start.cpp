#include <Arduino.h>
#include <ChNil.h>
#include "params.h"

void checkParameters();
void initParameters();

void start() {
  Serial.begin(115200);
  setupParameters(); // we load paramters from the EEPROM
  checkParameters(); // setup automatically the default parameter after install boot loader
  initParameters();
  chBegin();
    #ifdef THR_WIRE_SLAVE
      startWireSlave();
    #endif
}
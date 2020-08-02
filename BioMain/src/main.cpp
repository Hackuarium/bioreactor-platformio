#define SOFTWARE_VERSION "v0.0.1"

#define THR_WIRE_MASTER 1
#define THR_SST_LOGGER 1
#define THR_SERIAL 1
#define THR_ONEWIRE 1
#define THR_PID 1
#define THR_STEPPER 1
#define THR_WEIGHT 1
#define THR_PUMPS 1

#include "BioMain.h"
#include "Parameters.h"

#include "BioParams.cpp"
#include "I2C.cpp"
#include "OneWire.cpp"
#include "PID.cpp"
#include "Pumps.cpp"
#include "SerialSpecific.cpp"
#include "Stepper.cpp"
#include "Weight.cpp"
#include "StartThreads.cpp"

/*********
   SETUP
 *********/
void setup()
{
  delay(1000);
  Serial.begin(9600);
  delay(1000);
  setupParameters();

#ifdef FLASH_SELECT
  pinMode(FLASH_SELECT, OUTPUT);
  setupMemory();
  recoverLastEntryN();
  loadLastEntryToParameters(); // get back the previous config
#endif

  nilSysBegin();
}

void loop() {}
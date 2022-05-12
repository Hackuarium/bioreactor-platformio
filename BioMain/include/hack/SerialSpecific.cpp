#include <Arduino.h>
//#include <TimeLib.h>

#include "HackOneWire.h"
#include "Params.h"
#include "Funcs.h"
#include "SSTLogger.h"
#include "Weight.h"
#include "libraries/time/TimeLib.h"

#if FLASH_SELECT == 10  // Flash SS_SPI
SST sst = SST('B', 6);  // D10 is PORT B - 6
#endif
#if FLASH_SELECT == 1    // Flash SS_SPI
SST sst2 = SST('D', 3);  // TX is PORT D - 3
#endif
#if FLASH_SELECT == A3  // Flash SS_SPI
SST sst = SST('F', 4);  // A3 is PORT F - 4
#endif

void printGeneralParameters(Print* output) {
  output->print(F("EPOCH:"));
  output->println(now());
  output->print(F("millis:"));
  output->println(millis());
#ifdef THR_SST_LOGGER
  output->print(F("Next log index:"));
  output->println(nextEntryID);
  output->print(F("FlashID:"));
  sst2.printFlashID(output);
#endif
}

void processSpecificCommand(char* data, char* paramValue, Print* output) {
  switch (data[0]) {
#ifdef THR_SST_LOGGER
    case 'l':
      processLoggerCommand(data[1], paramValue, output);
      break;
#endif
#if THR_ONEWIRE
    case 'o':
      oneWireInfo(output);
#endif
      break;
    case 'p':
      printGeneralParameters(output);
      break;
    case 't':
      output->print(F("Status: "));
      output->println(getParameter(PARAM_STATUS), BIN);
      for (byte i = 0; i < 11; i++) {
        output->print(i);
        output->print(": ");
        output->println(getParameterBit(PARAM_STATUS, i));
      }
      output->print(F("Enabled: "));
      output->println(getParameter(PARAM_ENABLED), BIN);
      for (byte i = 0; i < 6; i++) {
        output->print(i);
        output->print(": ");
        output->println(getParameterBit(PARAM_ENABLED, i));
      }
      output->print(F("Error: "));
      output->println(getParameter(PARAM_ERROR), BIN);
      for (byte i = 0; i < 8; i++) {
        output->print(i);
        output->print(": ");
        output->println(getParameterBit(PARAM_ERROR, i));
      }
      break;
#ifdef THR_WEIGHT
    case 'w':
      processWeightCommand(data[1], paramValue, output);
      break;
#endif
  }
}

void printSpecificHelp(Print* output) {
#ifdef THR_SST_LOGGER
  output->println(F("(l)og"));
#endif
#ifdef THR_ONEWIRE
  output->println(F("(o)ne-wire"));
#endif
  output->println(F("(p)aram"));
  output->println(F("s(t)atus"));
#ifdef THR_WEIGHT
  output->println(F("(w)eight"));
#endif
}

#include <Arduino.h>
#include <ChNil.h>
//#include <TimeLib.h>
#include <avr/eeprom.h>

#include "libraries/time/TimeLib.h"

#include "BioParams.h"
#include "ToHex.h"
#include "EEPROMHack.h"
#include "SSTLogger.h"

#ifdef THR_EEPROM_LOGGER
  #include "EEPROMLogger.h"
#endif

int parameters[MAX_PARAM];

bool getParameterBit(uint8_t number, uint8_t bitToRead) {
  return (parameters[number] >> bitToRead ) & 1;
}

bool setParameterBit(uint8_t number, uint8_t bitToSet) {
  if (getParameterBit(number, bitToSet)) return false;
  parameters[number] |= 1 << bitToSet;
  return true;
}

bool clearParameterBit(uint8_t number, uint8_t bitToClear) {
  if (! getParameterBit(number, bitToClear)) return false;
  parameters[number] &=  ~ (1 << bitToClear);
  return true;
}

void toggleParameterBit(uint8_t number, uint8_t bitToToggle) {
  parameters[number] ^= 1 << bitToToggle;
}

void setupParameters() {
  //We copy all the values in the parameters table
  eeprom_read_block((void*)parameters, (const void*)EE_START_PARAM, MAX_PARAM * 2);
}

int getParameter(uint8_t number) {
  return parameters[number];
}

void setParameter(uint8_t number, int value) {
  parameters[number] = value;
}

void incrementParameter(uint8_t number) {
  parameters[number]++;
}

void saveParameters() {
  for (uint8_t i = 0; i < MAX_PARAM; i++) {
    eeprom_write_word((uint16_t*) EE_START_PARAM + i, parameters[i]);
  }
  #ifdef EVENT_LOGGING
    #ifdef THR_EEPROM_LOGGER
    writeLog();
    #else
    writeLog(EVENT_SAVE_ALL_PARAMETER, 0);
    #endif
  #endif
}

/*
  This will take time, around 4 ms
  This will also use the EEPROM that is limited to 100000 writes
*/
void setAndSaveParameter(uint8_t number, int value) {
  parameters[number] = value;
  //The address of the parameter is given by : EE_START_PARAM+number*2
  eeprom_write_word((uint16_t*) EE_START_PARAM + number, value);
  #ifdef EVENT_LOGGING
    #ifdef THR_EEPROM_LOGGER
    writeLog();
    #else
    writeLog(EVENT_PARAMETER_SET + number, value);
    #endif
  #endif
}

// this method will check if there was a change in the error status and log it in this case
bool saveAndLogError(boolean isError, uint8_t errorFlag) {
  if (isError) {
    if (setParameterBit(PARAM_ERROR, errorFlag)) { // the status has changed
      #ifdef EVENT_LOGGING
        #ifdef THR_EEPROM_LOGGER
        writeLog();
        #else
        writeLog(EVENT_ERROR_FAILED, errorFlag);
        #endif
      #endif
      return true;
    }
  } else {
    if (clearParameterBit(PARAM_ERROR, errorFlag)) { // the status has changed
      #ifdef EVENT_LOGGING
      #ifdef THR_EEPROM_LOGGER
        writeLog();
        #else
        writeLog(EVENT_ERROR_RECOVER, errorFlag);
        #endif
      #endif
      return true;
    }
  }
  return false;
}

void printParameter(Print* output, uint8_t number) {
  output->print(number);
  output->print("-");
  if (number > 25) {
    output->print((char)(floor(number / 26) + 64));
  }
  else {
    output->print(" ");
  }
  output->print((char)(number - floor(number / 26) * 26 + 65));
  output->print(": ");
  output->println(parameters[number]);
}

void printParameters(Print* output) {
  for (int i = 0; i < MAX_PARAM; i++) {
    printParameter(output, i);
  }
}

uint8_t printCompactParameters(Print* output, uint8_t number) {
  if (number > MAX_PARAM) {
    number = MAX_PARAM;
  }
  uint8_t checkDigit = 0;

  // we first add epoch
  checkDigit ^= toHex(output, (long)now());
  for (int i = 0; i < number; i++) {
    int value = getParameter(i);
    checkDigit ^= toHex(output, value);
  }
  checkDigit ^= toHex(output, (int)getQualifier());
  toHex(output, checkDigit);
  output->println("");
  return 1;
}

uint8_t printCompactParameters(Print* output) {
  return printCompactParameters(output, MAX_PARAM);
}


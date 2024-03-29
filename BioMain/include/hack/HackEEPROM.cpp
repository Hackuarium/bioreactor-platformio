#include <Arduino.h>
#include <ChNil.h>
#include <avr/eeprom.h>
//#include <EEPROM.h>

#include "Params.h"

/* The qualifier represents the card ID and is stored just after the last
 * parameter */
uint16_t getQualifier() {
  return eeprom_read_word((uint16_t*)(EE_QUALIFIER));
}

void setQualifier(uint16_t value) {
  eeprom_write_word((uint16_t*)(EE_QUALIFIER), value);
}

void setDataLong(int index, long value) {
  eeprom_write_dword((uint32_t*)(EEPROM_MAX_ADDR - 4 * index - 3), value);
}

long getDataLong(int index) {
  return eeprom_read_dword((uint32_t*)(EEPROM_MAX_ADDR - 4 * index - 3));
}

// code from http://www.arduino.cc/playground/Code/EepromUtil
void getStatusEEPROM(Print* output) {
  int bytesPerRow = 16;
  int i;
  int j;
  byte b;
  char buf[4];

  j = 0;

  // go from first to last eeprom address
  for (i = EEPROM_MIN_ADDR; i <= EEPROM_MAX_ADDR; i++) {
    if (j == 0) {
      sprintf(buf, "%03X", i);
      output->print(buf);
      output->print(F(": "));
    }

    // read current byte from eeprom
    b = eeprom_read_byte((uint8_t*)i);
    sprintf(buf, "%02X ", b);
    j++;
    if (j == bytesPerRow) {
      j = 0;
      output->println(buf);
      chThdSleep(25);
    } else {
      output->print(buf);
    }
  }
}

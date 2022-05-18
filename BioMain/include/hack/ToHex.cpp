#include <Arduino.h>
#include <ChNil.h>

/* Functions to convert a number to hexadeciaml */

const char hex[] = "0123456789ABCDEF";

uint8_t toHex(Print* output, byte value) {
  output->print( ( value >> 4 ) & 0x0F, HEX);
  output->print( value & 0x0F, HEX);
  return value;
}

uint8_t toHex(Print* output, int value) {
  byte checkDigit = toHex(output, (byte)( value >> 8 & 0x00FF ) );
  checkDigit ^= toHex(output, (byte)(value & 0x00FF));
  return checkDigit;
}

uint8_t toHex(Print* output, long value) {
  byte checkDigit = toHex(output, (int)( value >> 16 & 0x0000FFFF ));
  checkDigit ^= toHex(output, (int)(value & 0x0000FFFF));
  return checkDigit;
}
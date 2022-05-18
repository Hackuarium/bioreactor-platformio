#include <Arduino.h>
#include <ChNil.h>

/* Functions to convert a number to hexadeciaml */

/**
 * It takes a byte value and prints it to the output stream as a two digit
 * hexadecimal number
 * 
 * @param output the Print object to write to
 * @param value The byte to be converted to hex.
 * 
 * @return The value of the byte.
 */
uint8_t toHex(Print* output, byte value) {
  output->print( ( value >> 4 ) & 0x0F, HEX);
  output->print( value & 0x0F, HEX);
  return value;
}

/**
 * The function takes a pointer to a Print object and an integer value. It returns
 * a byte value. The function prints the hexadecimal representation of the integer
 * value to the Print object. The function returns the XOR of the two bytes that
 * make up the integer value
 * 
 * @param output the output stream to write the hex to
 * @param value The value to be converted to hex.
 * 
 * @return The check digit.
 */
uint8_t toHex(Print* output, int value) {
  byte checkDigit = toHex(output, (byte)( value >> 8 & 0x00FF ) );
  checkDigit ^= toHex(output, (byte)(value & 0x00FF));
  return checkDigit;
}

/**
 * It converts a long value to a hexadecimal string.
 * 
 * @param output The output stream to write the hexadecimal representation to.
 * @param value The value to be converted to hex.
 * 
 * @return The check digit.
 */
uint8_t toHex(Print* output, long value) {
  byte checkDigit = toHex(output, (int)( value >> 16 & 0x0000FFFF ));
  checkDigit ^= toHex(output, (int)(value & 0x0000FFFF));
  return checkDigit;
}
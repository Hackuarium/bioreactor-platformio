// code taken from
// https://github.com/Hackuarium/simple-spectro/tree/master/arduino/SimpleSpectro.
// Thread allowing serail over usb communication.

#include <Arduino.h>
#include <ChNil.h>
#include "Params.h"

#ifdef THR_SERIAL

extern char serialBuffer[SERIAL_BUFFER_LENGTH];
extern uint8_t serialBufferPosition;

void printResult(char*, Print*);
void printHelp(Print*);
void processSpecificCommand(char*, char*, Print*);
void printSpecificHelp(Print*);

/*
  SerialEvent occurs whenever a new data comes in the
  hardware serial RX.

  This method will mainly set/read the parameters:
  Uppercase + number + CR ('-' and 1 to 5 digit) store a parameter
  (0 to 25 depending the letter, starting 26 using to letter like 'AA')
  example: A100, A-1
  -> Many parameters may be set at once
  example: C10,20,30,40,50
  Uppercase + CR read the parameter
  example: A
  -> Many parameters may be read at once
  example: A,B,C,D

  It is also possible to write some data to a specific I2C device using
  nnnRRxxx where
  * nnn : the I2C device number
  * RR : the register to write as a letter: A for 0, B for 1, etc.
  * xxx : a number

  s : read all the parameters
  h : help
  l : show the log file
*/

void printResult(char*, Print*);
void printHelp(Print*);
void noThread(Print*);

#endif

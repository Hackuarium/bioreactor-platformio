#include <Arduino.h>
#include <ChNil.h>

#include "Params.h"

#if defined(I2C)

#include <Wire.h>
/*
 FLUX
 - B1011 XXX R/W  (XXX is the user defined address and R/W the read/write byte)
 --> TBD PH METER
 - B????????
 */

/********************
 * Utilities functions
 **********************/

void wireWrite(uint8_t, uint8_t);
void wireWrite(uint8_t, uint8_t, uint8_t);
uint8_t wireRead(uint8_t);
void wireInfo(Print*);
void wireUpdateList();
void wireRemoveDevice(uint8_t);
void wireInsertDevice(uint8_t, uint8_t);
bool wireDeviceExists(uint8_t);
// We will combine flags in a byte. Using pointer does not seems to improve
// memory size so we don't use pointer
void setWireFlag(uint8_t*, uint8_t);
void clearWireFlag(uint8_t*, uint8_t);
bool wireFlagStatus(uint8_t*, uint8_t);

#endif

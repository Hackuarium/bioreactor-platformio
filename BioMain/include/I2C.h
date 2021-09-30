#if defined(I2C)

#include <Arduino.h>

#include <Wire.h>
/*
 FLUX
 - B1011 XXX R/W  (XXX is the user defined address and R/W the read/write byte) --> TBD
 PH METER
 - B????????
 */

#define WIRE_MAX_DEVICES 5

byte numberI2CDevices;
byte wireDeviceID[WIRE_MAX_DEVICES];

THD_WORKING_AREA(waThreadWire, 88); //min of 64 when pH present
THD_FUNCTION(ThreadWire, arg);

/********************
 * Utilities functions 
 **********************/

void wireWrite( uint8_t, uint8_t );
void wireWrite( uint8_t, uint8_t, uint8_t );
void wireInfo( Print* );
void wireUpdateList();
void wireRemoveDevice( byte );
void wireInsertDevice( byte, byte );
bool wireDeviceExists( byte );
byte wireRead( uint8_t );

// We will combine flags in a byte. Using pointer does not seems to improve
// memory size so we don't use pointer
void setWireFlag( byte*, byte );
void clearWireFlag( byte*, byte);
bool wireFlagStatus( byte*, byte );

#endif
// setting ATmega32U4 as I2C slave.
#include <Arduino.h>

#ifdef THR_WIRE_MASTER

#ifndef I2C_HARDWARE
#define I2C_HARDWARE 1
#endif

#define I2C_TIMEOUT 10
#define I2C_SLOWMODE 1

#if I2C_HARDWARE == 1
#include "Wire.h"
TwoWire WireM;
#else
// WireM.available returns a wrong value with SoftWire when device unplugged
#include "SoftWire.h"
SoftWire WireM;
#endif

// #define WIRE_MASTER_HOT_PLUG 1  // scan for new devices preventing sleep mode
// of I2C slaves

#define WIRE_MAX_DEVICES 8
byte numberI2CDevices;
byte wireDeviceID[WIRE_MAX_DEVICES];

void wireUpdateList();

THD_WORKING_AREA(waThreadWireMaster, 200);
THD_FUNCTION(ThreadWireMaster, arg);

int wireReadInt( uint8_t );
void wireWakeup( uint8_t );
void wireSetRegister( uint8_t, uint8_t );
int wireReadIntRegister( uint8_t, uint8_t );
int wireCopyParameter( uint8_t, uint8_t, uint8_t );
void wireWriteIntRegister( uint8_t, uint8_t, int );
void printWireInfo( Print* );
void printWireDeviceParameter( Print*, uint8_t );
void wireRemoveDevice( byte );
void wireInsertDevice( byte, byte );
bool wireDeviceExists(byte id );
void wireUpdateList();
void printWireHelp( Print* );
void processWireCommand( char, char*, Print* );

#endif

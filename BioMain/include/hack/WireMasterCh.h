#include "Params.h"

// setting ATmega32U4 as I2C slave.
#ifdef THR_WIRE_SLAVE

#include <Arduino.h>
#include <ChNil.h>
#include <Wire.h>

int wireReadInt(uint8_t);
void wireWakeup(uint8_t);
void wireSetRegister(uint8_t, uint8_t);
int wireReadIntRegister(uint8_t, uint8_t);
void wireCopyParameter(uint8_t, uint8_t, uint8_t);
void wireWriteIntRegister(uint8_t, uint8_t, int);
void printWireInfo(Print*);
void printWireDeviceParameter(Print*, uint8_t);
void wireRemoveDevice(byte);
void wireInsertDevice(byte, byte);
bool wireDeviceExists(byte);
void wireUpdateList();
void printWireHelp(Print*);
void processWireCommand(char, char*, Print*);

THD_WORKING_AREA(waThreadWireMaster, 200);
THD_FUNCTION(ThreadWireMaster, arg);

#endif
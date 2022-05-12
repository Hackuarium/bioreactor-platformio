#include <Arduino.h>
#include <ChNil.h>

#include <Params.h>

// setting ATmega32U4 as I2C slave.
#ifdef THR_WIRE_SLAVE

#include <Wire.h>

uint8_t command;

void printResult(char*, Print*);
int wireSlaveCommand(uint8_t, long);

void requestEvent();
void receiveEvent();

void startWireSlave();

#endif

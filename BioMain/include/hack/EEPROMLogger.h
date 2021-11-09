#ifdef THR_EEPROM_LOGGER

#include <Arduino.h>
#include <ChNil.h>
// part of the EEPROM is for the log
// we should be able to save and reload the log

// log is saved in the format ID / in1 / out1 / ... / in8 / out8
// ID is a sequential number
// We expect to add an entry every hour

int getFirstAddress(uint16_t);
void writeLog();
void loggerInit();
int16_t getParameterFromLog(uint16_t, byte);
void readLog(uint16_t);
void formatLog();
uint16_t getFirstLogEntryID();
uint16_t getNextLogEntryID();
void printLog(Print*);

void printLoggerHelp(Print*);
void processLoggerCommand(char, char*, Print*);

THD_WORKING_AREA(waThreadLogger, 20);
THD_FUNCTION(ThreadLogger, arg);

#endif

#ifdef THR_EEPROM_LOGGER

#include <Arduino.h>
#include <ChNil.h>
// part of the EEPROM is for the log
// we should be able to save and reload the log


// log is saved in the format ID / in1 / out1 / ... / in8 / out8
// ID is a sequential number
// We expect to add an entry every hour

#define FIRST_ADDRESS   64
#define LAST_ADDRESS   1023

extern const byte LOG_ENTRY_LENGTH;
extern const byte NUMBER_LOGS;

unsigned long lastLog;
uint16_t eepromLoggerID;
uint16_t eepromLoggerTimeBetween;

int getFirstAddress( uint16_t );
void writeLog();
void loggerInit();
int16_t getParameterFromLog( uint16_t, byte );
void readLog( uint16_t );
void formatLog();
uint16_t getFirstLogEntryID();
uint16_t getNextLogEntryID();
void printLog(Print* );

void printLoggerHelpEEPROM( Print * );
void processLoggerCommandEEPROM( char, char*, Print* );

THD_WORKING_AREA( waThreadLogger, 20 );
THD_FUNCTION( ThreadLogger, arg );

#endif

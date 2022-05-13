// #define DEBUG_MEMORY    // takes huge amount of memory should not be
// activated !!

/*****************************************************************************************
  This thread takes care of the logs and manage the time and its synchronisation
  The thread write the logs at a definite fixed interval of time in the
SST25VF064 chip The time synchronization works through the NTP protocol and our
server
******************************************************************************************/
#include "Params.h"
#ifdef THR_SST_LOGGER

#include <Arduino.h>

//#include "SST.h"
#include "libraries/SST/SST.h"

extern uint32_t nextEntryID;

uint32_t findAddressOfEntryN(uint32_t);

/***********************************************************************************
  Save logs in the Flash memory.
  event_number: If there is a command, then this parameter should be set with
the corresponding command/event number. Should be found in the define list of
  commands/errors
************************************************************************************/
void writeLog(uint16_t, int);

/******************************************************************************************
  Read the corresponding logs in the flash memory of the entry number (ID).
  result: Array of uint8_t where the logs are stored. It should be a 32 bytes
 array for the 3 RRD logs and 12 bytes for the commands/events logs. #ifdef
 LOG_INTERVAL entryN: Log ID that will correspond to the logs address to be read
 and stored in result return:  Error flag: 0: no error occured
  EVENT_ERROR_NOT_FOUND_ENTRY_N: The log ID (entryN) was not found in the flash
 memory
 *****************************************************************************************/
uint32_t printLogN(Print*, uint32_t);

void Last_Log_To_SPI_buff(byte*);
void loadLastEntryToParameters();

/******************************************************************************
  Returns the address corresponding to one log ID nilThdSleepMilliseconds(5);
nilThdSleepMilliseconds(5); entryNb:     Log ID return:      Address of the
first byte where the corresponding log is located
*******************************************************************************/
uint32_t findAddressOfEntryN(uint32_t);

/*****************************************************************************
  Returns the last log ID stored in the memory
  return: Last log ID stored in the memory corresponding to a log type
******************************************************************************/
void recoverLastEntryN();

/*****************************
  Memory related functions
 *****************************/
// Setup the memory for future use
// Need to be used only once at startup
void setupMemory();

void printLastLog(Print*);
void formatFlash(Print*);
void testFlash(Print*);
void readFlash(Print*, long);
/*
   We will check when we have a change to FF at the ID
*/

void debugFlash(Print*);

/*
   We will check when we have a change to FF at the ID
*/
void checkNextID(Print*);

void processLoggerCommand(char, char*, Print*);
void printLoggerHelp(Print*);
void dumpLoggerFlash(Print*, uint32_t, uint32_t);

#endif

// #define DEBUG_MEMORY    // takes huge amount of memory should not be activated !!

/*****************************************************************************************
  This thread takes care of the logs and manage the time and its synchronisation
  The thread write the logs at a definite fixed interval of time in the SST25VF064 chip
  The time synchronization works through the NTP protocol and our server
******************************************************************************************/

#ifdef THR_SST_LOGGER

#include "SST.h"
#include <Arduino.h>

void printLoggerHelp( Print* );

/******************************************
   DEFINE FLASH VERSION (default is SST64)
 *****************************************/
//  THIS SHOULD BE AUTOMATIC !!!
//support SST25VF064C, SST26VF064B (64Mbits) or similar from Cypress
#define SST64 1
//support SST25VF032C, SST26VF032B (32Mbits) or similar from Cypress
//#define SST32 1

#if defined(SST64) || defined(SST32)



//Types of logs
#define ENTRY_SIZE_LINEAR_LOGS     64
#define SIZE_TIMESTAMPS            4
#define SIZE_COUNTER_ENTRY         4

// Definition of the log sectors in the flash for the logs
#if defined(SST64) //64Mbits
#define ADDRESS_MAX   0x800000 // http://www.sst.com/dotAsset/40498.pdf&usd=2&usg=ALhdy294tEkn4s_aKwurdSetYTt_vmXQhw
#elif defined(SST32) //32Mbits
#define ADDRESS_MAX   0X400000
#endif

// #define ADDRESS_MAX   0X001000 // if we don't want to use all memory !!!!


#define ADDRESS_BEG   0x000000
#define ADDRESS_LAST  (ADDRESS_MAX - ENTRY_SIZE_LINEAR_LOGS)
#define SECTOR_SIZE       4096
#define NB_ENTRIES_PER_SECTOR    (SECTOR_SIZE  / ENTRY_SIZE_LINEAR_LOGS)
#define ADDRESS_SIZE  (ADDRESS_MAX  - ADDRESS_BEG)
// The number of entires by types of logs (seconds, minutes, hours, commands/events)
#define MAX_NB_ENTRIES    (ADDRESS_SIZE  / ENTRY_SIZE_LINEAR_LOGS)

#define MAX_MULTI_LOG 64 // Allows to display long log on serial

SST sst;

static uint32_t nextEntryID = 0;
bool logActive;

uint32_t findAddressOfEntryN( uint32_t );

/***********************************************************************************
  Save logs in the Flash memory.
  event_number: If there is a command, then this parameter should be set with the
  corresponding command/event number. Should be found in the define list of
  commands/errors
************************************************************************************/
void writeLog( uint16_t, int );

/******************************************************************************************
  Read the corresponding logs in the flash memory of the entry number (ID).
  result: Array of uint8_t where the logs are stored. It should be a 32 bytes array
  for the 3 RRD logs and 12 bytes for the commands/events logs.
  #ifdef LOG_INTERVAL
  entryN: Log ID that will correspond to the logs address to be read and stored in result
  return:  Error flag: 0: no error occured
  EVENT_ERROR_NOT_FOUND_ENTRY_N: The log ID (entryN) was not found in the flash memory
 *****************************************************************************************/
uint32_t printLogN( Print*, uint32_t );

void Last_Log_To_SPI_buff( byte* );
uint8_t loadLastEntryToParameters();

/******************************************************************************
  Returns the address corresponding to one log ID nilThdSleepMilliseconds(5); nilThdSleepMilliseconds(5);
  entryNb:     Log ID
  return:      Address of the first byte where the corresponding log is located
*******************************************************************************/
uint32_t findAddressOfEntryN( uint32_t );

/*****************************************************************************
  Returns the last log ID stored in the memory
  return: Last log ID stored in the memory corresponding to a log type
******************************************************************************/
void recoverLastEntryN();

/*****************************
  Memory related functions
 *****************************/
//Setup the memory for future use
//Need to be used only once at startup
void setupMemory();

void printLastLog( Print* );
void formatFlash(Print* );
void testFlash( Print* );
void readFlash( Print*, long );
/*
   We will check when we have a change to FF at the ID
*/

void debugFlash( Print* );

/*
   We will check when we have a change to FF at the ID
*/
void checkNextID( Print* );

#ifdef LOG_INTERVAL

#ifdef DEBUG_LOGS
THD_WORKING_AREA(waThreadLogger, 128);
#else
THD_WORKING_AREA(waThreadLogger, 64);
#endif

THD_FUNCTION(ThreadLogger, arg);

#endif


void processLoggerCommand( char, char*, Print* );
void printLoggerHelp( Print* );
void dumpLoggerFlash( Print*, uint32_t, uint32_t);

#endif
#endif
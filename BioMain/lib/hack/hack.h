#include <ChNil.h>

SEMAPHORE_DECL(lockTimeCriticalZone, 1); // only one process in some specific zones

#include <avr/wdt.h>

// Hack library
#include "NullStream.h"
#include "toHex.h"
#include "utility.h"
#include "params.h"
#include "eeprom.h"
#include "eepromLogger.h"
#include "sstLogger.h"
#include "wireSlave.h"
#include "WireMaster.h"
#include "SerialUtilities.h"
#include "Serial.h"
#include "status.h"
#include "start.h"

// Time library
#include "Time.h"

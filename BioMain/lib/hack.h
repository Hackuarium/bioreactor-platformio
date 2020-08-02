
#include "nil/NilRTOS.c"
#include "nil/NilRTOS.h"
#include "nil/board.c"
#include "nil/nil.c"
#include "nil/nilUtility.cpp"
#include "nil/nilcore.c"

SEMAPHORE_DECL(lockTimeCriticalZone,
               1);  // only one process in some specific zones

#include <avr/wdt.h>  // watch dog for automatic reboot in case of crash

#include "hack/NullStream.h"
#include "hack/Serial.h"
#include "hack/SerialUtilities.h"
#include "hack/Utility.h"
#include "hack/WireMaster.h"
#include "hack/WireSlave.h"
#include "hack/eeprom.h"
#include "hack/eepromLogger.h"
#include "hack/params.h"
#include "hack/sstLogger.h"
#include "hack/start.h"
#include "hack/status.h"
#include "hack/toHex.h"
#include "time/Time.cpp"  // git clone https://github.com/PaulStoffregen/Time

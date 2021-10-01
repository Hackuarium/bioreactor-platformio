#include <Arduino.h>
#include <ChNil.h>

// Declare Semaphore
SEMAPHORE_DECL(lockTimeCriticalZone, 1); // only one process in some specific zones
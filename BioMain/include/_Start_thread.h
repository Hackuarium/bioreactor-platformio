
/***********************************************************
                Watchdog, Autoreboot Thread
Monitor the activity. Should be the lower priority process
If the led is "stable" (blinks 500 times per seconds), 
there are not too many activities on the microcontroler
************************************************************/
#include <Arduino.h>
#include <ChNil.h>

THD_WORKING_AREA( waThreadMonitoring, 0 );
THD_FUNCTION( ThreadMonitoring, arg );

/****************************************************************
                NilRTOS Multithreading Table
      The higher in the Table The higher the priority
*****************************************************************/
/****************************************************************
                NilRTOS Multithreading Table
      The higher in the Table The higher the priority
*****************************************************************/
THD_TABLE_BEGIN

// logger should have priority to prevent any corruption of flash memory
#ifdef THR_SST_LOGGER
#include "sstLogger.h"
NIL_THREADS_TABLE_ENTRY(NULL, ThreadLogger, NULL, waThreadLogger, sizeof(waThreadLogger))
#endif

#ifdef THR_STEPPER
#include "Stepper.h"
NIL_THREADS_TABLE_ENTRY(NULL, ThreadStepper, NULL, waThreadStepper, sizeof(waThreadStepper))
#endif

#ifdef THR_WEIGHT
#include "Weight.h"
NIL_THREADS_TABLE_ENTRY(NULL, ThreadWeight, NULL, waThreadWeight, sizeof(waThreadWeight))
#endif

#ifdef THR_ONEWIRE
#include "OneWire2.h"
#include "PID.h"
#include "Fan.h"
  NIL_THREADS_TABLE_ENTRY(NULL, ThreadOneWire, NULL, waThreadOneWire, sizeof(waThreadOneWire))  
  #ifdef THR_PID
  NIL_THREADS_TABLE_ENTRY(NULL, ThreadPID, NULL, waThreadPID, sizeof(waThreadPID))  
  #endif  
  #ifdef THR_FAN
  NIL_THREADS_TABLE_ENTRY(NULL, ThreadFan, NULL, waThreadFan, sizeof(waThreadFan))  
  #endif         
#endif

#ifdef THR_OUTPUTS
#include "Outputs.h"
NIL_THREADS_TABLE_ENTRY(NULL, ThreadOutputs, NULL, waThreadOutputs, sizeof(waThreadOutputs))
#endif

#ifdef THR_STEPS
#include "Steps.h"
NIL_THREADS_TABLE_ENTRY(NULL, ThreadSteps, NULL, waThreadSteps, sizeof(waThreadSteps))
#endif

#ifdef THR_SERIAL
#include "serial.h"
NIL_THREADS_TABLE_ENTRY(NULL, ThreadSerial, NULL, waThreadSerial, sizeof(waThreadSerial))
#endif

#ifdef THR_ERROR
#include "Error.h"
NIL_THREADS_TABLE_ENTRY(NULL, ThreadError, NULL, waThreadError, sizeof(waThreadError))  
#endif    

#ifdef THR_MONITORING
NIL_THREADS_TABLE_ENTRY(NULL, ThreadMonitoring, NULL, waThreadMonitoring, sizeof(waThreadMonitoring))
#endif

THD_TABLE_END
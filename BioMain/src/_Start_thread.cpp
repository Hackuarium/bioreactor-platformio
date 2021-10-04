
/***********************************************************
                Watchdog, Autoreboot Thread
Monitor the activity. Should be the lower priority process
If the led is "stable" (blinks 500 times per seconds), 
there are not too many activities on the microcontroler
************************************************************/
#include <Arduino.h>
#include <ChNil.h>

#include "BioParams.h"

#ifdef THR_MONITORING
  #include "Monitoring.h"
#endif

#ifdef THR_SST_LOGGER
  #include "SSTThread.h"
#endif

#ifdef THR_SERIAL
  #include "SerialThread.h"
#endif

#ifdef THR_ONEWIRE
  #include "BioOneWireThread.h"
#endif

/*******************************************************************************
                          NilRTOS Multithreading Table
      The higher in the Table The higher the priority
*******************************************************************************/
THD_TABLE_BEGIN

// logger should have priority to prevent any corruption of flash memory

#ifdef THR_SST_LOGGER
  THD_TABLE_ENTRY(waThreadLogger, NULL, ThreadLogger, NULL)
#endif

/*

#ifdef THR_STEPPER
#include "Stepper.h"
NIL_THREADS_TABLE_ENTRY(NULL, ThreadStepper, NULL, waThreadStepper, sizeof(waThreadStepper))
#endif

#ifdef THR_WEIGHT
#include "Weight.h"
NIL_THREADS_TABLE_ENTRY(NULL, ThreadWeight, NULL, waThreadWeight, sizeof(waThreadWeight))
#endif
*/
#ifdef THR_ONEWIRE
  THD_TABLE_ENTRY(waThreadOneWire, NULL, ThreadOneWire, NULL)
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
THD_TABLE_ENTRY(waThreadSerial, NULL, ThreadSerial, NULL)
#endif

/*
#ifdef THR_ERROR
#include "Error.h"
NIL_THREADS_TABLE_ENTRY(NULL, ThreadError, NULL, waThreadError, sizeof(waThreadError))  
#endif    

*/
#ifdef THR_MONITORING
THD_TABLE_ENTRY(waThreadMonitoring, NULL, ThreadMonitoring, NULL)
#endif

THD_TABLE_END
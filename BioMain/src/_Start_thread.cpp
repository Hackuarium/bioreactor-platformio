
/***********************************************************
                Watchdog, Autoreboot Thread
Monitor the activity. Should be the lower priority process
If the led is "stable" (blinks 500 times per seconds), 
there are not too many activities on the microcontroler
************************************************************/
#include <Arduino.h>
#include <ChNil.h>

#include <BioParams.h>

#ifdef THR_MONITORING
  #include "BioMonitoringThread.h"
#endif

#ifdef THR_SST_LOGGER
  #include "BioSSTThread.h"
#endif

#ifdef THR_SERIAL
  #include "BioSerialThread.h"
#endif

#ifdef THR_ONEWIRE
  #include "BioOneWireThread.h"
#endif

#ifdef THR_FAN
  #include "BioFanThread.h"
#endif

#ifdef THR_ERROR
  #include "BioErrorThread.h"
#endif

#ifdef THR_PID
  #include "BioPIDThread.h"
#endif

#ifdef THR_STEPPER
  #include "BioStepperThread.h"
#endif

#ifdef THR_STEPS
  #include "BioStepsThread.h"
#endif

#ifdef THR_WEIGHT
  #include "BioWeightThread.h"
#endif

#ifdef THR_OUTPUTS
  #include "BioOutputsThread.h"
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

#ifdef THR_STEPPER
THD_TABLE_ENTRY(waThreadStepper, NULL, ThreadStepper, NULL)
#endif

#ifdef THR_WEIGHT
THD_TABLE_ENTRY(waThreadWeight, NULL, ThreadWeight, NULL)
#endif

#ifdef THR_ONEWIRE
  THD_TABLE_ENTRY(waThreadOneWire, NULL, ThreadOneWire, NULL)
  #ifdef THR_PID
  THD_TABLE_ENTRY(waThreadPID, NULL, ThreadPID, NULL)
  #endif  
  #ifdef THR_FAN
  THD_TABLE_ENTRY(waThreadFan, NULL, ThreadFan, NULL)
  #endif         
#endif

#ifdef THR_OUTPUTS
THD_TABLE_ENTRY(waThreadOutputs, NULL, ThreadOutputs, NULL)
#endif

#ifdef THR_STEPS
THD_TABLE_ENTRY(waThreadSteps, NULL, ThreadSteps, NULL)
#endif

#ifdef THR_SERIAL
THD_TABLE_ENTRY(waThreadSerial, NULL, ThreadSerial, NULL)
#endif

#ifdef THR_ERROR
THD_TABLE_ENTRY(waThreadError, NULL, ThreadError, NULL)
#endif    

#ifdef THR_MONITORING
THD_TABLE_ENTRY(waThreadMonitoring, NULL, ThreadMonitoring, NULL)
#endif

THD_TABLE_END
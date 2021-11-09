#include <Arduino.h>
#include <ChNil.h>

#include "hack/BioParams.h"

#ifdef THR_PID

#ifdef THR_ONEWIRE

THD_WORKING_AREA( waThreadPID, 110 ); //tune the allocated mem (here extra is provided)
THD_FUNCTION(ThreadPID, arg);

/*Temperature PID Control addressing relay*/
void pid_ctrl();

// see the rest of oliver's code for sanity checks
void heatingSetup();

#endif
#endif
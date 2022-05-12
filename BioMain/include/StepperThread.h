#include <Arduino.h>
#include <ChNil.h>

#include "hack/Params.h"

#ifdef THR_STEPPER
/****************************
    THREAD STEPPER MOTOR

    The last verison use a stepper driver and therefore we may simply use a
 Timer to generate an impulsion at a very precise time frame.
 ******************************/

//--------------- IS STEPPER STOPPED ---------------//

bool isStepperStopped();
void doSteps(int, int);

//--------------- STEPPER THREAD ---------------//
THD_WORKING_AREA(waThreadStepper, 16);
THD_FUNCTION(ThreadStepper, arg);

#endif
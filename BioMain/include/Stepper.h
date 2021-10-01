#ifdef THR_STEPPER
/****************************
    THREAD STEPPER MOTOR

    The last verison use a stepper driver and therefore we may simply use a Timer to generate
    an impulsion at a very precise time frame.
 ******************************/

#define MIN_STEPPER_SPEED 5   // RPM
#define MAX_STEPPER_SPEED 90 // RPM

//--------------- IS STEPPER STOPPED ---------------//

bool isStepperStopped();

//--------------- STEPPER THREAD ---------------//

THD_WORKING_AREA( waThreadStepper, 16 );
THD_FUNCTION( ThreadStepper, arg );
void doSteps( int, int );

#endif
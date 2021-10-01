#ifdef THR_PID

#include "PID_v1.h"

#ifdef THR_ONEWIRE

#define SAFETY_MAX_PCB_TEMP 7000  // pcb temperature is max 70°C
#define SAFETY_MIN_PCB_TEMP 1000  // pcb temperatire is min 10°C
#define SAFETY_MAX_LIQ_TEMP 6000  // liquid temperature is max 60°C
#define SAFETY_MIN_LIQ_TEMP 1000  // liquid temperature is min 10°C

#define PID_OUTPUT_LIMIT    100  //200 is ~80% of max PWM --> Limits max avg power to ~8A

void pid_ctrl();
void heatingSetup();

double heatingRegInput;
double heatingRegOutput;
double heatingRegSetpoint;
//Specify the heating regulation links and initial tuning parameters
PID heatingRegPID(&heatingRegInput, &heatingRegOutput, &heatingRegSetpoint, 1, 0.0002, 5, DIRECT);

THD_WORKING_AREA(waThreadPID, 120); //tune the allocated mem (here extra is provided)
THD_FUNCTION( ThreadPID, arg );

/*Temperature PID Control addressing relay*/

void pid_ctrl();

// see the rest of oliver's code for sanity checks
void heatingSetup();

#endif
#endif
#include <Arduino.h>
#include <ChNil.h>

#include "BioParams.h"
#include "Params.h"
#include "Status.h"

#ifdef THR_STEPPER
/****************************
    THREAD STEPPER MOTOR

    The last verison use a stepper driver and therefore we may simply use a Timer to generate
    an impulsion at a very precise time frame.
 ******************************/

#include <TimerOne.h>

#define MIN_STEPPER_SPEED 5   // RPM
#define MAX_STEPPER_SPEED 90 // RPM

//--------------- IS STEPPER STOPPED ---------------//

bool isStepperStopped() {
  if (! isRunning(FLAG_STEPPER_CONTROL) || ! isEnabled(FLAG_STEPPER_CONTROL)) { // PID is disabled
    return true;
  }

  if (isError()) { // any error we should stop stepper !
    return true;
  }
  return false;
}

void doSteps(int speed, int sleep) {
  if (speed < MIN_STEPPER_SPEED) speed = MIN_STEPPER_SPEED;
  if (speed > MAX_STEPPER_SPEED) speed = MAX_STEPPER_SPEED;
  if (isStepperStopped()) {
    Timer1.stop();
  } else {
    Timer1.setPeriod(1000000 / 3200 / speed * 60);
    Timer1.start();
  }
  chThdSleep(sleep);
}

//--------------- STEPPER THREAD ---------------//
THD_FUNCTION(ThreadStepper, arg) {
  chThdSleep(4000);
  bool forward = true;
  uint8_t count = 0;

  pinMode(STEPPER_DIRECTION, OUTPUT);
  pinMode(STEPPER_STEP, OUTPUT);
  // The stepper motor recquires 3200 steps in order to do a full rotation

  Timer1.initialize(1000000 / 3200); // 5000ms  = 40 Hz
  Timer1.pwm(STEPPER_STEP, 512);
  Timer1.stop();

  while (true) {
    //first a check is performed on the motor status
    if (forward) {
      digitalWrite(STEPPER_DIRECTION, HIGH);
    } else {
      digitalWrite(STEPPER_DIRECTION, LOW);
    }

    // acceleration
    for (uint8_t i = 0; i <= 20; i++) {
      int speed = getParameter(PARAM_STEPPER_SPEED) * i / 20;
      doSteps(speed, 50);
    }

    for (int i = 0; i < getParameter(PARAM_STEPPER_SECONDS) - 2; i++) {
      int speed = getParameter(PARAM_STEPPER_SPEED);
      doSteps(speed, 1000);
    }

    // deceleration
    for (int i = 20; i >= 0; i--) {
      int speed = getParameter(PARAM_STEPPER_SPEED) * i / 20;
      doSteps(speed, 50);
    }
    Timer1.stop();

    forward = !forward;
    for (int i = 0; i < getParameter(PARAM_STEPPER_WAIT); i++) {
      chThdSleep(1000);
    }

  }
}

#endif
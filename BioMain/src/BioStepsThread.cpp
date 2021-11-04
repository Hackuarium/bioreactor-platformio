#include <Arduino.h>
#include <ChNil.h>

#include "BioParams.h"
#include "Params.h"

#ifdef THR_STEPS

bool DEBUG_STEPS = false;

uint8_t getMinute() {
  return (uint8_t)((millis() % 3600000) / 60000);
}

void printBits(int x) {
  for (uint8_t i = 16; i > 0; i--) {
    Serial.print(x >> (i - 1) & 1);
  }
  Serial.println("");
}

THD_FUNCTION(ThreadSteps, arg) {
  chThdSleep(3129); // wait a little bit not everything starts at once


  // TODO know when the minute starts so that the minute does not change after couple of seconds
  byte previousMinute = getMinute();
  uint16_t setStatus = 0b0000000000000000;

  while (true) {
    // allows to change the step from the terminal, we reload each time the step
    byte index = getParameter(PARAM_CURRENT_STEP);
    if (index >= NB_STEP_PARAMETERS) {
      index = 20;
    }
    //int stepValue = getParameter(index + FIRST_STEP_PARAMETER);
    int stepValue = getParameter(PARAM_STATUS);
    //byte parameter = (stepValue & 0b0111100000000000) >> 11;
    byte parameter = (stepValue & 0b100000000000) >> 11;
    byte currentMinute = getMinute();
    //int value = stepValue & 0b0000011111111111;
    int value = getParameter(PARAM_CURRENT_WAIT_TIME);
    if (DEBUG_STEPS) {
      Serial.print("======> ");
      Serial.println(index);
      Serial.print("S:");
      printBits(stepValue);
      Serial.print("P:");
      Serial.println(parameter);
      Serial.print("M:");
      Serial.println(currentMinute);
      Serial.print("V:");
      Serial.println(value);
    }
    /*if (stepValue >> 15) { // we set a parameter
      switch (parameter) {
        case 0:
          setParameter(PARAM_TEMP_TARGET, value * 100);
          break;
      }
      index++;
    */
    //} else { // it is an action
      int waitingTime = getParameter(PARAM_CURRENT_WAIT_TIME);
      int sedimentationTime = getParameter(PARAM_SEDIMENTATION_TIME);
      int filledTime = getParameter(PARAM_FILLED_TIME);
      //switch (parameter) {
      switch (index) {
        case 0: // Do nothing
          setParameter(PARAM_ENABLED, 0b000000);
          setParameter(PARAM_STATUS, 0b000000000000);
          //index++;
          index = 20;
          break;
        case 1: // Wait in minutes
          setParameter(PARAM_ENABLED, 0b111111);
          previousMinute = getMinute();
          index++;
        case 2: // Wait in hours
          //if (waitingTime <= 0 && stepValue > 0) {
          if (parameter > 0) {
            //setParameter(PARAM_CURRENT_WAIT_TIME, value * (parameter == 1 ? 1 : 60));
            setParameter(PARAM_CURRENT_WAIT_TIME, waitingTime * 60);
            setParameter(PARAM_STATUS, FLAG_WAITING_TIME_HOURS << 0);
          } else {
            if (DEBUG_STEPS) {
              Serial.print(waitingTime);
              Serial.print(" ");
              Serial.print(currentMinute);
              Serial.print(" ");
              Serial.println(previousMinute);
            }
            if (currentMinute != previousMinute) {
              waitingTime--;
              previousMinute = currentMinute;
              setParameter(PARAM_CURRENT_WAIT_TIME, waitingTime);
            }
            if (waitingTime <= 0) {
              index++;
            }
          }
          break;
        case 3: // Wait for weight reduction to yy grams
          //setParameter(PARAM_STATUS, 0b00010000111);
          setStatus = 0b0000000000000000;
          setStatus ^= ( (1 << FLAG_FOOD_CONTROL) | (1 << FLAG_RELAY_EMPTYING) );
          setParameter(PARAM_STATUS, setStatus );
          if (getParameter(PARAM_WEIGHT) >= getParameter(PARAM_WEIGHT_OFFSET)) {  // Completely empty
            setStatus ^= (1 << FLAG_RELAY_EMPTYING);
            setParameter(PARAM_STATUS, setStatus );
            index++;
          }
          break;
        case 4: // Wait for weight increase to yy grams
          setStatus = 0b0000000000000000;
          setStatus ^= ( (1 << FLAG_PID_CONTROL) | (1 << FLAG_STEPPER_CONTROL) | (1 << FLAG_FOOD_CONTROL) | (1 << FLAG_RELAY_FILLING) );
          setParameter(PARAM_STATUS, setStatus );
          if (getParameter(PARAM_WEIGHT) <= getParameter(PARAM_WEIGHT_MAX)) {
            setStatus ^= (1 << FLAG_RELAY_FILLING);
            setParameter(PARAM_STATUS, setStatus );
            index++;
          }
          break;
        case 5: // Wait for temperature change (continue if < 0.5°C)
          if (abs( (getParameter(PARAM_TEMP_EXT1) + getParameter(PARAM_TEMP_EXT2) / 2 ) - getParameter(PARAM_TEMP_TARGET)) < 50) {
            previousMinute = getMinute();
            index++;
          }
          break;
        // Filled
        case 6:
          if (currentMinute != previousMinute) {
            filledTime--;
            previousMinute = currentMinute;
            setParameter(PARAM_FILLED_TIME, filledTime);
          }
          if (filledTime <= 0) {
            setStatus = 0b0000000000000000;
            setStatus |= ( (1 << FLAG_PID_CONTROL) | ~(1 << FLAG_STEPPER_CONTROL) );
            setParameter(PARAM_STATUS, setStatus );
            previousMinute = getMinute();
            index++;
          }
          break;
        // Sedimentation
        case 7:
          if (currentMinute != previousMinute) {
            sedimentationTime--;
            previousMinute = currentMinute;
            setParameter(PARAM_SEDIMENTATION_TIME, sedimentationTime);
          }
          if (sedimentationTime <= 0) {
            index++;
          }
          break;
        // Empty
        case 8:
          setStatus = 0b0000000000000000;
          setStatus |= ( ~(1 << FLAG_PID_CONTROL) | ~(1 << FLAG_STEPPER_CONTROL) | (1 << FLAG_FOOD_CONTROL) | (1 << FLAG_RELAY_EMPTYING) );
          setParameter(PARAM_STATUS, setStatus);
          if (getParameter(PARAM_WEIGHT) <= getParameter(PARAM_WEIGHT_MIN)) { // No completely empty
            setStatus ^= (1 << FLAG_RELAY_EMPTYING);
            setParameter(PARAM_STATUS, setStatus );
            index = 0;
          }
          break;
        case 20:  // Do nothing
        break;
        default:
          index = 20;
      }
    //}
    setParameter(PARAM_CURRENT_STEP, index);
    chThdSleep(1000);
  }
}

#endif
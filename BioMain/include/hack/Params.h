/*********************************************
   This file is used to declare the parameters
   table used by the program.

   We use the EEPROM for saving the parameters
   changed by the user during the functionment
   of the Bioreactor.

   The parameter are loaded during the boot.

   All change to important parameters are saved
   to the EEPROM
 *********************************************/
#include <Arduino.h>
#include <ChNil.h>

/******************************
  THREADS
*******************************/

// #define THR_WIRE_MASTER 1
#define THR_SST_LOGGER 1
#define THR_SERIAL 1
#define THR_ONEWIRE 1
#define THR_PID 1
#define THR_FAN 1
#define THR_ERROR 1
#define THR_STEPPER 1
#define THR_STEPS 1
#define THR_WEIGHT 1
#define THR_OUTPUTS 1
#define THR_MONITORING 1

#define NB_PARAMETERS_LINEAR_LOGS 26

// Definition of all events to be logged
#define EVENT_ARDUINO_BOOT 1
#define EVENT_ARDUINO_SET_SAFE 2

#define EVENT_STATUS_ENABLE 3
#define EVENT_STATUS_DISABLE 4

#define EVENT_ERROR_FAILED 6
#define EVENT_ERROR_RECOVER 7

#define EVENT_MOTOR_START 20
#define EVENT_MOTOR_STOP 21

#define EVENT_ERROR_NOT_FOUND_ENTRY_N 150

#define EVENT_SAVE_ALL_PARAMETER 255
// extern const uint8_t EVENT_SAVE_ALL_PARAMETER;
// When parameters are set (and saved) an event is recorded (256-281 : A-Z +
// .... (if more parameters than 262 ...)
#define EVENT_PARAMETER_SET 256

// MONITORING Thread
#define MONITORING_LED 13

// STEPPER Thread
#define STEPPER_DIRECTION 8
#define STEPPER_STEP 9

// OUTPUT Thread
#define OUT_1 10
#define OUT_2 5
#define OUT_3 A6
#define OUT_4 12

// FAN Thread
#define OUT_FAN 11
#define TEMP_FAN_ON 3500

// ERROR Thread
#define OUT_ERROR A4

// Weght Thread
#define WEIGHT_DATA A1
#define WEIGHT_CLK \
  A0  // need to redefine the calibration parameters and process (see "HX711")

// ONE WIRE Thread
#define TEMP_EXT1 7
#define TEMP_EXT2 A5
#define TEMP_PCB A2

// PID Thread
#define PID_CONTROL 6

// EEPROM || SST Thread
#define EVENT_LOGGING 1

/******************************
  SERIAL, LOGGER AND DEBUGGERS
*******************************/

#define MAX_PARAM 68

#ifdef THR_SST_LOGGER
#define FLASH_SELECT 1   // Flash SS_SPI
#define LOG_INTERVAL 300  // Interval in (s) between logs logger
#define EVENT_LOGGING 1
#endif

#define PARAM_TEMP_EXT1 0  // A - temperature of the solution
#define PARAM_TEMP_EXT2 1  // B - temperature of the solution

#define PARAM_TEMP_PCB 2     // C - temperature of the heating plate
#define PARAM_PID 3          // D - heating amount of energy
#define PARAM_TEMP_TARGET 4  // E - target temperature of the liquid

#define PARAM_WEIGHT 5                   // F - in unit of the balance
#define PARAM_WEIGHT_G 6                 // G - in unit of the balance (gr)
#define PARAM_WEIGHT_SINCE_LAST_EVENT 7  // H - last weight
#define PARAM_WEIGHT_MAX 8               // I - Maximum weight

#define PARAM_STEPPER_SPEED 26  // AA - motor speed, in RPM
#define PARAM_STEPPER_SECONDS \
  27  // AB   number of seconds before changing direction
#define PARAM_STEPPER_WAIT \
  28  // AC   wait time in seconds between change of direction
#define PARAM_WEIGHT_FACTOR \
  29  // AD - Weight calibration: conversion factor digital -> gr
      // (weight=FACTOR*dig_unit)
#define PARAM_WEIGHT_EMPTY \
  30  // AE - Weight calibration: digital offset value when bioreactor is empty

#define PARAM_CURRENT_STEP 22
#define PARAM_CURRENT_WAIT_TIME 23
// 36-51 is used by the 16 allowed step
#define FIRST_STEP_PARAMETER 52  // BA
#define LAST_STEP_PARAMETER 67   // BP
#define NB_STEP_PARAMETERS LAST_STEP_PARAMETER - FIRST_STEP_PARAMETER + 1

/******************
   FLAG DEFINITION
 ******************/
#define PARAM_ERROR 24  // Y - errors
// extern const int PARAM_ERROR;
#define FLAG_TEMP_PCB_PROBE_ERROR \
  0  // pcb probe failed (one wire not answering)
#define FLAG_TEMP_EXT1_PROBE_ERROR \
  1  // external temperature 1 probe failed (one wire not answering)
#define FLAG_TEMP_EXT2_PROBE_ERROR \
  2  // external temperature 2 probe failed (one wire not answering)
#define FLAG_TEMP_PCB_RANGE_ERROR 3   // temperature of pcb is outside range
#define FLAG_TEMP_EXT1_RANGE_ERROR 4  // temperature of liquid is outside range
#define FLAG_TEMP_EXT2_RANGE_ERROR 5  // temperature of liquid is outside range
#define FLAG_TEMP_TARGET_RANGE_ERROR 6  // target temperature is outside range
#define MASK_TEMP_ERROR 0b01111111  // where are the bit for temperature error

#define FLAG_WEIGHT_RANGE_ERROR 7     // the weight is outside range
#define MASK_WEIGHT_ERROR 0b10000000  // where are the bit for weight error

#define PARAM_ENABLED 25  // Z - enabled service (set by user)
#define PARAM_STATUS 51   // AZ - currently active service

// the following flags are defined for PARAM_STATUS and PARAM_ENABLED
#define FLAG_PID_CONTROL 0      // 0 to stop PID
#define FLAG_STEPPER_CONTROL 1  // 0 to stop engine
#define FLAG_OUTPUT_1 2
#define FLAG_OUTPUT_2 3
#define FLAG_OUTPUT_3 4
#define FLAG_OUTPUT_4 5

// PARAM_STATUS
#define FLAG_FOOD_CONTROL 2  // Not used
#define FLAG_PH_CONTROL 6
#define FLAG_GAS_CONTROL 7
#define FLAG_SEDIMENTATION 8
#define FLAG_RELAY_FILLING 9
#define FLAG_RELAY_EMPTYING 10
#define FLAG_PH_CALIBRATE 11
#define FLAG_RELAY_ACID 12
#define FLAG_RELAY_BASE 13

// value that should not be taken into account
// in case of error the parameter is set to this value
#define ERROR_VALUE -32768

/*******************************************************************************
      Funcs.h
*******************************************************************************/

#define INT_MAX_VALUE 32767
#define INT_MIN_VALUE -32768
#define LONG_MAX_VALUE 2147483647

#define EE_START_PARAM 0  // We save the parameter from byte 0 of EEPROM
#define EE_LAST_PARAM \
  (MAX_PARAM * 2 - 1)  // The last parameter is stored at byte 50-51

#define EE_QUALIFIER (MAX_PARAM * 2)

#define EEPROM_MIN_ADDR 0
#define EEPROM_MAX_ADDR 1023

/*******************************************************************************
      Serial.h
*******************************************************************************/

#define SERIAL_BUFFER_LENGTH 32
#define SERIAL_MAX_PARAM_VALUE_LENGTH 32

// setting ATmega32U4 as I2C slave.
#ifndef I2C_HARDWARE
#define I2C_HARDWARE 1
#endif

/*******************************************************************************
      WireMaster.h
*******************************************************************************/

#define I2C_TIMEOUT 10
#define I2C_SLOWMODE 1
#define WIRE_MAX_DEVICES 8

/*******************************************************************************
      EEPROMLogger.h
*******************************************************************************/
//#define LOG_INTERVAL      10  //Interval in (s) between logs logger

#define LOG_ENTRY_LENGTH (NB_PARAMETERS_LINEAR_LOGS + 2) * 2
#define NUMBER_LOGS 960 / LOG_ENTRY_LENGTH

#define FIRST_ADDRESS 64
#define LAST_ADDRESS 1023
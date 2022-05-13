#include <Arduino.h>
#include <ChNil.h>
#include <avr/eeprom.h>

#include "Params.h"

extern int parameters[MAX_PARAM];

// uint16_t getQualifier();
bool setParameterBit(uint8_t number, uint8_t bitToSet);
bool clearParameterBit(uint8_t number, uint8_t bitToClear);
// void writeLog( uint16_t event_number, int parameter_value );

void toggleParameterBit(uint8_t, uint8_t);
void setupParameters();
void setParameter(uint8_t, int);
void incrementParameter(uint8_t);
void saveParameters();
void setAndSaveParameter(uint8_t, int);
void printParameter(Print*, uint8_t);
void printParameters(Print*);

bool getParameterBit(uint8_t, uint8_t);
bool setParameterBit(uint8_t, uint8_t);
bool clearParameterBit(uint8_t, uint8_t);
bool saveAndLogError(bool, uint8_t);

uint8_t printCompactParameters(Print*, uint8_t);
uint8_t printCompactParameters(Print*);

int getParameter(uint8_t);

void resetParameters();
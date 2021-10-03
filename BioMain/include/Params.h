
#include <Arduino.h>
#include <ChNil.h>
#include <avr/eeprom.h>

#include "BioParams.h"

extern int parameters[MAX_PARAM];

//uint16_t getQualifier();
bool setParameterBit( byte number, byte bitToSet );
bool clearParameterBit( byte number, byte bitToClear );
//void writeLog( uint16_t event_number, int parameter_value );

void toggleParameterBit( byte, byte );
void setupParameters();
void setParameter( byte, int );
void incrementParameter( byte );
void saveParameters();
void setAndSaveParameter( byte, int );
void printParameter( Print*, byte );
void printParameters( Print* );

bool getParameterBit( byte, byte );
bool setParameterBit( byte, byte );
bool clearParameterBit( byte, byte );
bool saveAndLogError( boolean, byte );

uint8_t printCompactParameters( Print*, byte );
uint8_t printCompactParameters( Print* );

int getParameter( byte );
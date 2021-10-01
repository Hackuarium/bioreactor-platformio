#ifdef THR_WEIGHT

#include <Arduino.h>
#include <ChNil.h>

THD_WORKING_AREA( waThreadWeight, 56 ); // minimum of 32 !
THD_FUNCTION( ThreadWeight, arg );

void printWeightHelp( Print* );
void processWeightCommand( char, char*, Print* );
int getWeight();
int convertWeightToG( int );

#endif
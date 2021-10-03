// code taken from https://github.com/Hackuarium/simple-spectro/tree/master/arduino/SimpleSpectro. Allows serial monitoring communication.
#include <ChNil.h>
#include <Arduino.h>

void resetParameters();

void printUtilitiesHelp( Print* );
void printFreeMemory( Print* );
void processUtilitiesCommand( char, char*, Print* );
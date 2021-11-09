// code taken from
// https://github.com/Hackuarium/simple-spectro/tree/master/arduino/SimpleSpectro.
// Allows serial monitoring communication.
#include <Arduino.h>
#include <ChNil.h>

void printUtilitiesHelp(Print*);
void printFreeMemory(Print*);
void processUtilitiesCommand(char, char*, Print*);
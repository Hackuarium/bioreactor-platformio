#include <Arduino.h>
#include <ChNil.h>

#include "Params.h"

#ifdef THR_WEIGHT

#include "libraries/HX711/HX711.h"

void printWeightHelp(Print*);
int getWeight();
int convertWeightToG(int);
void processWeightCommand(char, char*, Print*);

#endif
#include <Arduino.h>
#include <ChNil.h>

#include "Params.h"

#ifdef THR_WEIGHT

void printWeightHelp(Print*);
int getWeight();
int convertWeightToG(int);
void processWeightCommand(char, char*, Print*);

#endif
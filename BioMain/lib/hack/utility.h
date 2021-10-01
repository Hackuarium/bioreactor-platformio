#include <Arduino.h>
#include "TimeLib.h"

void print2Digits(Print* , int );
void epochToString(time_t , Print* );
void reboot();
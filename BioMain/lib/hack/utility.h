#include <Arduino.h>
#include "Time.h"

void print2Digits(Print* , int );
void epochToString(time_t , Print* );
void reboot();
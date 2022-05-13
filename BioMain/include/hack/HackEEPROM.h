#include <Arduino.h>
#include <ChNil.h>

void setQualifier(uint16_t);
void setDataLong(int, long);
void getStatusEEPROM(Print*);

uint16_t getQualifier();

long getDataLong(int);
#include <Arduino.h>
#include <ChNil.h>

#define SOFTWARE_VERSION "v0.0.1"

// Import constants
#include <Params.h>
// Import internal libraries
#include <Hack.h>

void checkParameters();
void initParameters();

/*********
   SETUP
 *********/
void setup() {
  delay(1000);
  Serial.begin(9600);
  delay(1000);
  setupParameters();

#ifdef FLASH_SELECT
  pinMode(FLASH_SELECT, OUTPUT);
  setupMemory();
  recoverLastEntryN();
  loadLastEntryToParameters();  // get back the previous config
#endif

  chBegin();
}

void loop() {}
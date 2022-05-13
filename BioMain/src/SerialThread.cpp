#include <Arduino.h>
#include <ChNil.h>
#include "Params.h"

#ifdef THR_SERIAL

#include <hack/Serial.h>

uint8_t serialBufferPositionB = 0;
char serialBufferB[SERIAL_BUFFER_LENGTH];

THD_FUNCTION(ThreadSerial, arg) {
  Serial.begin(9600);
  while (true) {
    while (Serial.available()) {
      // get the new byte:
      char inChar = (char)Serial.read();

      if (inChar == 13 || inChar == 10) {
        // this is a carriage return;
        if (serialBufferPositionB > 0) {
          printResult(serialBuffer, &Serial);
        }
        serialBufferPositionB = 0;
        serialBuffer[0] = '\0';
      } else {
        if (serialBufferPositionB < SERIAL_BUFFER_LENGTH) {
          serialBuffer[serialBufferPositionB] = inChar;
          serialBufferPositionB++;
          if (serialBufferPositionB < SERIAL_BUFFER_LENGTH) {
            serialBuffer[serialBufferPositionB] = '\0';
          }
        }
      }
    }
    chThdSleep(1);
  }
}

#endif
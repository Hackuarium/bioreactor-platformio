#include <Arduino.h>
#include <ChNil.h>

#include "Params.h"
#include "Funcs.h"

#ifdef THR_WEIGHT

#include "Sem.h"
// SEMAPHORE_DECL(lockTimeCriticalZone, 1); // only one process in some specific
// zones

// #include <HX711.h>
#include "libraries/HX711/HX711.h"

HX711 scale(WEIGHT_DATA, WEIGHT_CLK, 64);

void printWeightHelp(Print* output) {
  output->println(F("Weight help"));
  output->println(F("(we) Empty (tare)"));
  output->println(F("(wk) Empty + 1kg"));
  output->println(F("(wh) Filled level"));
  output->println(F("(wt) Test"));
}

int getWeight() {  // we can not avoid to have some errors measuring the weight
  // and currently we don't know where it is coming from
  // so we need to find out what are the correct values and what are the wrong
  // one if there is an error it always end with 00000001 we will also need 4
  // consecutive values that differ less than 10%
  byte counter = 0;
  long weight = 0;
  while (counter < 4) {
    while (!scale.is_ready()) {
      chThdSleep(10);
    }
    chSemWait(&lockTimeCriticalZone);
    long currentWeight = scale.read();
    // long currentWeight = scale.read_average();
    chSemSignal(&lockTimeCriticalZone);

    if ((currentWeight & 0xFF) != 1) {
      if (weight == 0) {
        weight += currentWeight;
        counter++;
      } else {
        int difference = abs((long)100 - (weight * (long)100 / (long)counter) / currentWeight);
        // int difference = abs((weight / counter) - currentWeight);
        if (difference < 10) {
          weight += currentWeight;
          counter++;
        } else {
          weight = 0;
          counter = 0;
        }
      }
      chThdSleep(10);
    }
  }
  return (weight / (long)counter / 100);
  // return weight / counter;
}

int convertWeightToG(int weight) {
  return ((long)(weight - getParameter(PARAM_WEIGHT_EMPTY)) * 1000) /
         getParameter(PARAM_WEIGHT_FACTOR);
}

void processWeightCommand(char command, char* data, Print* output) {
  int weight = getWeight();
  switch (command) {
    case 'e':  // define the empty level
      setAndSaveParameter(PARAM_WEIGHT_EMPTY, weight);
      output->println(weight);
      break;
    case 'k':  // define the weight one kg over the tare
      setAndSaveParameter(PARAM_WEIGHT_FACTOR,
                          weight - getParameter(PARAM_WEIGHT_EMPTY));
      output->println(weight);
      break;
    case 'h':  // define high level
      setAndSaveParameter(PARAM_WEIGHT_MAX, weight);
      output->println(weight);
      break;
    case 't':
      output->println(F("Current weight"));
      for (byte i = 0; i < 10; i++) {
        int weight = getWeight();
        output->print(weight);
        output->print(F(" = "));
        output->print(convertWeightToG(weight));
        output->println("g");
      }
      break;
    default:
      printWeightHelp(output);
  }
}

#endif
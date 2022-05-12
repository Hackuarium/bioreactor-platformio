#include <Arduino.h>
#include <ChNil.h>

#include "Params.h"
#include "Funcs.h"
#include "Weight.h"

#ifdef THR_WEIGHT

THD_FUNCTION(ThreadWeight, arg) {
  chThdSleep(1234);  // wait a little bit not everything starts at once

  /********************************************
               initialisation
  ********************************************/
  int weight;

  /********************************************
               Thread Loop
  ********************************************/
  while (true) {
    chThdSleep(1000);

    weight = getWeight();  // sensor read, better to have a higher value if the
                           // weight increase
    setParameter(PARAM_WEIGHT, weight);
    setParameter(PARAM_WEIGHT_G, convertWeightToG(weight));

    // are we outside ranges ?

    int error =
        (getParameter(PARAM_WEIGHT_MAX) - getParameter(PARAM_WEIGHT_EMPTY)) / 5;

    if ((error > 0 && ((weight < (getParameter(PARAM_WEIGHT_EMPTY) - error)) ||
                       (weight > (getParameter(PARAM_WEIGHT_MAX) + error)))) ||
        (error < 0 && ((weight > (getParameter(PARAM_WEIGHT_EMPTY) - error)) ||
                       (weight < (getParameter(PARAM_WEIGHT_MAX) + error))))) {
      saveAndLogError(true, FLAG_WEIGHT_RANGE_ERROR);
    } else {
      saveAndLogError(false, FLAG_WEIGHT_RANGE_ERROR);
    }
  }
}

#endif
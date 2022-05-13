#include <Arduino.h>

#include "Funcs.h"
#include "SSTLogger.h"

bool isError(int filter) {
  if ((getParameter(PARAM_ERROR) & filter) != 0)
    return true;
  return false;
}

bool isError() {
  return (getParameter(PARAM_ERROR) != 0);
}

bool getStatus(byte statusFlag) {
  return getParameterBit(PARAM_STATUS, statusFlag);
}

bool isEnabled(byte statusFlag) {
  return getParameterBit(PARAM_ENABLED, statusFlag);
}

bool isRunning(byte statusFlag) {
  return getParameterBit(PARAM_STATUS, statusFlag);
}

bool startProcess(byte statusFlag) {
  boolean statusChanged = setParameterBit(PARAM_STATUS, statusFlag);
#ifdef EVENT_LOGGING
  if (statusChanged) {
    writeLog(EVENT_STATUS_ENABLE, statusFlag);
  }
#endif
  return statusChanged;
}

bool stopProcess(uint8_t statusFlag) {
  bool statusChanged = clearParameterBit(PARAM_STATUS, statusFlag);
#ifdef EVENT_LOGGING
  if (statusChanged) {
    writeLog(EVENT_STATUS_DISABLE, statusFlag);
  }
#endif
  return statusChanged;
}
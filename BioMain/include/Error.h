#ifdef THR_ERROR

#include <ChNil.h>

THD_WORKING_AREA(waThreadError, 0); //tune the allocated mem (here extra is provided)
NIL_THREAD(ThreadError, arg);

#endif
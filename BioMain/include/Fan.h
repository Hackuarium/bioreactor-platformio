#ifdef THR_FAN

#include <ChNil.h>

THD_WORKING_AREA(waThreadFan, 0); //tune the allocated mem (here extra is provided)
THD_FUNCTION(ThreadFan, arg);

/*Temperature PID Control addressing relay*/

void setFan();

#endif
#include <ChNil.h>
//#include "Params.h"
#include "hack/Params.h"

#ifdef THR_FAN

/*Temperature PID Control addressing relay*/
void setFan();

THD_WORKING_AREA(waThreadFan,
                 0);  // tune the allocated mem (here extra is provided)
THD_FUNCTION(ThreadFan, arg);

#endif
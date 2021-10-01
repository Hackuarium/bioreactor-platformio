#if defined(THR_STEPS)

bool DEBUG_STEPS = false;

THD_FUNCTION( waThreadSteps, 100 );
THD_FUNCTION( ThreadSteps, arg );

byte getMinute();
void printBits( int );

#endif
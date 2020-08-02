
/***********************************************************
                Watchdog, Autoreboot Thread
Monitor the activity. Should be the lower priority process
If the led is "stable" (blinks 500 times per seconds),
there are not too many activities on the microcontroler
************************************************************/
NIL_WORKING_AREA(waThreadMonitoring, 0);
NIL_THREAD(ThreadMonitoring, arg) {
  nilThdSleepMilliseconds(8000);  // Do not start the watchdog too quickly
  wdt_enable(WDTO_8S);            // activate the watchdog
#ifdef MONITORING_LED
  pinMode(MONITORING_LED, OUTPUT);  // diode pin out
#endif

  while (TRUE) {
#ifdef MONITORING_LED
    digitalWrite(MONITORING_LED, HIGH);
    nilThdSleepMilliseconds(500);
    digitalWrite(MONITORING_LED, LOW);
    nilThdSleepMilliseconds(500);
#endif
    wdt_reset();  // resed avoid the automatic reboot
  }
}

/****************************************************************
                NilRTOS Multithreading Table
      The higher in the Table The higher the priority
*****************************************************************/
NIL_THREADS_TABLE_BEGIN()

// logger should have priority to prevent any corruption of flash memory
#ifdef THR_SST_LOGGER
NIL_THREADS_TABLE_ENTRY(NULL,
                        ThreadLogger,
                        NULL,
                        waThreadLogger,
                        sizeof(waThreadLogger))
#endif

#ifdef THR_STEPPER
NIL_THREADS_TABLE_ENTRY(NULL,
                        ThreadStepper,
                        NULL,
                        waThreadStepper,
                        sizeof(waThreadStepper))
#endif

#ifdef THR_WEIGHT
NIL_THREADS_TABLE_ENTRY(NULL,
                        ThreadWeight,
                        NULL,
                        waThreadWeight,
                        sizeof(waThreadWeight))
#endif

#ifdef THR_ONEWIRE
NIL_THREADS_TABLE_ENTRY(NULL,
                        ThreadTemp,
                        NULL,
                        waThreadTemp,
                        sizeof(waThreadTemp))
#ifdef THR_PID
NIL_THREADS_TABLE_ENTRY(NULL,
                        Thread_PID,
                        NULL,
                        waThread_PID,
                        sizeof(waThread_PID))
#endif
#endif

#ifdef THR_PUMPS
NIL_THREADS_TABLE_ENTRY(NULL,
                        ThreadPumps,
                        NULL,
                        waThreadPumps,
                        sizeof(waThreadPumps))
#endif

#ifdef THR_SERIAL
NIL_THREADS_TABLE_ENTRY(NULL,
                        ThreadSerial,
                        NULL,
                        waThreadSerial,
                        sizeof(waThreadSerial))
#endif

#ifdef THR_MONITORING
NIL_THREADS_TABLE_ENTRY(NULL,
                        ThreadMonitoring,
                        NULL,
                        waThreadMonitoring,
                        sizeof(waThreadMonitoring))
#endif

NIL_THREADS_TABLE_END()
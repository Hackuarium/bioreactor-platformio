
/***********************************************************
                Watchdog, Autoreboot Thread
Monitor the activity. Should be the lower priority process
If the led is "stable" (blinks 500 times per seconds), 
there are not too many activities on the microcontroler
************************************************************/
#include <Arduino.h>
#include <ChNil.h>
#include <avr/wdt.h>

THD_FUNCTION(ThreadMonitoring, arg) {
  chThdSleep(8000); //Do not start the watchdog too quickly
  wdt_enable(WDTO_8S);  //activate the watchdog
  #ifdef MONITORING_LED
  pinMode(MONITORING_LED, OUTPUT); //diode pin out   
  #endif
  
  while (true) {
    
    #ifdef MONITORING_LED
    digitalWrite(MONITORING_LED,HIGH);
    nilThdSleepMilliseconds(500); 
    digitalWrite(MONITORING_LED,LOW);
    nilThdSleepMilliseconds(500);
    #endif
    wdt_reset();//resed avoid the automatic reboot
  }
}

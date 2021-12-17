#include "timers.h"
#include "blinker.h"
#include "clocks_etc.h"
#include "debug.h"

#include <stdint.h>
#include <assert.h>

#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/cpufunc.h>


Blinker blinker;
Timer timer;

#define PIN PB4

void setupPins(void) {
    DDRB |= _BV(PIN);
}

void sleep(void) {
    sleep_enable();
    sleep_cpu();
    sleep_disable();
}

void setupBlinker(void) {
    blinkerSetup(&blinker, 3, ST_MS2TICKS(100), ST_MS2TICKS(150), PIN);
}

void startBlinker(void) {
    blinkerStart(&blinker, 0, 0);
}

void startTimer(void* arg) {
    stSetTimer(&timer, ST_MS2TICKS(2000), startTimer, 0);
    startBlinker();
}
    

int main(void)
{
    setupClockEtc();
    setupPins();
    stInit();
    setupBlinker();
    startTimer(0);
    sei();
    stEnableClock();
    sleep();
    while (1)
    {
        sleep();
    }
}

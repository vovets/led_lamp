#include "timers.h"
#include "blinker.h"
#include "lib/clocks_etc.h"
#include "debug.h"

#include <stdint.h>
#include <assert.h>

#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/cpufunc.h>


Blinker onOffBlinker;
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
    blinkerSetup(&onOffBlinker, 3, ST_MS2TICKS(100), ST_MS2TICKS(150), PIN);
}

void startBlinker(void) {
    blinkerStart(&onOffBlinker, 0, 0);
}

void startTimer(void* arg) {
    tmSetTimer(&timer, ST_MS2TICKS(2000), startTimer, 0);
    startBlinker();
}
    

int main(void)
{
    setupClock();
    setupPins();
    tmInit();
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

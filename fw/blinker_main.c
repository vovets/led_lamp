#include "timers.h"
#include "blinker.h"
#include "lib/clocks_etc.h"
#include "debug.h"

#include <stdint.h>
#include <assert.h>

#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/cpufunc.h>

uint8_t pins[3] = { PB4, PB0, PB1};

Blinker blinkers[3];

void setupPins(void) {
    DDRB |= _BV(pins[0]);
    DDRB |= _BV(pins[1]);
    DDRB |= _BV(pins[2]);
}

void sleep(void) {
    sleep_enable();
    sleep_cpu();
    sleep_disable();
}

void setupBlinkers() {
    blinkerSetup(&blinkers[0],  1, ST_MS2TICKS(10), ST_MS2TICKS(40), pins[0]);
    blinkerSetup(&blinkers[1],  1, ST_MS2TICKS(1), ST_MS2TICKS(4000), pins[1]);
    blinkerSetup(&blinkers[2],  1, ST_US2TICKS(500), ST_US2TICKS(99500), pins[2]);
}

void blinkerFinish(Blinker* blinker, void* arg);

void startBlinkers() {
    blinkerStart(&blinkers[0], blinkerFinish, 0);
    blinkerStart(&blinkers[1], blinkerFinish, 0);
    blinkerStart(&blinkers[2], blinkerFinish, 0);
    _NOP();
}

void blinkerFinish(Blinker* blinker, void* arg) {
//    debugTrace((uintptr_t)blinker);
    blinkerStart(blinker, blinkerFinish, 0);
}

int main(void)
{
    setupClock();
    setupPins();
    tmInit();
    setupBlinkers();
    startBlinkers();
    sei();
    stEnableClock();
    sleep();
    while (1)
    {
        sleep();
    }
}

#include <lib/timers.h>
#include <lib/blinker.h>
#include <lib/clocks_etc.h>
#include <lib/debug.h>
#include <lib/loop.h>
#include <lib/event_queue.h>

#include <stdint.h>

#include <avr/interrupt.h>


Blinker onOffBlinker;
Timer timer;

#define LED_PIN PB3

void setupPins(void) {
    DDRB |= _BV(LED_PIN);
}

uint8_t sleepMode(void) {
    return SLEEP_MODE_IDLE;
}

void pin(bool on) {
    if (on) {
        PORTB |= _BV(LED_PIN);
    } else {
        PORTB &= ~_BV(LED_PIN);
    }
}

void setupBlinker(void) {
    blinkerSetup(&onOffBlinker, BlinkerModeOnThenOff, 3, ST_MS2TICKS(100), ST_MS2TICKS(150), &pin);
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
    eqInit();
    stInit();
    tmInit();
    setupBlinker();
    startTimer(0);
    sei();
    stEnableClock();
    loop();
}

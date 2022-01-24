#include "timers.h"
#include "blinker.h"
#include "lib/clocks_etc.h"
#include "debug.h"
#include "macro_utils.h"

#include <stdint.h>
#include <assert.h>

#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/io.h>
#include <avr/cpufunc.h>


#define PIN PB4
// min(PERIOD)==2
#define PERIOD MAX(ST_MS2TICKS(1), 2)

void setupPins(void) {
    DDRB |= _BV(PIN);
}

void togglePin(uint8_t pin) {
    if (PORTB & _BV(pin)) {
        PORTB &= ~_BV(pin);
    } else {
        PORTB |= _BV(pin);
    }
}

void sleep(void) {
    sleep_mode();
}

void setAlarm(void);

void alarm(void* arg) {
    static volatile SysTimePoint prev = 0;
    uint8_t ocr = OCR1A;
    setAlarm();
    togglePin(PIN);
    SysTimePoint t = stNow();
    assert((t & 0xFFU) == (uint8_t)(ocr + 1)); // we are still within the same time interval as when timer fired
    assert(t - prev == PERIOD);
    prev = t;
}

void setAlarm(void) {
    stSetAlarm(PERIOD, alarm, 0);
}

int main(void)
{
    setupClock();
    setupPins();
    tmInit();
    setAlarm();
    stEnableClock();
    sei();
    do {
        sleep();
        _NOP();
    } while (1);
}

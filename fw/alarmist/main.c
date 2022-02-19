#include <lib/sys_time.h>
#include <lib/clocks_etc.h>
#include <lib/debug.h>
#include <lib/macro_utils.h>
#include <lib/loop.h>
#include <lib/event_queue.h>

#include <stdint.h>
#include <assert.h>

#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/io.h>


#define LED_PIN PB4
#define PERIOD 2

void setupDebug(void) {
    debugTraceEnableIds(
            (uint32_t)0
//            | bits(debugEvPut)
//            | bits(debugEvGet)
            | bits(debugAlarmEnabled)
//            | bits(debugAlarmDisabled)
//            | bits(debugEnterSleep)
//            | bits(debugExitSleep)
    );
}

void setupPins(void) {
    DDRB |= _BV(LED_PIN);
}

static inline void togglePin(uint8_t pin) {
    if (PORTB & _BV(pin)) {
        PORTB &= ~_BV(pin);
    } else {
        PORTB |= _BV(pin);
    }
}

uint8_t sleepMode(void) {
    return SLEEP_MODE_IDLE;
//    return SLEEP_MODE_NONE;
}

void alarm(Event* event) {
    static volatile SysTimePoint prev = 0;
//    debugPinOff(DEBUG_PIN_0);
    togglePin(LED_PIN);
    stSetAlarmAt(event->time + PERIOD);
    SysTimePoint now = stNow();
    assert_(now - event->time < PERIOD - 1);
    assert_(now - prev == PERIOD);
    prev = now;
}

int main(void)
{
    setupDebug();
    debugPinInit();
    setupClock();
    setupPins();
    eqInit();
    stInit();
    stSetAlarmAtI(stNowI() + PERIOD);
    stEnableClock();
    sei();
    while (true) {
        while(processOneEvent()) {
        }
        tryToSleep();
    }
}

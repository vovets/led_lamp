#include "loop.h"
#include <lib/event_queue.h>
#include <lib/timers.h>
#include "debug.h"

#include <assert.h>

#include <avr/sleep.h>
#include <util/atomic.h>


void loop(void) {
    while (true) {
        Event e;
        while(!eqEmpty()) {
            eqGet(&e);
            switch(e.type) {
            case evAlarm:
                handleAlarm(&e);
                break;
            case evPinChange:
                handlePinChange(&e);
                break;
            case evAdc:
                handleAdc(&e);
                break;
            default:
                assert(false);
            }
            tmCheckConsistency();
        }
        tmSetAlarm();
        uint8_t sm = sleepMode();
        set_sleep_mode(sm);
        ATOMIC_BLOCK(ATOMIC_FORCEON) {
            if (!eqEmpty()) {
                break; // ATOMIC_BLOCK is a for loop actually
            }
            sleep_enable();
            debugTrace2(debugEnterSleep, sm);
            sei();
            sleep_cpu();
            debugTrace2(debugExitSleep, sm);
            sleep_disable();
        }
    }
}

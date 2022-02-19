#include <lib/loop.h>
#include <lib/event.h>
#include <lib/event_queue.h>
#include <lib/timers.h>
#include <lib/macro_utils.h>
#include <lib/debug.h>
#include <lib/panic.h>

#include <assert.h>

#include <avr/sleep.h>
#include <util/atomic.h>

typedef void (*EventHandler)(Event* e);

static void unusedEventHandler(Event* e) { panic(); }

#define SEP ,
#define LAST_SEP
#define X(a, A, id, data, handler, sep) &handler sep

static EventHandler handlers[] = {
        &unusedEventHandler,
        EVENT_LIST
};

#undef X
#undef SEP
#undef LAST_SEP

bool processOneEvent(void) {
    if (eqEmpty()) { return false; }
    Event e;
//    debugPinOn(DEBUG_PIN_0);
    eqGet(&e);
//    debugPinOff(DEBUG_PIN_0);
    assert_(e.type < ARR_SIZE(handlers));
    handlers[e.type](&e);
    return true;
}

void tryToSleep(void) {
    uint8_t sm = sleepMode();
    if (sm == SLEEP_MODE_NONE) { return; }
    set_sleep_mode(sm);
    ATOMIC() {
        if (!eqEmpty()) {
            break; // ATOMIC_BLOCK is a for loop actually
        }
        debugTrace2(debugEnterSleep, sm);
        debugPinOff(DEBUG_PIN_1);
        sleep_enable();
        sei();
        sleep_cpu();
        sleep_disable();
        debugPinOn(DEBUG_PIN_1);
        debugTrace2(debugExitSleep, sm);
    }
}

void loop(void) {
    while (true) {
        while(processOneEvent()) {
            tmCheckConsistency();
        }
        tmSetAlarm();
        tryToSleep();
    }
}

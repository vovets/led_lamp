#include <lib/parameters.h>
#include "debouncer.h"
#include "timers.h"
#include "button.h"
#include <lib/stack_check.h>
#include "debug.h"
#include "event.h"
#include <lib/event_queue.h>
#include "loop.h"

#include <assert.h>

#include <avr/io.h>
#include <util/atomic.h>


typedef struct Debouncer {
    Timer timer;
    bool state;
    volatile uint8_t counter;
} BtnDebouncer;

static BtnDebouncer debouncer;

static void dbnTimerExpired(void*);
static void dbnStartScan(bool state);
static void dbnStopScan(void);

void handlePinChange(const Event* e) {
    dbnStartScan(btnRead());
    dbnEnable();
}

static bool dbnIsScanActive(void) {
    return debouncer.counter;
}

void dbnEnable(void) {
    GIFR |= _BV(PCIF);
    GIMSK |= _BV(PCIE);
}

void dbnDisable(void) {
    GIMSK &= ~_BV(PCIE);
    GIFR |= _BV(PCIF);
}

static inline void dbnSetTimer(void) {
    tmSetTimer(&debouncer.timer, DEBOUNCER_DELAY, dbnTimerExpired, 0);
}

static void dbnStartScan(bool state) {
    if (dbnIsScanActive()) {
        dbnStopScan();
    }
    debouncer.state = state;
    debouncer.counter = DEBOUNCER_ITERATIONS;
    dbnSetTimer();
}

static void dbnStopScan(void) {
    if (tmIsTimerSet(&debouncer.timer)) {
        tmCancelTimer(&debouncer.timer);
    }
    debouncer.counter = 0;
}

static void dbnTimerExpired(void* arg) {
    bool state = btnRead();
    if (state != debouncer.state) {
        dbnStartScan(state);
        return;
    }

    --debouncer.counter;
    debugTrace2(debugDbnCounter, debouncer.counter);
    if (!debouncer.counter) {
        btnToggle(debouncer.state);
        return;
    }

    dbnSetTimer();
}

ISR(PCINT0_vect) {
    stackCheck();
    dbnDisable();
    Event e;
    e.type = evPinChange;
    eqPutI(&e);
}

#include <lib/parameters.h>
#include <lib/debouncer.h>
#include <lib/timers.h>
#include <lib/button.h>
#include <lib/stack_check.h>
#include <lib/debug.h>
#include <lib/event.h>
#include <lib/event_queue.h>
#include <lib/loop.h>

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

void handlePinChange(Event* e) {
    dbnStartScan(btnRead());
    dbnEnable();
}

static bool dbnIsScanActive(void) {
    return debouncer.counter;
}

void dbnEnable(void) {
    // note use of '=' instead of '|="'
    GIFR = _BV(PCIF);
    GIMSK |= _BV(PCIE);
}

void dbnDisable(void) {
    GIMSK &= ~_BV(PCIE);
    GIFR = _BV(PCIF);
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
    e.data = 0;
    eqPutI(&e);
}

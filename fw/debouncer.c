#include "debouncer.h"
#include "timers.h"
#include "button.h"
#include "stack_check.h"
#include "debug.h"

#include <assert.h>

#include <avr/io.h>
#include <util/atomic.h>


typedef struct Debouncer {
    Timer timer;
    bool state;
    volatile uint8_t counter;
} BtnDebouncer;

BtnDebouncer debouncer;

static void dbnTimerExpired(void*);
static void dbnStartScan(bool state);
static void dbnStopScan(void);

static bool dbnIsScanActive(void) {
    return debouncer.counter;
}

ISR(PCINT0_vect) {
    stackCheck();
    dbnStartScan(btnRead());
}

void dbnEnable(void) {
    GIMSK |= _BV(PCIE);
}

static inline void dbnSetTimer(void) {
    stSetTimer(&debouncer.timer, DEBOUNCER_DELAY, dbnTimerExpired, 0);
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
    if (stIsTimerSet(&debouncer.timer)) {
        stCancelTimer(&debouncer.timer);
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
    if (!debouncer.counter) {
        btnToggle(debouncer.state);
        return;
    }

    dbnSetTimer();
}

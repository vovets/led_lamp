#include "timers.h"
#include "alarm.h"
#include "stack_check.h"
#include "debug.h"
#include "macro_utils.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <avr/cpufunc.h>

#include <assert.h>


#define ST_TIMER_MIN_DELAY 2

typedef struct Timers {
    SysTimePoint last;
    struct Timer* timersFirst;
    struct Timer* timersLast;
} Timers;

Timers timers;

static void stAlarm(void* arg);

static void stTimersUpdateAlarm() {
    if (stIsAlarmSet()) {
        stCancelAlarm();
    }
    if (timers.timersFirst) {
        SysTimePoint now = stNow();
        assert(timers.timersFirst->delta <= UINT16_MAX);
        assert(now - timers.last < timers.timersFirst->delta);
        SysTimeDelta delay = timers.last + timers.timersFirst->delta - now;
        stSetAlarm(delay, stAlarm, 0);
    }
}

void stSetTimer(Timer* timer, SysTimeDelta delay, TimerFunc func, void* arg) {
    assert(func);
    assert(!timer->func);
    if (delay < ST_TIMER_MIN_DELAY) { delay = ST_TIMER_MIN_DELAY; }
    SysTimePoint now = stNow();

    timer->delta = delay;
    timer->func = func;
    timer->arg = arg;
    timer->prev = 0;
    timer->next = 0;

    if (!timers.timersFirst) {
        timers.timersFirst = timer;
        timers.timersLast = timer;
        timers.last = now;
        stTimersUpdateAlarm();
        return;
    }

    // t != 0
    Timer *t = timers.timersFirst;
    SysTimeDelta nowFromLast = now - timers.last;
    // first delta in the list is referenced to sysTimeG.last
    // adjust delay accordingly as it is referenced to now
    // note uint32_t as nowFromLast + delay may become >max(SysTimeDelta)
    uint32_t delayFromLast = (uint32_t) nowFromLast + delay; // (1)
    while (t && (delayFromLast > t->delta)) {
        delayFromLast -= t->delta;
        t = t->next;
    }
    assert(delayFromLast <= UINT16_MAX);
    if (!t) {
        // we are at the end of the list
        timer->delta = delayFromLast;
        timers.timersLast->next = timer;
        timer->prev = timers.timersLast;
        timers.timersLast = timer;
        return;
    }
    // delayFromLast <= t->delta
    t->delta -= delayFromLast;
    timer->delta = delayFromLast;
    // insert timer before t
    timer->prev = t->prev;
    t->prev = timer;
    timer->next = t;
    if (timer->prev) {
        timer->prev->next = timer;
    } else {
        // first in the list
        timers.timersFirst = timer;
        stTimersUpdateAlarm();
    }
}

static inline void stAlarm(void* arg) {
    Timer* t = timers.timersFirst;
    while (t) {
        SysTimePoint now = stNow();
        SysTimeDelta nowFromLast = now - timers.last;
        if (t->delta > nowFromLast) {
            t->delta -= nowFromLast;
            timers.last = now;
            break;
        }
        // t->delta <= now - sysTimeG.last
        // remove t from waiting timers list
        timers.last += t->delta;
        timers.timersFirst = t->next;
        if (timers.timersFirst) {
            timers.timersFirst->prev = 0;
        } else {
            // removing the only element
            timers.timersLast = 0;
        }
        assert(t->func);
        TimerFunc f = t->func;
        void* arg = t->arg;
        t->func = 0;
        t->next = 0;
        t->prev = 0;
        f(arg);
        t = timers.timersFirst;
        now = stNow();
    }
    stTimersUpdateAlarm();
}

bool stIsTimerSet(Timer* timer) {
    return timer->func;
}

void stCancelTimer(Timer* timer) {
    assert(timer->func);
    timer->func = 0;
    if (timer->prev) {
        // not the first in the list
        // at any moment the sum of all deltas except first in the list <= max(SysTimeDelta)
        // so we can add any two deltas without overflow
        if (timer->next) {
            timer->next->delta += timer->delta;
            timer->next->prev = timer->prev;
        } else {
            timers.timersLast = timer->prev;
        }
        timer->prev->next = timer->next;
        timer->prev = 0;
        timer->next = 0;
        return;
    }
    // first timer in the list
    SysTimePoint now = stNow();
    SysTimePoint nowFromLast = now - timers.last;
    timers.last = now;
    if (timer->next) {
        timer->next->delta = ((uint32_t)timer->next->delta + timer->delta) - nowFromLast;
        timer->next->prev = 0;
    } else {
        timers.timersLast = 0;
    }
    timers.timersFirst = timer->next;
    timer->next = 0;
    timer->prev = 0;
    stTimersUpdateAlarm();
}

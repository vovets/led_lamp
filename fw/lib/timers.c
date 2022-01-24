#include "timers.h"
#include <lib/sys_time.h>
#include "debug.h"
#include "loop.h"

#include <util/atomic.h>
#include <avr/cpufunc.h>

#include <assert.h>


#define ST_TIMER_MIN_DELAY 1
#define TM_ALARM_MIN_DELAY 2

static TimerList timers;


void tmInit(void) {
    tlInit(&timers);
}

void tmCheckConsistency(void) {
    tlCheckConsistency(&timers);
}

void tmSetAlarm(void) {
    if (!tlIsFirstDelayModified(&timers)) {
        return;
    }

    if (tlEmpty(&timers)) {
        stCancelAlarm();
        tlClearFirstDelayIsModified(&timers);
        return;
    }

    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        SysTimePoint now = stNowI();
        SysTimeDelta nowFromBase = now - timers.base;
        SysTimeDelta firstTimerDelta = timers.first->delta;
        SysTimeDelta alarmFromNow = 0;
        if (firstTimerDelta >= nowFromBase) {
            alarmFromNow = firstTimerDelta - nowFromBase;
        }
        if (alarmFromNow < TM_ALARM_MIN_DELAY) { alarmFromNow = TM_ALARM_MIN_DELAY; }
        stSetAlarmAtI(now + alarmFromNow);
        tlClearFirstDelayIsModified(&timers);
    }
}

void tmSetTimer(Timer* timer, SysTimeDelta delay, TimerFunc func, void* arg) {
    assert(func);
    assert(!timer->func);
    if (delay < ST_TIMER_MIN_DELAY) { delay = ST_TIMER_MIN_DELAY; }

    SysTimePoint now = stNow();
    timer->func = func;
    timer->arg = arg;

    tlInsert(&timers, timer, now + delay - timers.base);
    debugTrace2(debugTimerSet, (uintptr_t)timer);
}

void handleAlarm(const Event* e) {
    SysTimePoint now = stNow();
    Timer* expired = tlRebase(&timers, now);
    while (expired) {
        debugTrace2(debugTimerExpired, (uintptr_t)expired);
        TimerFunc f = expired->func;
        void* arg = expired->arg;
        expired->func = NULL;
        expired = expired->next;
        // f can be NULL if timer was canceled during
        // execution of another timer func in some previous iteration of this loop
        if (f) {
            f(arg);
        }
    }
}

bool tmIsTimerSet(Timer* timer) {
    return timer->func;
}

void tmCancelTimer(Timer* timer) {
    assert(timer->func);
    timer->func = 0;
    tlDelete(&timers, timer);
    debugTrace2(debugTimerCancel, (uintptr_t)timer);
}

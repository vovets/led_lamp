#include <lib/parameters.h>
#include <lib/timers.h>
#include <lib/sys_time.h>
#include <lib/debug.h>
#include <lib/assert_.h>
#include <lib/loop.h>
#include <lib/macro_utils.h>

#include <util/atomic.h>
#include <avr/cpufunc.h>


#define ST_TIMER_MIN_DELAY 1

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

    ATOMIC() {
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
    assert_(func);
    assert_(!timer->func);
    if (delay < ST_TIMER_MIN_DELAY) { delay = ST_TIMER_MIN_DELAY; }

    SysTimePoint now = stNow();
    timer->func = func;
    timer->arg = arg;

    tlInsert(&timers, timer, now + delay - timers.base);
    debugTrace2(debugTimerSet, (uintptr_t)timer);
}

void tmHandleAlarm(Event* e) {
//    debugPinOn(DEBUG_PIN_0);
    SysTimePoint now = stNow();
    Timer* expired = tlRebase(&timers, now);
    while (expired) {
        debugTrace2(debugTimerExpired, (uintptr_t)expired);
        TimerFunc f = expired->func;
        void* arg = expired->arg;
        Timer* next = expired->next;
        expired->func = NULL;
        expired->next = NULL;
        expired->arg = NULL;
        expired = next;

        // f can be NULL if timer was canceled during
        // execution of another timer func in some previous iteration of this loop
        if (f) {
            f(arg);
        }
    }
//    debugPinOff(DEBUG_PIN_0);
}

bool tmIsTimerSet(Timer* timer) {
    return timer->func;
}

void tmCancelTimer(Timer* timer) {
    assert_(timer->func);
    timer->func = 0;
    tlDelete(&timers, timer);
    debugTrace2(debugTimerCancel, (uintptr_t)timer);
}

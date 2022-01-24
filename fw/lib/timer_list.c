#include "timer_list.h"
#include "sys_time.h"

#include <stddef.h>
#include <assert.h>


void tlInit(TimerList* tl) {
    tl->base = 0;
    tl->first = NULL;
    tl->last = NULL;
    tl->firstDelayIsModified = false;
}

static inline void tlInsertAtBegin(TimerList* tl, Timer* timer) {
    tl->first->delta -= timer->delta;
    timer->next = tl->first;
    timer->prev = NULL;
    timer->next->prev = timer;
    tl->first = timer;
    tl->firstDelayIsModified = true;
}

static inline void tlInsertBefore(TimerList* tl, Timer* ref, Timer* timer) {
    if (!ref->prev) {
        tlInsertAtBegin(tl, timer);
        return;
    }
    ref->delta -= timer->delta;
    ref->prev->next = timer;
    timer->next = ref;
    timer->prev = ref->prev;
    ref->prev = timer;
}

static inline void tlInsertAtEnd(TimerList* tl, Timer* timer) {
    tl->last->next = timer;
    timer->prev = tl->last;
    timer->next = NULL;
    tl->last = timer;
}

void tlInsert(TimerList *tl, Timer *timer, SysTimeDelta delayFromBase) {
    timer->delta = delayFromBase;
    if (!tl->first) {
        timer->next = NULL;
        timer->prev = NULL;
        tl->first = timer;
        tl->last = timer;
        tl->firstDelayIsModified = true;
        return;
    }
    
    Timer* c = tl->first;
    while (c) {
        if (c->delta > timer->delta) {
            tlInsertBefore(tl, c, timer);
            return;
        }
        timer->delta -= c->delta;
        c = c->next;
    }
    tlInsertAtEnd(tl, timer);
}

void tlDelete(TimerList* tl, Timer* timer) {
    if (timer->next) {
        if (!timer->prev) {
            // first
            tl->first = timer->next;
            tl->firstDelayIsModified = true;
            timer->next->prev = NULL;
            timer->next->delta += timer->delta;
            goto end;
        }
        // in the middle
        timer->next->prev = timer->prev;
        timer->prev->next = timer->next;
        timer->next->delta += timer->delta;
        goto end;
    }
    // last
    tl->last = timer->prev;
    if (timer->prev) {
        timer->prev->next = NULL;
    } else {
        tl->first = NULL;
    }
 end:
    timer->prev = NULL;
    timer->next = NULL;
}

Timer* tlRebase(TimerList* tl, SysTimePoint newBase) {
    Timer* expiredFirst = NULL;
    Timer* expiredLast = NULL;
    if (tlEmpty(tl)) {
        goto end;
    }
    SysTimeDelta delta = newBase - tl->base;
    Timer* c = tl->first;
    while (c) {
        if (c->delta > delta) {
            c->delta -= delta;
            break;
        }
        Timer* next = c->next;
        tlDelete(tl, c);
        if (!expiredLast) {
            expiredFirst = expiredLast = c;
        } else {
            expiredLast->next = c;
            expiredLast = c;
        }
        c = next;
    }
    end:
    tl->base = newBase;
    tl->firstDelayIsModified = true;
    return expiredFirst;
}

void tlCheckConsistency(const TimerList* tl) {
    const Timer* c = tl->first;
    const Timer* prev = NULL;
    while (c) {
        assert(c->prev == prev);
        assert(c->func);
        prev = c;
        c = c->next;
    }
    assert(tl->last == prev);
}
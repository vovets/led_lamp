#pragma once

#include "sys_time.h"

#include <stdint.h>
#include <stdbool.h>

typedef uint32_t TimerDelta;

typedef void (*TimerFunc)(void* arg);

typedef struct Timer {
    struct Timer* next;
    struct Timer* prev;
    TimerDelta delta;
    TimerFunc func;
    void* arg;
} Timer;

typedef struct TimerList {
    SysTimePoint base;
    struct Timer* first;
    struct Timer* last;
    bool firstDelayIsModified;
} TimerList;

void tlInit(TimerList* tl);

void tlInsert(TimerList *tl, Timer *timer, SysTimeDelta delayFromBase);

void tlDelete(TimerList* tl, Timer* timer);

Timer* tlRebase(TimerList* tl, SysTimePoint newBase);

static inline bool tlEmpty(const TimerList* tl) { return !tl->first; }

static inline void tlClearFirstDelayIsModified(TimerList* tl) { tl->firstDelayIsModified = false; }

static inline bool tlIsFirstDelayModified(const TimerList* tl) { return tl->firstDelayIsModified; }

void tlCheckConsistency(const TimerList* tl);
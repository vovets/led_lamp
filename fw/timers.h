#pragma once

#include "alarm.h"

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


void stSetTimer(Timer* timer, SysTimeDelta delay, TimerFunc func, void* arg);

bool stIsTimerSet(Timer* timer);

void stCancelTimer(Timer* timer);

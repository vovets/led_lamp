#pragma once

#include <stdint.h>
#include <stdbool.h>


#ifndef ST_FREQ_DIVIDER
#error please define ST_FREQ_DIVIDER as 1..1024, power of two
#endif
#define ST_PERIOD_US ((ST_FREQ_DIVIDER * 1000UL) / (F_CPU / 1000UL))
#define ST_US2TICKS(US) (US / ST_PERIOD_US)
#define ST_MS2TICKS(MS) ST_US2TICKS(MS * 1000UL)

typedef uint16_t SysTimePoint;

typedef uint16_t SysTimeDelta;

typedef void (*AlarmFunc)(void* arg);


void stInit(void);

void stEnableClock(void);

void stDisableClock(void);

SysTimePoint stNow(void);

void stSetAlarm(SysTimePoint t, AlarmFunc f, void* arg);

void stCancelAlarm(void);

bool stIsAlarmSet(void);

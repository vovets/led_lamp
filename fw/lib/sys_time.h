#pragma once

#include <lib/parameters.h>
#include <lib/sys_time.h>

#include <stdint.h>
#include <stdbool.h>

typedef uint16_t SysTimePoint;
typedef uint16_t SysTimeDelta;

#define ST_PERIOD_US ((ST_FREQ_DIVIDER * 1000ULL) / (F_CPU / 1000ULL))
#define ST_US2TICKS(US) (US / ST_PERIOD_US)
#define ST_MS2TICKS(MS) ST_US2TICKS((MS * 1000ULL))

typedef void (*AlarmFunc)(void* arg);


void stInit(void);

void stEnableClock(void);

void stDisableClock(void);

SysTimePoint stNow(void);

SysTimePoint stNowI(void);

void stSetAlarmAt(SysTimePoint t);

void stSetAlarmAtI(SysTimePoint t);

void stCancelAlarm(void);

bool stIsAlarmSet(void);

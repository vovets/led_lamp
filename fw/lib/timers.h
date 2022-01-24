#pragma once

#include <lib/sys_time.h>
#include <lib/timer_list.h>

#include <stdint.h>
#include <stdbool.h>


void tmInit(void);

void tmSetTimer(Timer* timer, SysTimeDelta delay, TimerFunc func, void* arg);

bool tmIsTimerSet(Timer* timer);

void tmCancelTimer(Timer* timer);

void tmSetAlarm(void);

void tmCheckConsistency(void);

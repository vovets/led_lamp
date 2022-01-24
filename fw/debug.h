#pragma once

#include <lib/timers.h>
#include "event.h"

#include <stdint.h>
#include <stdbool.h>

#include <avr/io.h>

#define DEBUG_TRACE_BUFFER_SIZE 20
#define DEBUG_PIN PB0

typedef enum DebugEventId {
    debugEvPut        = 0,
    debugEvGet        = 1,
//    debugPinChangeEvPut    = 2,
//    debugPinChangeEvGet    = 3,
//    debugAdcEvPut          = 4,
//    debugAdcEvGet          = 5,
    debugBtnToggle       = 6,
    debugBtnEvent        = 7,
    debugDbnCounter      = 8,
    debugTimerExpired    = 9,
    debugTimerSet        = 10,
    debugTimerCancel     = 11,
    debugAlarmEnabled    = 12,
    debugAlarmDisabled   = 13,
    debugEnterSleep      = 14,
    debugExitSleep       = 15,
    debugVccm            = 16,
    debugState           = 17,
    debugAdcStartConversion = 18,
    debugPwm             = 19
} DebugEventId;

static inline uint32_t bits(DebugEventId id) { return (uint32_t)1 << id; }

typedef union DebugEventData {
    uintptr_t uintptr;
    EventType eventType;
} DebugEventData;

void debugTraceEnableIds(uint32_t ids);

void debugTrace2(DebugEventId id, uintptr_t data);

void debugPinInit(void);

static inline void debugPin(bool state) {
    if (state) {
        PORTB |= _BV(DEBUG_PIN);
    } else {
        PORTB &= ~_BV(DEBUG_PIN);
    }
}

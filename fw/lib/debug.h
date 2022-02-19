#pragma once

#include <debug_event_ids.h>

#include <lib/timers.h>
#include <lib/event.h>
#include <lib/panic.h>

#include <stdint.h>
#include <stdbool.h>

#include <avr/io.h>

static inline uint32_t bits(DebugEventId id) { return (uint32_t)1 << id; }

typedef union DebugEventData {
    uintptr_t uintptr;
    EventType eventType;
} DebugEventData;

void debugTraceEnableIds(uint32_t ids);

#if DEBUG_TRACE_BUFFER_SIZE != 0
void debugTrace2(DebugEventId id, uintptr_t data);
#else
#define debugTrace2(X, Y) (void)0
#endif

void debugPinInit(void);

#if DEBUG_PIN_0_ENABLED || DEBUG_PIN_1_ENABLED
#define debugPinOn(PIN) do { PORTB |= _BV(PIN); } while (false)
#define debugPinOff(PIN) do { PORTB &= ~_BV(PIN); } while (false)
#else
#define debugPinOn(PIN) (void)0
#define debugPinOff(PIN) (void)0
#endif

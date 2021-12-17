#pragma once

#include "timers.h"

#include <stdint.h>
#include <stdbool.h>

#include <avr/io.h>

#define DEBUG_TRACE_BUFFER_SIZE 16
#define DEBUG_PIN PB0


void debugTrace(uintptr_t id);
void debugPinInit(void);
static inline void debugPin(bool state) {
    if (state) {
        PORTB |= _BV(DEBUG_PIN);
    } else {
        PORTB &= ~_BV(DEBUG_PIN);
    }
}

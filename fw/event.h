#pragma once

#include <lib/sys_time.h>

#include <stdint.h>


typedef enum {
    evUnused = 0,
    evAlarm = 1,
    evPinChange = 2,
    evAdc = 3
} EventType;

typedef struct Event {
    EventType type;
    SysTimePoint time;
    union {
        struct Alarm {
        } alarm;
        
        struct PinChange {
        } pinChange;
        
        struct Adc {
            uint16_t value;
        } adc;
    };
} Event;

static inline void evCopy(const Event* src, Event* dst) {
    *dst = *src;
}

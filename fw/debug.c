#include "debug.h"
#include "timers.h"

#include <avr/io.h>


typedef struct DebugTraceEvent {
    uintptr_t id;
    SysTimePoint time;
} DebugTraceEvent;

typedef struct DebugTraceBuffer {
    uint8_t head;
    DebugTraceEvent buffer[DEBUG_TRACE_BUFFER_SIZE];
} DebugTraceBuffer;

DebugTraceBuffer buffer;

void debugTrace(uintptr_t id) {
    DebugTraceEvent* e = &buffer.buffer[buffer.head];
    e->id = id;
    e->time = stNow();
    buffer.head = (buffer.head + 1) % DEBUG_TRACE_BUFFER_SIZE;
//    if (!buffer.head) {
//        abort();
//    }
}

void debugPinInit(void) {
    DDRB |= _BV(DEBUG_PIN);
}

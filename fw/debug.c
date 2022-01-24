#include "debug.h"
#include <lib/timers.h>

#include <avr/io.h>
#include <avr/cpufunc.h>
#include <util/atomic.h>


typedef struct DebugTraceEvent {
    DebugEventId id;
    DebugEventData data;
    SysTimePoint time;
} DebugTraceEvent;

typedef struct DebugTraceBuffer {
    uint32_t enabledEvents;
    uint8_t head;
    DebugTraceEvent buffer[DEBUG_TRACE_BUFFER_SIZE];
} DebugTraceBuffer;

static DebugTraceBuffer debugTraceBuffer;


void debugTraceEnableIds(uint32_t ids) {
    debugTraceBuffer.enabledEvents |= ids;
}

void debugTrace2(DebugEventId id, uintptr_t data) {
    if (!(debugTraceBuffer.enabledEvents & bits(id))) {
        return;
    }
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        DebugTraceEvent *e = &debugTraceBuffer.buffer[debugTraceBuffer.head];
        e->id = id;
        e->data.uintptr = data;
        e->time = stNow();
        debugTraceBuffer.head = (debugTraceBuffer.head + 1) % DEBUG_TRACE_BUFFER_SIZE;
//    if (!buffer.head) {
//        abort();
//    }
    }
}

void debugPinInit(void) {
    DDRB |= _BV(DEBUG_PIN);
}

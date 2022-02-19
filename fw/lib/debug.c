#include <lib/debug.h>
#include <lib/timers.h>
#include <lib/macro_utils.h>

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

#if DEBUG_TRACE_BUFFER_SIZE != 0
void debugTrace2(DebugEventId id, uintptr_t data) {
    if (!(debugTraceBuffer.enabledEvents & bits(id))) {
        return;
    }
    ATOMIC() {
        DebugTraceEvent *e = &debugTraceBuffer.buffer[debugTraceBuffer.head];
        e->id = id;
        e->data.uintptr = data;
        e->time = stNowI();
        advance(debugTraceBuffer.head, DEBUG_TRACE_BUFFER_SIZE);
//    if (!buffer.head) {
//        panic();
//    }
    }
}
#endif // DEBUG_TRACE_BUFFER_SIZE != 0

void debugPinInit(void) {
#if DEBUG_PIN_0_ENABLED
    DDRB |= _BV(DEBUG_PIN_0);
#endif
#if DEBUG_PIN_1_ENABLED
    DDRB |= _BV(DEBUG_PIN_1);
#endif
}

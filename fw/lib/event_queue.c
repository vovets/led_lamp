#include <lib/parameters.h>
#include "event_queue.h"
#include "debug.h"
#include <lib/sys_time.h>

#include <stdbool.h>
#include <assert.h>

#include <util/atomic.h>


typedef struct EventQueue {
    Event buffer[EQ_QUEUE_SIZE];
    uint8_t putIndex;
    uint8_t getIndex;
} EventQueue;

static EventQueue eqQueue;

inline bool eqEmpty(void) {
    return eqQueue.buffer[eqQueue.getIndex].type == evUnused;
}

inline bool eqFull(void) {
    return eqQueue.buffer[eqQueue.putIndex].type != evUnused;
}

static inline void advance(uint8_t* index) {
    *index = (*index + 1) % EQ_QUEUE_SIZE;
}

void eqPutI(const Event* event) {
    assert(!eqFull());
    assert(event->type != evUnused);
    evCopy(event, &eqQueue.buffer[eqQueue.putIndex]);
    eqQueue.buffer[eqQueue.putIndex].time = stNowI();
    debugTrace2(debugEvPut, event->type);
    advance(&eqQueue.putIndex);
}

void eqGet(Event* event) {
    assert(!eqEmpty());
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        debugTrace2(debugEvGet, eqQueue.buffer[eqQueue.getIndex].type);
        evCopy(&eqQueue.buffer[eqQueue.getIndex], event);
        eqQueue.buffer[eqQueue.getIndex].type = evUnused;
        advance(&eqQueue.getIndex);
    }    
}

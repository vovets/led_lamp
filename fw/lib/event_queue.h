#pragma once

#include <lib/event.h>
#include <lib/debug.h>
#include <lib/assert_.h>
#include <lib/macro_utils.h>

#include <stdbool.h>

#include <util/atomic.h>


typedef struct EventQueue {
    Event buffer[EQ_QUEUE_SIZE];
    Event* putPtr;
    Event* getPtr;
} EventQueue;

extern EventQueue eqQueue;


void eqInit(void);
static inline void eqPutI(Event* event) __attribute__((always_inline));
static inline void eqGet(Event* event);
static inline bool eqEmpty(void);
static inline bool eqFull(void);

bool eqEmpty(void) {
    return eqQueue.getPtr->type == evUnused;
}

bool eqFull(void) {
    return eqQueue.putPtr->type != evUnused;
}

#define eqAdvance(ptr) \
do { ++ptr; if (ptr == &eqQueue.buffer[0] + EQ_QUEUE_SIZE) { ptr = &eqQueue.buffer[0]; } } while (false)

void eqPutI(Event* event) {
//    debugPinOn(DEBUG_PIN_0);
    assert_(!eqFull());
    assert_(event->type != evUnused);
    event->time = stNowI();
    evCopy(event, eqQueue.putPtr);
    eqAdvance(eqQueue.putPtr);
    debugTrace2(debugEvPut, event->type);
//    debugPinOff(DEBUG_PIN_0);
}

static inline void eqGet(Event* event) {
    assert_(!eqEmpty());
    ATOMIC() {
        evCopy(eqQueue.getPtr, event);
        eqQueue.getPtr->type = evUnused;
        eqAdvance(eqQueue.getPtr);
        debugTrace2(debugEvGet, eqQueue.getPtr->type);
//        debugPinOff(DEBUG_PIN_0);
    }
}

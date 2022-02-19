#include <lib/parameters.h>
#include <lib/event_queue.h>


EventQueue eqQueue;

void eqInit(void) {
    eqQueue.putPtr = &eqQueue.buffer[0];
    eqQueue.getPtr = &eqQueue.buffer[0];
}

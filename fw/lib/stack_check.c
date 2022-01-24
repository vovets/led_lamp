#include "stack_check.h"

#include <avr/io.h>

__attribute__((naked,section(".init3")))
void fillStack(void) {
    register char* ptr;
    for (ptr = &__heap_end; ptr < (char*)RAMEND; ++ptr) {
        *ptr = 0x55;
    }
}

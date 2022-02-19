#include "stack_check.h"

#include <avr/io.h>

__attribute__((naked,section(".init3")))
void fillStack(void) {
    __heap_end[0] = 0x55U;
    __heap_end[1] = 0x55U;
    __heap_end[2] = 0x55U;
    __heap_end[3] = 0x55U;
}

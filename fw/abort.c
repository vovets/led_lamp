#include "break.h"

#include <util/delay_basic.h>
#include <avr/interrupt.h>
#include <avr/cpufunc.h>

void abort() {
    static volatile uint8_t counter = 0;
    cli();
    _NOP();
    while (1) {
        ++counter;
        _delay_loop_1(3);
    }
}

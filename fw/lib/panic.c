#include <lib/panic.h>

#include <util/delay_basic.h>
#include <avr/interrupt.h>
#include <avr/cpufunc.h>

void panic(void) {
    cli();
    _NOP();
    while (1) {
        _delay_loop_1(UINT8_MAX);
    }
}

#include "clocks_etc.h"
#include <lib/macro_utils.h>

#include <avr/io.h>
#include <avr/power.h>
#include <util/atomic.h>


#define CLK_DIV_1000000 clock_div_8
#define CLK_DIV_2000000 clock_div_4
#define CLK_DIV_4000000 clock_div_2
#define CLK_DIV_8000000 clock_div_1

#define CLK_DIV LL_CAT(CLK_DIV_, F_CPU)

void setupClock(void) {
    clock_prescale_set(CLK_DIV);
    // disable analog comparator
    ACSR |= _BV(ACD);
}

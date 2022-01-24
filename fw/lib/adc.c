#include <lib/parameters.h>
#include "adc.h"
#include "stack_check.h"
#include "event.h"
#include "event_queue.h"
#include "debug.h"
#include "macro_utils.h"

#include <assert.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#define ADC_DIV_TO_ADPS(DIVISOR) LL_CAT(ADC_DIV_, DIVISOR)
#define ADC_ADPS_MASK (_BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0))
#define ADC_ADPS_BITS (ADC_DIV_TO_ADPS(ADC_FREQ_DIVIDER) << ADPS0)

#define ADC_DIV_128 (_BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0))
#define ADC_DIV_64  (_BV(ADPS2) | _BV(ADPS1)             )
#define ADC_DIV_32  (_BV(ADPS2)              | _BV(ADPS0))
#define ADC_DIV_16  (_BV(ADPS2)                          )
#define ADC_DIV_8   (             _BV(ADPS1) | _BV(ADPS0))

void adcEnable(void) {
    PRR &= ~_BV(PRADC);
    ADMUX = ADC_ADMUX_VALUE;
    DIDR0  |= _BV(ADC3D);
    ADCSRA = (ADCSRA & ~ADC_ADPS_MASK) | ADC_ADPS_BITS;
    ADCSRA |= _BV(ADEN);
}

void adcDisable(void) {
    ADCSRA &= _BV(ADEN);
    PRR |= _BV(PRADC);
}

static inline void enableAdcInt(void) {
    ADCSRA |= _BV(ADIE);
}

static inline void disableAdcInt(void) {
    ADCSRA &= ~_BV(ADIE);
}

void adcStartConversion(void) {
    enableAdcInt();
    ADCSRA |= _BV(ADSC);
    debugTrace2(debugAdcStartConversion, 0);
}

ISR(ADC_vect) {
    stackCheck();
    disableAdcInt();
    uint8_t l = ADCL;
    Event e;
    e.type = evAdc;
    e.adc.value = (ADCH << 8) | l;
    eqPutI(&e);
}

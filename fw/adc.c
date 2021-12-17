#include "adc.h"

#include <assert.h>

#include <avr/io.h>
#include <avr/interrupt.h>


//#define ADC_PIN PB3

typedef struct AdcState {
    AdcConversionFinished func;
    void* arg;
} AdcState;

static AdcState adcState;

void adcEnable(uint8_t admuxValue) {
    PRR &= ~_BV(PRADC);
    if (!admuxValue) {
        ADMUX = _BV(MUX1) | _BV(MUX0);
    } else {
        ADMUX = admuxValue;
    }
    DIDR0  |= _BV(ADC3D);

//    ADCSRA |= _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
//    ADCSRA |= _BV(ADPS2) | _BV(ADPS1);
//    ADCSRA |= _BV(ADPS2) | _BV(ADPS0);
    ADCSRA |= _BV(ADPS2);
//    ADCSRA |= _BV(ADPS1) | _BV(ADPS0);

    ADCSRA |= _BV(ADEN);
}

void adcDisable(void) {
    ADCSRA &= _BV(ADEN);
    PRR |= _BV(PRADC);
    adcState.func = 0;
}

void adcStartConversion(AdcConversionFinished func, void* arg) {
    assert(func);
    assert(!adcState.func);
    adcState.func = func;
    adcState.arg = arg;
    ADCSRA |= _BV(ADIE);
    ADCSRA |= _BV(ADSC);
}

ISR(ADC_vect) {
    ADCSRA &= ~_BV(ADIE);
    assert(adcState.func);
    uint8_t l = ADCL;
    uint16_t result = (ADCH << 8) | l;
    AdcConversionFinished func = adcState.func;
    adcState.func = 0;
    func(adcState.arg, result);
}

#include <lib/parameters.h>
#include <lib/pwm.h>
#include <lib/macro_utils.h>
#include "debug.h"

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

#define PWM_DIV_0       0
#define PWM_DIV_1       1
#define PWM_DIV_2       2
#define PWM_DIV_4       3
#define PWM_DIV_8       4
#define PWM_DIV_512     10
#define PWM_DIV_1024    11
#define PWM_DIV_2048    12
#define PWM_DIV_4096    13
#define PWM_DIV_8192    14
#define PWM_DIV_16384   15

#define PWM_DIV_TO_CS(DIVISOR) LL_CAT(PWM_DIV_, DIVISOR)
#define PWM_CS_MASK (_BV(CS13) | _BV(CS12) | _BV(CS11) | _BV(CS10))
#define PWM_CS_BITS (PWM_DIV_TO_CS(PWM_FREQ_DIVIDER) << CS10)
#define PWM_OC_MASK 255U

static void pwmSetPrescaler(bool prescalerEnabled) {
    if (prescalerEnabled) {
        PLLCSR |= _BV(PCKE);
        TCCR1 = (TCCR1 & ~PWM_CS_MASK) | PWM_CS_BITS;
    } else {
        TCCR1 = (TCCR1 & ~PWM_CS_MASK);
        PLLCSR &= ~_BV(PCKE);
    }
}

static void pwmSetPLL(bool pllEnabled) {
    if (pllEnabled) {
        PLLCSR |= _BV(PLLE);
        _delay_us(100.);
    } else {
        PLLCSR &= ~_BV(PLLE);
    }
}

static void pwmWaitPLLReady(void) {
    while (!(PLLCSR & _BV(PLOCK))) {}
}

static void pwmSetOutput(bool outputConnected) {
    if (outputConnected) {
        TCCR1 |= _BV(COM1A1);
        TCCR1 &= ~_BV(COM1A0);
    } else {
        TCCR1 &= ~(_BV(COM1A1) | _BV(COM1A0));
    }
}

void pwmInit(void) {
    TCCR1 |= _BV(PWM1A);
    OCR1C = PWM_OC_MASK;
    PLLCSR |= _BV(LSM);
    pwmSetPLL(true);
    pwmWaitPLLReady();
}

void pwmEnable(void) {
    pwmWaitPLLReady();
    pwmSetPrescaler(true);
    pwmSetOutput(true);
}

void pwmDisable(void) {
    pwmSetOutput(false);
    pwmSetPrescaler(false);
}

void pwmSet(uint8_t v) {
    debugTrace2(debugPwm, v);
    OCR1A = v & PWM_OC_MASK;
}

uint8_t pwmGet(void) {
    return OCR1A & PWM_OC_MASK;
}

bool pwmIsEnabled(void) {
    return TCCR1 & PWM_CS_MASK;
}

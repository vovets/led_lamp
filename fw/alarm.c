#include "alarm.h"
#include "macro_utils.h"
#include "stack_check.h"

#include <avr/io.h>
#include <avr/interrupt.h>

#include <assert.h>
#include <string.h>

#define ST_DIV_0       0
#define ST_DIV_1       1
#define ST_DIV_8       2
#define ST_DIV_64      3
#define ST_DIV_256     4
#define ST_DIV_1024    5

#define ST_DIV_TO_CS(DIVISOR) LL_CAT(ST_DIV_, DIVISOR)
#define ST_CS_MASK (_BV(CS02) | _BV(CS01) | _BV(CS00))
#define ST_CS_BITS (ST_DIV_TO_CS(ST_FREQ_DIVIDER) << CS00)

#define ST_MIN_DELAY 3

typedef struct SysTime {
    volatile uint8_t timeH;
    uint8_t alarmH;
    AlarmFunc alarmFunc;
    void* alarmArg;
    uint16_t periodUs; // This is for debug purposes only, never used anywhere
} SysTime;

// zero-init is ok
static SysTime sysTime;

static void disableOCInt(void) {
    TIMSK &= ~_BV(OCIE0A);
//    debugPin(false);
}

static void enableOCInt(void) {
    TIMSK |= _BV(OCIE0A);
//    debugPin(true);
}

bool stIsAlarmSet(void) {
    return sysTime.alarmFunc;
}

ISR(TIMER0_OVF_vect) {
    stackCheck();
    ++sysTime.timeH;
}

ISR(TIMER0_COMPA_vect) {
//    debugPin(true);
    disableOCInt();
    stackCheck();
    if (sysTime.timeH == sysTime.alarmH) {
        AlarmFunc func = sysTime.alarmFunc;
        void* arg = sysTime.alarmArg;
        stCancelAlarm();
        assert(func);
        func(arg);
    } else {
        enableOCInt();
    }
//    debugPin(false);
}

void stInit(void) {
    memset(&sysTime, 0, sizeof(SysTime));
    sysTime.periodUs = ST_PERIOD_US;
    TCNT0 = 0;
    OCR0A = 0;
}


void stEnableClock(void) {
    TCCR0B = (TCCR0B & ~ST_CS_MASK) | ST_CS_BITS;
    TIMSK |= _BV(TOIE0);
}

void stDisableClock() {
    TCCR0B = (TCCR0B & ~ST_CS_MASK);
}

SysTimePoint stNow(void) {
    SysTimePoint retval;
    uint8_t f = (TIFR & _BV(TOV0)) >> TOV0;
    retval = ((uint16_t)(sysTime.timeH + f) << 8) | TCNT0;
    return retval;
}

void stSetAlarm(SysTimeDelta delayFromNow, AlarmFunc f, void* arg) {
    SysTimePoint now = stNow();
    assert(!stIsAlarmSet());
    if (delayFromNow < ST_MIN_DELAY) delayFromNow = ST_MIN_DELAY;
    SysTimePoint alarmTime = now + delayFromNow;
    sysTime.alarmH = alarmTime >> 8;
    sysTime.alarmFunc = f;
    sysTime.alarmArg = arg;
    // According to datasheet:
    // "A match will set the Output Compare Flag at the next _timer_ clock cycle."
    // If we want the interrupt to occur at TCNT0 == N, we must set OCR0A = N - 1.
    // Note that we cannot set OCR0A to current TCNT0 because that will not cause interrupt.
    uint8_t alarmCounter = (alarmTime - 1) & 0xffU;
    OCR0A = alarmCounter;
    enableOCInt();
}

void stCancelAlarm(void) {
    assert(sysTime.alarmFunc);
    disableOCInt();
    sysTime.alarmFunc = 0;
}

#include <lib/sys_time.h>
#include "macro_utils.h"
#include "stack_check.h"
#include "event.h"
#include "event_queue.h"
#include "debug.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/cpufunc.h>
#include <util/atomic.h>

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

typedef struct SysTime {
    uint8_t timeH;
    uint8_t alarmH;
    uint16_t periodUs; // This is for debug purposes only, never used anywhere
} SysTime;

// zero-init is ok
static SysTime sysTime;

static inline void disableOCInt(void) {
    TIMSK &= ~_BV(OCIE0A);
//    debugPin(false);
}

static inline void enableOCInt(void) {
    TIMSK |= _BV(OCIE0A);
//    debugPin(true);
}

static inline void clearOCIntFlag(void) {
    TIFR |= _BV(OCF0A);
}

static inline uint8_t OVFIntFlag(void) {
    return (TIFR & _BV(TOV0)) ? 1U : 0U;
}

inline bool stIsAlarmSet(void) {
    return TIMSK & _BV(OCIE0A);
}

inline SysTimePoint stNowI(void) {
    return ((uint16_t)(sysTime.timeH + OVFIntFlag()) << 8) | TCNT0;
}

ISR(TIMER0_OVF_vect) {
    stackCheck();
    ++sysTime.timeH;
}

ISR(TIMER0_COMPA_vect) {
//    debugPin(true);
    disableOCInt();
    stackCheck();
    if (sysTime.timeH != sysTime.alarmH) {
        enableOCInt();
        return;
    }
    Event e;
    e.type = evAlarm;
    eqPutI(&e);
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
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        retval = stNowI();
    }
    return retval;
}

void stSetAlarmAtI(SysTimePoint t) {
    // According to datasheet:
    // "A match will set the Output Compare Flag at the next _timer_ clock cycle."
    // If we want the interrupt to occur at TCNT0 == N, we must set OCR0A = N - 1.
    // Note that setting OCR0A to current TCNT0 will not cause immediate interrupt.
    clearOCIntFlag();
    OCR0A = (t & 0xffU) - 1U;
    sysTime.alarmH = t >> 8U;
    debugTrace2(debugAlarmEnabled, t);
    enableOCInt();
}

void stCancelAlarm(void) {
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        if (stIsAlarmSet()) {
            disableOCInt();
            debugTrace2(debugAlarmDisabled, 0);
        }
    }
}

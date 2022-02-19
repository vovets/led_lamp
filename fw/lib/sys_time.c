#include <lib/sys_time.h>
#include <lib/macro_utils.h>
#include <lib/stack_check.h>
#include <lib/event.h>
#include <lib/event_queue.h>
#include <lib/debug.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/cpufunc.h>
#include <avr/wdt.h>
#include <util/atomic.h>
#include <util/delay.h>

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
    volatile uint8_t timeH;
    uint8_t alarmH;
    uint16_t periodUs; // This is for debug purposes only, never used anywhere
} SysTime;

// zero-init is ok
static SysTime sysTime;

#define disableOCInt() do { TIMSK &= ~_BV(OCIE0A); } while (false)
#define enableOCInt() do { TIMSK |= _BV(OCIE0A); } while (false)

// Use of = is intentional, writing zero will not reset any set flags nor set any.
// If we use |= operator then compiler generates something like this:
// 00000450 <stSetAlarmAtI>:
// 450:   28 b7           in      r18, 0x38       ; 56
// 452:   28 60           ori     r18, 0x08       ; 8
// 454:   28 bf           out     0x38, r18       ; 56
// But this fragment will unintentionally reset _any_ already set interrupt flags
// with horrible consequences like rare and subtle bugs which are very hard to debug. :)
#define clearOCIntFlag() do { TIFR = _BV(OCF0A); } while (false)

#define disableOVFInt() do { TIMSK &= ~_BV(TOIE0); } while (false)
#define enableOVFInt() do { TIMSK |= _BV(TOIE0); } while (false)
#define clearOVFIntFlag() do { TIFR = _BV(TOV0); } while (false)

#define setOCRegister(V) do { OCR0A = (V); } while (false)

static inline uint8_t OVFIntFlag(void) {
    return (TIFR & _BV(TOV0)) ? 1U : 0U;
}

static inline bool stIsOCIntEnabled(void) { return TIMSK & _BV(OCIE0A); }

inline bool stIsAlarmSet(void) {
    return stIsOCIntEnabled();
}

ISR(TIMER0_OVF_vect) {
    debugPinOn(DEBUG_PIN_0);
//    wdt_reset();
    stackCheck();
    ++sysTime.timeH;
    debugPinOff(DEBUG_PIN_0);
}

ISR(TIMER0_COMPA_vect) {
    debugPinOn(DEBUG_PIN_0);
    disableOCInt();
    stackCheck();
    if (sysTime.timeH != sysTime.alarmH) {
        enableOCInt();
        return;
    }
    Event e;
    e.type = evAlarm;
    e.data = 0;
//    debugPinOn(DEBUG_PIN_0);
    eqPutI(&e);
//    debugPinOn(DEBUG_PIN_0);
    debugPinOff(DEBUG_PIN_0);
}

void stEnableClock(void) {
    TCCR0B = (TCCR0B & ~ST_CS_MASK) | ST_CS_BITS;
    enableOVFInt();
}

void stDisableClock() {
    disableOVFInt();
    clearOVFIntFlag();
    TCCR0B = (TCCR0B & ~ST_CS_MASK);
}

void stInit(void) {
    stDisableClock();
    TCNT0 = 0;
    setOCRegister(0);
//    OCR0B = 255;
//    TCCR0A |= _BV(COM0B0);
    disableOVFInt();
    clearOVFIntFlag();
    disableOCInt();
    clearOCIntFlag();
    memset(&sysTime, 0, sizeof(SysTime));
    sysTime.periodUs = ST_PERIOD_US;
}

inline SysTimePoint stNowI(void) {
    return ((uint16_t)(sysTime.timeH + OVFIntFlag()) << 8) | TCNT0;
}

SysTimePoint stNow(void) {
    SysTimePoint retval;
    ATOMIC() {
        retval = stNowI();
    }
    return retval;
}

void stSetAlarmAt(SysTimePoint t) {
    ATOMIC() {
        stSetAlarmAtI(t);
    }
}

void stSetAlarmAtI(SysTimePoint t) {
    // According to datasheet:
    // "A match will set the Output Compare Flag at the next _timer_ clock cycle."
    // If we want the interrupt to occur at TCNT0 == N, we must set OCR0A = N - 1.
    // Note that setting OCR0A to current TCNT0 will not cause immediate interrupt.
    clearOCIntFlag();
    setOCRegister((t & 0xffU) - 1U);
    sysTime.alarmH = t >> 8U;
    debugTrace2(debugAlarmEnabled, t);
    enableOCInt();
}

void stCancelAlarm(void) {
    ATOMIC() {
        if (stIsAlarmSet()) {
            disableOCInt();
            clearOCIntFlag();
            debugTrace2(debugAlarmDisabled, 0);
        }
    }
}

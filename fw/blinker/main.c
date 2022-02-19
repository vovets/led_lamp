#include <lib/timers.h>
#include <lib/blinker.h>
#include <lib/clocks_etc.h>
#include <lib/debug.h>
#include <lib/loop.h>
#include <lib/event_queue.h>

#include <stdint.h>

#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/cpufunc.h>

typedef struct {
    SysTimePoint last;
} BlinkerData;

uint8_t pins[3] = { PB0, PB4, PB3 };

Blinker blinkers[3];
BlinkerData blinkerData[3];

void setupDebugTrace(void) {
    debugTraceEnableIds(
            (uint32_t)0
            //            | bits(debugEvPut)
            //            | bits(debugEvGet)
            | bits(debugAlarmEnabled)
//            | bits(debugAlarmDisabled)
//            | bits(debugEnterSleep)
//            | bits(debugExitSleep)
    );
}

void setupPins(void) {
    DDRB |= _BV(pins[0]);
    DDRB |= _BV(pins[1]);
    DDRB |= _BV(pins[2]);
}

uint8_t sleepMode(void) {
    return SLEEP_MODE_IDLE;
}

static inline void pin_(uint8_t pin, bool on) {
    if (on) {
        PORTB |= _BV(pin);
    } else {
        PORTB &= ~_BV(pin);
    }
}

void pin0(bool on) { pin_(pins[0], on); }
void pin1(bool on) { pin_(pins[1], on); }
void pin2(bool on) { pin_(pins[2], on); }

void setupBlinkers() {
    blinkerSetup(&blinkers[0], BlinkerModeOnThenOff, 1, ST_MS2TICKS(10), ST_MS2TICKS(10), &pin0);
    blinkerSetup(&blinkers[1], BlinkerModeOnThenOff,  1, ST_MS2TICKS(1), ST_MS2TICKS(20), &pin1);
    blinkerSetup(&blinkers[2], BlinkerModeOnThenOff,  1, ST_US2TICKS(500), ST_US2TICKS(19500), &pin2);
}

void blinkerFinish(Blinker* blinker, void* arg);

void startBlinkers() {
    SysTimePoint now = stNow();
    blinkerData[0].last = now;
    blinkerData[1].last = now;
    blinkerData[2].last = now;
    blinkerStart(&blinkers[0], blinkerFinish, &blinkerData[0]);
    blinkerStart(&blinkers[1], blinkerFinish, &blinkerData[1]);
    blinkerStart(&blinkers[2], blinkerFinish, &blinkerData[2]);
}

void blinkerFinish(Blinker* blinker, void* arg) {
    SysTimePoint now = stNow();
    BlinkerData* d = (BlinkerData*)arg;
    assert_(now - d->last <= blinker->state_0_time + blinker->state_1_time + 3);
    d->last = now;
    blinkerStart(blinker, blinkerFinish, arg);
}

int main(void)
{
    setupDebugTrace();
    debugPinInit();
    setupClock();
    setupPins();
    eqInit();
    stInit();
    tmInit();
    setupBlinkers();
    startBlinkers();
//    WDTCR |= (_BV(WDP0));
//    WDTCR |= _BV(WDIE);
    sei();
    stEnableClock();
    loop();
}

//ISR(WDT_vect) {
//    _NOP();
//}

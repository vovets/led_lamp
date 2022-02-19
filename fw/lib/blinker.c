#include <lib/blinker.h>
#include <lib/assert_.h>

#include <avr/cpufunc.h>


static void blinkerTimerExpired(void* arg) {
    Blinker* blinker = (Blinker*)arg;
    assert_(blinker->state);
    blinker->state(blinker);
}

static void blinkerState_1(Blinker* blinker);

static void blinkerState_0(Blinker* blinker) {
    // this function is called when state 0 ends
    blinker->state = blinkerState_1;
    tmSetTimer(&blinker->timer, blinker->state_1_time, blinkerTimerExpired, blinker);
    blinker->ledFunc(blinker->mode == BlinkerModeOnThenOff ? false : true);
}

static void blinkerState_1(Blinker* blinker) {
    // this function is called when state 1 ends
    if (blinker->iterations) {
        --blinker->iterationsLeft;
        if (!blinker->iterationsLeft) {
            blinker->state = 0;
            if (blinker->finishedFunc) {
                blinker->finishedFunc(blinker, blinker->finishedArg);
            }
            return;
        }
    }
    blinker->state = blinkerState_0;
    blinker->ledFunc(blinker->mode == BlinkerModeOnThenOff ? true : false);
    tmSetTimer(&blinker->timer, blinker->state_0_time, blinkerTimerExpired, blinker);
}

void blinkerStart(Blinker* blinker, BlinkerFunc func, void* arg) {
    blinker->finishedFunc = func;
    blinker->finishedArg = arg;
    blinker->state = blinkerState_0;
    blinker->iterationsLeft = (blinker->iterations ? blinker->iterations : 1);
    blinker->ledFunc(blinker->mode == BlinkerModeOnThenOff ? true : false);
    tmSetTimer(&blinker->timer, blinker->state_0_time, blinkerTimerExpired, blinker);
}

void blinkerStop(Blinker* blinker) {
    blinker->state = 0;
    if (tmIsTimerSet(&blinker->timer)) {
        tmCancelTimer(&blinker->timer);
        blinker->ledFunc(blinker->mode == BlinkerModeOnThenOff ? false : true);
    }
}

void blinkerSetup(Blinker* blinker, BlinkerMode mode, uint8_t iterations, SysTimeDelta state_0_time, SysTimeDelta state_1_time, BlinkerLedFunc ledFunc) {
    assert_(blinker);
    assert_(ledFunc);
    blinker->mode = mode;
    blinker->iterations = iterations;
    blinker->state_0_time = state_0_time > 0 ? state_0_time : 1;
    blinker->state_1_time = state_1_time > 0 ? state_1_time : 1;
    blinker->ledFunc = ledFunc;
}

bool blinkerIsActive(Blinker* blinker) {
    return blinker->state;
}

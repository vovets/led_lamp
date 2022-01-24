#include <lib/parameters.h>
#include "button.h"
#include <lib/timers.h>
#include "debug.h"

#include <avr/io.h>
#include <avr/cpufunc.h>


#define BTN_LONG_PRESS_TICKS ST_MS2TICKS(BTN_LONG_PRESS_MS)

typedef struct BtnState {
    BtnFunc func;
    uint8_t pin;
    bool state;
    Timer longPress;
} BtnState;

static BtnState btnState;

static void btnDown(void);
static void btnUp(void);
static void btnLongPressExpired(void* arg);

bool btnRead(void) {
    bool value = PINB & _BV(btnState.pin);
#if BTN_DOWN_IS_PIN_LOW
    return !value;
#else
    return value;
#endif
}

void btnInit(uint8_t pin, BtnFunc func) {
    btnState.pin = pin;
    btnState.func = func;
}

void btnToggle(bool stateNow) {
    debugTrace2(debugBtnToggle, stateNow);
    if (btnState.state == stateNow) {
        return;
    }
    btnState.state = stateNow;
    if (stateNow) {
        btnDown();
    } else {
        btnUp();
    }
}

static void btnDown() {
    if (tmIsTimerSet(&btnState.longPress)) {
        return;
    }
    tmSetTimer(&btnState.longPress, BTN_LONG_PRESS_TICKS, btnLongPressExpired, 0);
}

static void btnUp() {
    if (!tmIsTimerSet(&btnState.longPress)) {
        return;
    }
    tmCancelTimer(&btnState.longPress);
    btnState.func(BtnShortPress);
}

static void btnLongPressExpired(void* arg) {
    btnState.func(BtnLongPress);
}

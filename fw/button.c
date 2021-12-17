#include "button.h"
#include "timers.h"
#include "debug.h"

#include <avr/io.h>
#include <avr/cpufunc.h>

#ifndef BTN_DOWN_IS_PIN_LOW
#define BTN_DOWN_IS_PIN_LOW 0
#endif

typedef struct BtnState {
    BtnFunc func;
    uint8_t pin;
    bool state;
    Timer longPress;
} BtnState;

BtnState btnState;

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
    if (stIsTimerSet(&btnState.longPress)) {
        return;
    }
    stSetTimer(&btnState.longPress, BTN_LONG_PRESS_TICKS, btnLongPressExpired, 0);
}

static void btnUp() {
    if (!stIsTimerSet(&btnState.longPress)) {
        return;
    }
    stCancelTimer(&btnState.longPress);
    btnState.func(BtnShortPress);
}

static void btnLongPressExpired(void* arg) {
    btnState.func(BtnLongPress);
}

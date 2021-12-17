#include "timers.h"
#include "blinker.h"
#include "clocks_etc.h"
#include "button.h"
#include "debouncer.h"
#include "debug.h"
#include "stack_check.h"

#include <stdint.h>
#include <assert.h>

#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/cpufunc.h>
#include <util/atomic.h>


#define LED_PIN PB4
#define BUTTON_PIN PB2

struct State {
    bool on;
    bool blinking;
} state;

void initState(void) {
    state.blinking = false;
    state.on = false;
}

Blinker blinker;

static void shortPress(void);
static void longPress(void);

static void setupPins(void) {
    DDRB |= _BV(LED_PIN);
    PORTB |= _BV(LED_PIN);
    // disable digital input on all 5 pins except...
    DIDR0 = 0x1FU & ~_BV(BUTTON_PIN);
}

static void setupPCINT(void) {
    PCMSK |= _BV(BUTTON_PIN);
    GIMSK |= _BV(PCIE);
}

static void setupBlinker() {
    blinkerSetup(&blinker, 0, ST_MS2TICKS(40), ST_MS2TICKS(60), LED_PIN);
}

static void startBlinker() {
    if (!blinkerIsActive(&blinker)) {
        blinkerStart(&blinker, 0, 0);
    }
}

static void stopBlinker() {
    if (blinkerIsActive(&blinker)) {
        blinkerStop(&blinker);
    }
}

static void led(bool on) {
    if (!on) {
        PORTB |= _BV(LED_PIN);
    } else {
        PORTB &= ~_BV(LED_PIN);
    }
}

static void buttonEvent(BtnEvent e) {
    switch (e) {
    case BtnShortPress:
        shortPress();
        break;

    case BtnLongPress:
        longPress();
        break;

    default:
        ;
    }
}

static void update(void) {
    if (state.on) {
        if (state.blinking) {
            startBlinker();
        } else {
            stopBlinker();
            led(true);
        }
    } else {
        stopBlinker();
        led(false);
    }
}

static void shortPress(void) {
    state.on = !state.on;
    update();
}

static void longPress(void) {
    if (state.on) {
        state.blinking = !state.blinking;
        update();
        return;
    }
}

static void sleep(void) {
    if (stIsAlarmSet()) {
        set_sleep_mode(SLEEP_MODE_IDLE);
    } else {
        set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    }
    sleep_enable();
    sei();
    sleep_cpu();
    sleep_disable();
}

int main(void)
{
    initState();
    setupClockEtc();
    setupPins();
    debugPinInit();
    stInit();
    btnInit(BUTTON_PIN, buttonEvent);
    setupPCINT();
    setupBlinker();
    dbnEnable();
    sei();
    stEnableClock();
    do {
        sleep();
    } while (1);
}


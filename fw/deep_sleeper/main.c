#include <lib/timers.h>
#include <lib/blinker.h>
#include <lib/clocks_etc.h>
#include <lib/button.h>
#include <lib/debouncer.h>
#include <lib/debug.h>
#include <lib/loop.h>
#include <lib/event_queue.h>

#include <stdint.h>

#include <avr/interrupt.h>
#include <avr/sleep.h>


#define LED_PIN PB3
#define BUTTON_PIN PB2

struct State {
    bool on;
    bool blinking;
} state;

void initState(void) {
    state.blinking = false;
    state.on = false;
}

Blinker onOffBlinker;

static void shortPress(void);
static void longPress(void);

static void setupPins(void) {
    DDRB |= _BV(LED_PIN);
    PORTB |= _BV(LED_PIN);
    // disable digital input on all 5 pins except...
    DIDR0 = 0x1FU & ~_BV(BUTTON_PIN);
}

static void led(bool on) {
    if (!on) {
        PORTB |= _BV(LED_PIN);
    } else {
        PORTB &= ~_BV(LED_PIN);
    }
}

static void setupPCINT(void) {
    PCMSK |= _BV(BUTTON_PIN);
    GIMSK |= _BV(PCIE);
}

static void setupBlinker() {
    blinkerSetup(&onOffBlinker, BlinkerModeOnThenOff, 0, ST_MS2TICKS(40), ST_MS2TICKS(60), &led);
}

static void startBlinker() {
    if (!blinkerIsActive(&onOffBlinker)) {
        blinkerStart(&onOffBlinker, 0, 0);
    }
}

static void stopBlinker() {
    if (blinkerIsActive(&onOffBlinker)) {
        blinkerStop(&onOffBlinker);
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

uint8_t sleepMode(void) {
    if (stIsAlarmSet()) {
        return SLEEP_MODE_IDLE;
    } else {
        return SLEEP_MODE_PWR_DOWN;
    }
}

int main(void)
{
    initState();
    setupClock();
    setupPins();
    debugPinInit();
    stInit();
    eqInit();
    tmInit();
    btnInit(BUTTON_PIN, buttonEvent);
    setupPCINT();
    setupBlinker();
    dbnEnable();
    sei();
    stEnableClock();
    loop();
}


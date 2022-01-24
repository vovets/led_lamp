#include <lib/timers.h>
#include <lib/blinker.h>
#include "lib/clocks_etc.h"
#include <lib/button.h>
#include <lib/debouncer.h>
#include <lib/pwm.h>
#include <lib/vcc_monitor.h>
#include "debug.h"
#include <lib/stack_check.h>
#include "loop.h"
#include <lib/pwm_animator.h>

#include <stdint.h>
#include <assert.h>

#include <avr/interrupt.h>


#define BATTERY_BYPASS_PIN PB0
#define OC1A_PIN           PB1
#define SWITCH_PIN         PB2
#define LED_ON_PIN         PB3
#define REF_ON_PIN         PB4
#define LED_ON_IS_HIGH true
#define LOW_VOLTAGE_BLINK_COUNTER_INIT 5

typedef BtnFunc StateFunc;

static void stateOff(BtnEvent e);
static void stateOn(BtnEvent e);
static void stateSetup(BtnEvent e);
static void vccMonitor(uint16_t mV);
static void turnOff_1(void);

typedef struct State {
    enum StateTag {
        StateOff = 0,
        StateOn,
        StateSetup
    } state;
    uint8_t dimLevel;
    uint16_t prevVoltage; // in mV
    uint16_t lowVoltageBlinkCounter;
} State;

static StateFunc state2func[] = {
    stateOff,
    stateOn,
    stateSetup
};


static uint8_t level2dimPercent[] = {
        100, 75, 50, 25, 0
};

static const uint8_t level2dimPercentSize = sizeof(level2dimPercent) / sizeof(level2dimPercent[0]);

static State state;
static Blinker onOffBlinker;
static Blinker vccmBlinker;

static void setState(enum StateTag s) {
    debugTrace2(debugState, s);
    state.state = s;
}

void setupDebug(void) {
    debugTraceEnableIds(
            (uint32_t)0
//            | bits(debugEvPut)
//            | bits(debugEvGet)
//            | bits(debugBtnToggle)
//            | bits(debugBtnEvent)
//            | bits(debugDbnCounter)
//            | bits(debugTimerExpired)
//            | bits(debugTimerSet)
//            | bits(debugTimerCancel)
//            | bits(debugAlarmEnabled)
//            | bits(debugAlarmDisabled)
//            | bits(debugEnterSleep)
//            | bits(debugExitSleep)
//            | bits(debugVccm)
//            | bits(debugState)
//            | bits(debugAdcStartConversion)
            | bits(debugPwm)
    );
}

void initState(void) {
    state.prevVoltage = 0;
}

static void setupPins(void) {
    DDRB |= _BV(OC1A_PIN);
    DDRB |= _BV(BATTERY_BYPASS_PIN);
    DDRB |= _BV(LED_ON_PIN);
    DDRB |= _BV(REF_ON_PIN);
    // disable digital input on all 5 pins except...
    DIDR0 = 0x1FU & ~_BV(SWITCH_PIN);
}

static void setupPCINT(void) {
    PCMSK |= _BV(SWITCH_PIN);
}

static void led(bool on) {
    if (on == LED_ON_IS_HIGH) {
        PORTB |= _BV(LED_ON_PIN);
    } else {
        PORTB &= ~_BV(LED_ON_PIN);
    }
}

static void ref(bool on) {
    if (on) {
        PORTB |= _BV(REF_ON_PIN);
    } else {
        PORTB &= ~_BV(REF_ON_PIN);
    }
}

static void bypass(bool on) {
    if (on) {
        PORTB &= ~_BV(BATTERY_BYPASS_PIN);
    } else {
        PORTB |= _BV(BATTERY_BYPASS_PIN);
    }
}

static uint8_t calculatePwm(uint8_t pwmLevel) {
    uint16_t dimPercent = level2dimPercent[pwmLevel];
    return (dimPercent * 255U) / 100U;
}

static void updatePwm(void) {
    pwmaStart(calculatePwm(state.dimLevel), NULL);
}

static void updateBypass(uint16_t mV) {
    const uint8_t hist = 5;
    int16_t delta = mV - state.prevVoltage;
    if (abs(delta) <= hist) {
        return;
    }
    state.prevVoltage = mV;
    bypass(mV < 4500U);
}

static void vccmBlinkerSetup(uint8_t iterations) {
    blinkerSetup(&vccmBlinker, BlinkerModeOffThenOn, iterations, ST_MS2TICKS(50), ST_MS2TICKS(100), &led);
}

static void vccmBlinkerFinished(Blinker* blinker, void* off) {
    if (off) {
        turnOff_1();
    }
}

static void checkLowVoltage(uint16_t mV) {
    if (mV < 2700) {
        vccmBlinkerSetup(5);
        blinkerStart(&vccmBlinker, &vccmBlinkerFinished, (void*)1);
    } else if (mV >= 2700 && mV < 3100) {
        if (state.lowVoltageBlinkCounter) {
            --state.lowVoltageBlinkCounter;
        } else {
            state.lowVoltageBlinkCounter = LOW_VOLTAGE_BLINK_COUNTER_INIT;
            vccmBlinkerSetup(3);
            blinkerStart(&vccmBlinker, &vccmBlinkerFinished, (void*)0);
        }
    }
}

static void vccMonitor(uint16_t mV) {
    debugTrace2(debugVccm, mV);
    updateBypass(mV);
    checkLowVoltage(mV);
    vccmContinue(&vccMonitor);
}

static void setupBlinker(void) {
    blinkerSetup(&onOffBlinker, BlinkerModeOffThenOn, 1, ST_MS2TICKS(100), ST_MS2TICKS(400), &led);
}

static void startBlinker(void) {
    if (!blinkerIsActive(&onOffBlinker)) {
        blinkerStart(&onOffBlinker, 0, 0);
    }
}

static void stopBlinker(void) {
    if (blinkerIsActive(&onOffBlinker)) {
        blinkerStop(&onOffBlinker);
    }
}

static void turnOn(void) {
    setState(StateOn);
    ref(true);
    pwmSet(255U);
    pwmEnable();
    vccmEnable();
    vccmStart(&vccMonitor);
    led(true);
    updatePwm();
}

static void turnOff_1(void) {
    setState(StateOff);
    vccmDisable();
    stopBlinker();
    led(false);
    ref(false);
    pwmaStop();
    pwmDisable();
}

static void turnOff_0(void) {
    pwmaStart(255, &turnOff_1);
}

static void enterSetup() {
    setState(StateSetup);
    startBlinker();
}

static void exitSetup(void) {
    setState(StateOn);
    startBlinker();
}

static void nextLevel(void) {
    state.dimLevel = (state.dimLevel + 1) % level2dimPercentSize;
    updatePwm();
}

static void stateOff(BtnEvent e) {
    switch (e) {
        case BtnShortPress:
            turnOn();
            break;

        default:
            ;
    }
}

static void stateOn(BtnEvent e) {
    switch (e) {
        case BtnShortPress:
            turnOff_0();
            break;

        case BtnLongPress:
            enterSetup();
            break;

        default:
            ;
    }
}

static void stateSetup(BtnEvent e) {
    switch (e) {
        case BtnLongPress:
            exitSetup();
            break;

        case BtnShortPress:
            nextLevel();
            break;

        default:
            ;
    }
}

uint8_t sleepMode(void) {
    if (state.state == StateOff && !stIsAlarmSet()) {
        return SLEEP_MODE_PWR_DOWN;
    }
    return SLEEP_MODE_IDLE;
}

static void buttonEvent(BtnEvent e) {
    debugTrace2(debugBtnEvent, e);
    state2func[state.state](e);
}

int main(void) __attribute__ ((noreturn));

int main(void)
{
    setupDebug();
    led(false);
    bypass(false);
    initState();
    setupClock();
    setupPins();
    pwmInit();
    stInit();
    tmInit();
    btnInit(SWITCH_PIN, buttonEvent);
    setupPCINT();
    setupBlinker();
    vccmInit();
    dbnEnable();
    stEnableClock();
    sei();
    loop();
}

#include "timers.h"
#include "blinker.h"
#include "clocks_etc.h"
#include "button.h"
#include "debouncer.h"
#include "pwm.h"
#include "vcc_monitor.h"
#include "debug.h"
#include "stack_check.h"

#include <stdint.h>
#include <assert.h>

#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/cpufunc.h>
#include <util/atomic.h>
#include <util/delay.h>


#define BATTERY_BYPASS_PIN PB0
#define OC1A_PIN           PB1
#define SWITCH_PIN         PB2
#define LED_ON_PIN         PB3
#define LED_ON_IS_HIGH true


typedef BtnFunc StateFunc;

static void stateOff(BtnEvent e);
static void stateOn(BtnEvent e);
static void stateSetup(BtnEvent e);
static void vccMonitor(uint16_t mV);

typedef struct State {
    enum {
        StateOff = 0,
        StateOn,
        StateSetup
    } state;
    uint8_t pwmLevel;
    uint16_t supplyVoltage; // in mV units
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
static Blinker blinker;


void initState(void) {
    state.supplyVoltage = 0;
}

static void setupPins(void) {
    DDRB |= _BV(OC1A_PIN);
    DDRB |= _BV(BATTERY_BYPASS_PIN);
    DDRB |= _BV(LED_ON_PIN);
    // disable digital input on all 5 pins except...
    DIDR0 = 0x1FU & ~_BV(SWITCH_PIN);
}

static void setupPCINT(void) {
    PCMSK |= _BV(SWITCH_PIN);
    GIMSK |= _BV(PCIE);
}

static void led(bool on) {
    if (on == LED_ON_IS_HIGH) {
        PORTB |= _BV(LED_ON_PIN);
    } else {
        PORTB &= ~_BV(LED_ON_PIN);
    }
}

//static uint8_t calculatePwm(uint8_t pwmLevel) {
//    static const uint16_t supplyNominal = 5000U; // mV
//    static const uint16_t vpwmMax = 2491U; // mV
//    static const uint16_t perCountNominal = (174U << 8) / 10U; // fixed 8.8, mV/count
//    uint8_t dimPercent = level2dimPercent[pwmLevel];
//    uint32_t pwmNominal = ((uint32_t)vpwmMax << 16) / perCountNominal; // fixed 24.8
//    uint32_t supplyFactor = (((uint32_t)supplyNominal << 16) / state.supplyVoltage); // fixed 16.16
//    uint16_t dimFactor = ((uint32_t)dimPercent << 8) / 100; // fixed 8.8
//    uint32_t factor = ((supplyFactor * dimFactor) >> 8); // fixed 16.16
//    return (factor * pwmNominal) >> 24;
//}

static uint8_t calculatePwm(uint8_t pwmLevel) {
    static const uint16_t supplyNominal = 3000U; // mV
    static const uint16_t vpwmMax = 2600U; // mV
    static const uint16_t perCountNominal = supplyNominal; // fixed 8.8, mV/count
    uint8_t dimPercent = level2dimPercent[pwmLevel];
    uint32_t pwmNominal = ((uint32_t)vpwmMax << 16) / perCountNominal; // fixed 24.8
    uint32_t supplyFactor = (((uint32_t)supplyNominal << 16) / state.supplyVoltage); // fixed 16.16
    uint16_t dimFactor = ((uint32_t)dimPercent << 8) / 100; // fixed 8.8
    uint32_t factor = ((supplyFactor * dimFactor) >> 8); // fixed 16.16
    return (factor * pwmNominal) >> 24;
}

static void updatePwm(void) {
    pwmSet(calculatePwm(state.pwmLevel));
}

static void vccMonitor(uint16_t mV) {
//    debugTrace(mV);
    state.supplyVoltage = mV;
    updatePwm();
    vccmContinue(&vccMonitor);
}

static void setupBlinker() {
    blinkerSetup(&blinker, BlinkerModeOffThenOn,1, ST_MS2TICKS(100), ST_MS2TICKS(400), led);
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

static void turnOn_2(void* arg) {
}

static void turnOn_1(uint16_t mV) {
    vccMonitor(mV);
    led(true);
    stSetTimer(&blinker.timer, ST_MS2TICKS(5), turnOn_2, 0);
}

static void turnOn_0() {
    set_sleep_mode(SLEEP_MODE_IDLE);
    pwmSet(255);
    if (!pwmIsEnabled()) {
        pwmEnable();
    }
    vccmEnable();
    vccmStart(&turnOn_1);
}

static void turnOff() {
    vccmDisable();
    stopBlinker();
    led(false);
    if (pwmIsEnabled()) {
        pwmDisable();
    }
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
}

static void enterSetup() {
    startBlinker();
}

static void exitSetup() {
    startBlinker();
}

static void nextLevel() {
    state.pwmLevel = (state.pwmLevel + 1) % level2dimPercentSize;
    updatePwm();
}

static void stateOff(BtnEvent e) {
    switch (e) {
        case BtnShortPress:
            state.state = StateOn;
            turnOn_0();
            break;

        default:
            ;
    }
}

static void stateOn(BtnEvent e) {
    switch (e) {
        case BtnShortPress:
            state.state = StateOff;
            turnOff();
            break;

        case BtnLongPress:
            state.state = StateSetup;
            enterSetup();
            break;

        default:
            ;
    }
}

static void stateSetup(BtnEvent e) {
    switch (e) {
        case BtnLongPress:
            state.state = StateOn;
            exitSetup();
            break;

        case BtnShortPress:
            nextLevel();
            break;

        default:
            ;
    }
}

static void sleep(void) {
    if (stIsAlarmSet()) {
        set_sleep_mode(SLEEP_MODE_IDLE);
    }
    sleep_enable();
    sei();
    sleep_cpu();
    sleep_disable();
}

static void buttonEvent(BtnEvent e) {
    state2func[state.state](e);
}

int main(void)
{
    led(false);
    initState();
    setupClockEtc();
    setupPins();
    pwmInit();
    stInit();
    btnInit(SWITCH_PIN, buttonEvent);
    setupPCINT();
    setupBlinker();
    vccmInit();
    dbnEnable();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    stEnableClock();
    sei();
    do {
        sleep();
    } while (1);
}

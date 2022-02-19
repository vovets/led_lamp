#include <lib/blinker.h>
#include <lib/adc.h>
#include <lib/adc_filter.h>
#include <lib/clocks_etc.h>
#include <lib/debug.h>
#include <lib/loop.h>
#include <lib/event_queue.h>

#include <avr/interrupt.h>

#include <stdint.h>

#define LED_PIN PB3
#define ADC_PERIOD ST_MS2TICKS(1)
#define ADC_MAX 1023
#define LED_PERIOD_MIN ST_MS2TICKS(10)
#define LED_PERIOD_MAX ST_MS2TICKS(250)

typedef struct AdcData {
    AdcFilter filter;
    uint8_t delayCycles;
    Timer timer;
} AdcData;

AdcData adcData;

Blinker onOffBlinker;

bool blinkerStarted;

void setupPins(void) {
    DDRB |= _BV(LED_PIN);
}

uint8_t sleepMode(void) {
    return SLEEP_MODE_IDLE;
}

void pin(bool on) {
    if (on) {
        PORTB |= _BV(LED_PIN);
    } else {
        PORTB &= ~_BV(LED_PIN);
    }
}

void blinkerFinished(Blinker* blinker, void* arg);

void startBlinker(void) {
    blinkerStart(&onOffBlinker, blinkerFinished, 0);
}

void blinkerFinished(Blinker* blinker, void* arg) {
    startBlinker();
}

void handleAdcFilteredResult(uint16_t result) {
//    static uint8_t counter = 0;
//    counter = (counter + 1) % 10;
//    if (!counter) {
//        debugPrint(stNow(), result);
//    }
    SysTimeDelta period = LED_PERIOD_MAX - ((int32_t)result * (LED_PERIOD_MAX - LED_PERIOD_MIN)) / ADC_MAX;
    SysTimeDelta state0 = period / 2;
    SysTimeDelta state1 = period - state0;
    blinkerSetup(&onOffBlinker, BlinkerModeOnThenOff, 1, state0, state1, &pin);
    if (!blinkerStarted) {
        startBlinker();
        blinkerStarted = true;
    }
}

void handleAdc(struct Event* e) {
    uint16_t filtered = adcFilterUpdate(&adcData.filter, e->adc.value);
    if (adcData.delayCycles) {
        --adcData.delayCycles;
        return;
    }
    handleAdcFilteredResult(filtered);
}

void adcDataInit() {
    adcData.delayCycles = ADC_FILTER_BUFFER_SIZE;
    adcFilterInit(&adcData.filter);
}

void setAdcTimer(AdcData* data);

void adcTimerAlarm(void* arg) {
    setAdcTimer((AdcData*)arg);
    adcStartConversion();
}

void setAdcTimer(AdcData* data) {
    tmSetTimer(&data->timer, ADC_PERIOD, adcTimerAlarm, data);
}

int main(void)
{
    setupClock();
    setupPins();
    adcDataInit(&adcData);
    adcEnable();
    eqInit();
    stInit();
    tmInit();
    setAdcTimer(&adcData);
    stEnableClock();
    sei();
    loop();
}

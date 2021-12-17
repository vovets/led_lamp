#include "timers.h"
#include "blinker.h"
#include "adc.h"
#include "adc_filter.h"
#include "clocks_etc.h"
#include "debug.h"

#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay_basic.h>

#include <stdint.h>
#include <assert.h>

#define PIN PB4
#define ADC_PERIOD ST_MS2TICKS(1)
#define ADC_MAX 1023

typedef struct AdcData {
    AdcFilter filter;
    uint8_t delayCycles;
    Timer timer;
} AdcData;

AdcData adcData;

Blinker blinker;

bool blinkerStarted;

void setupPins(void) {
    DDRB |= _BV(PIN);
}

void sleep(void) {
    sleep_enable();
    sleep_cpu();
    sleep_disable();
}

void setupBlinker(void) {
    blinkerSetup(&blinker, 1, 100, 900, PIN);
}

void blinkerFinished(Blinker* blinker, void* arg);

void startBlinker(void) {
    blinkerStart(&blinker, blinkerFinished, 0);
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
    SysTimeDelta period = 125 + ((uint32_t)result * 375) / ADC_MAX;
    blinkerSetup(&blinker, blinker.iterations, 100, period - 100, blinker.pin);
    if (!blinkerStarted) {
        startBlinker();
        blinkerStarted = true;
    }
}

void conversionFinished(void* arg, uint16_t result) {
    AdcData* data = (AdcData*)arg;
    uint16_t filtered = adcFilterUpdate(&data->filter, result);
    if (data->delayCycles) {
        --data->delayCycles;
        return;
    }
    handleAdcFilteredResult(filtered);
}

void adcDataInit(AdcData* data) {
    data->delayCycles = ADC_FILTER_BUFFER_SIZE;
}

void setAdcTimer(AdcData* data);

void adcTimerAlarm(void* arg) {
    setAdcTimer((AdcData*)arg);
    adcStartConversion(conversionFinished, arg);
//    debugPrint(stNow(), 0);
}

void setAdcTimer(AdcData* data) {
    stSetTimer(&data->timer, ADC_PERIOD, adcTimerAlarm, data);
}

int main(void)
{
    setupClockEtc();
    setupPins();
    adcFilterInit(&adcData.filter);
    adcDataInit(&adcData);
    adcEnable();
    stInit();
    setAdcTimer(&adcData);
    setupBlinker();
    stEnableClock();
    sei();
    sleep();
    while (1)
    {
        sleep();
    }
}

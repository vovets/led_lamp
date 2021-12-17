#include <assert.h>
#include "vcc_monitor.h"
#include "timers.h"
#include "adc.h"
#include "adc_filter.h"
#include "debug.h"


#define VCC_MONITOR_PERIOD_MS 100
#define VCC_MONITOR_ADMUX (_BV(MUX3)|_BV(MUX2))

typedef struct VccMonitor {
    VccmFunc func;
    Timer timer;
    uint16_t iterationsLeft;
    AdcFilter filter;
} VccMonitor;

VccMonitor vccMonitor;

static void vccmConvFinished(void* arg, uint16_t result);
static void vccmTimerAlarm(void* arg);

void vccmInit(void) {
    adcFilterInit(&vccMonitor.filter);
}

void vccmEnable(void) {
    adcEnable(VCC_MONITOR_ADMUX);
}

static void vccmStartConversion(void);

void vccmStart(VccmFunc func) {
    assert(func);
    vccMonitor.func = func;
    vccMonitor.iterationsLeft = ADC_FILTER_BUFFER_SIZE;
    vccmStartConversion();
}

void vccmContinue(VccmFunc func) {
    assert(func);
    vccMonitor.func = func;
    vccMonitor.iterationsLeft = ADC_FILTER_BUFFER_SIZE;
    stSetTimer(
        &vccMonitor.timer, ST_MS2TICKS(VCC_MONITOR_PERIOD_MS), &vccmTimerAlarm, 0);
}

void vccmDisable(void) {
    adcDisable();
    if (stIsTimerSet(&vccMonitor.timer)) {
        stCancelTimer(&vccMonitor.timer);
    }
    vccMonitor.func = 0;
}

static uint16_t calculate_mV(void) {
    static const uint16_t vbg = 1100; // in mV
    static const uint32_t adcMax = 1024U;
    /* uint16_t result = */
    /* ((adcMax * vbg) / adcFilterCurrentSum(&vccMonitor.filter)) */
    /* << ADC_FILTER_BUFFER_SIZE_LOG; */

    uint16_t result =
    ((adcMax << ADC_FILTER_BUFFER_SIZE_LOG) * vbg)
    / adcFilterCurrentSum(&vccMonitor.filter);

    return result;
}

static void vccmTimerAlarm(void* arg) {
    vccmStartConversion();
}

static void vccmStartConversion(void) {
    adcStartConversion(&vccmConvFinished, 0);
}

static void vccmConvFinished(void* arg, uint16_t result) {
    adcFilterAdd(&vccMonitor.filter, result);
    --vccMonitor.iterationsLeft;

    if (vccMonitor.iterationsLeft) {
        stSetTimer(&vccMonitor.timer, 1, &vccmTimerAlarm, 0);
        return;
    }

    VccmFunc func = vccMonitor.func;
    vccMonitor.func = 0;

    if (func) {
        func(calculate_mV());
    }
}

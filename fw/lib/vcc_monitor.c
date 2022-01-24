#include <assert.h>
#include <lib/vcc_monitor.h>
#include <lib/timers.h>
#include <lib/adc.h>
#include <lib/adc_filter.h>
#include "debug.h"
#include "loop.h"


typedef struct VccMonitor {
    VccmFunc func;
    Timer timer;
    uint16_t iterationsLeft;
    AdcFilter filter;
} VccMonitor;

static VccMonitor vccMonitor;

static void vccmTimerAlarm(void* arg);

void vccmInit(void) {
    adcFilterInit(&vccMonitor.filter);
}

void vccmEnable(void) {
    adcEnable();
}

void vccmStart(VccmFunc func) {
    assert(func);
    vccMonitor.func = func;
    vccMonitor.iterationsLeft = ADC_FILTER_BUFFER_SIZE;
    adcStartConversion();
}

void vccmContinue(VccmFunc func) {
    assert(func);
    vccMonitor.func = func;
    vccMonitor.iterationsLeft = ADC_FILTER_BUFFER_SIZE;
    tmSetTimer(
            &vccMonitor.timer, ST_MS2TICKS(VCC_MONITOR_PERIOD_MS), &vccmTimerAlarm, 0);
}

void vccmDisable(void) {
    adcDisable();
    if (tmIsTimerSet(&vccMonitor.timer)) {
        tmCancelTimer(&vccMonitor.timer);
    }
    vccMonitor.func = 0;
}

static uint16_t calculate_mV(void) {
    static const uint16_t vbg = 1100U; // in mV
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
    adcStartConversion();
}

void handleAdc(const Event* e) {
    adcFilterAdd(&vccMonitor.filter, e->adc.value);
    --vccMonitor.iterationsLeft;

    if (vccMonitor.iterationsLeft) {
        tmSetTimer(&vccMonitor.timer, 2, &vccmTimerAlarm, 0);
        return;
    }

    VccmFunc func = vccMonitor.func;
    vccMonitor.func = 0;

    if (func) {
        func(calculate_mV());
    }
}

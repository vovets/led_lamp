#include "adc_filter.h"

#include <string.h>


void adcFilterInit(struct AdcFilter* adc) {
    memset(adc, 0, sizeof(AdcFilter));
}

uint16_t adcFilterCurrent(AdcFilter* adc) {
    return adc->sum >> ADC_FILTER_BUFFER_SIZE_LOG;
}

void adcFilterAdd(AdcFilter* adc, uint16_t value) {
    adc->sum += value;
    adc->sum -= adc->buffer[adc->writeIndex];
    adc->buffer[adc->writeIndex] = value;
    adc->writeIndex = (adc->writeIndex + 1) % ADC_FILTER_BUFFER_SIZE;
}

uint16_t adcFilterUpdate(AdcFilter* adc, uint16_t value) {
    adcFilterAdd(adc, value);
    return adcFilterCurrent(adc);
}

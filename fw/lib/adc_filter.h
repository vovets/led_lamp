#pragma once

#include <lib/parameters.h>

#include <stdint.h>

#define ADC_FILTER_BUFFER_SIZE (1U<<ADC_FILTER_BUFFER_SIZE_LOG)

typedef struct AdcFilter {
    uint16_t sum;
    uint8_t writeIndex;
    uint16_t buffer[ADC_FILTER_BUFFER_SIZE];
} AdcFilter;

void adcFilterInit(struct AdcFilter* adc);

uint16_t adcFilterCurrent(AdcFilter* adc);

uint16_t adcFilterUpdate(AdcFilter* adc, uint16_t value);

static inline uint16_t adcFilterCurrentSum(AdcFilter* adc) {
    return adc->sum;
}

void adcFilterAdd(AdcFilter* adc, uint16_t value);

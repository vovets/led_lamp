#pragma once

#include <custom_parameters.h>

#ifndef F_CPU
#define F_CPU 8000000
#endif

#ifndef ST_FREQ_DIVIDER
#define ST_FREQ_DIVIDER 1024
#endif

#ifndef TM_ALARM_MIN_DELAY
#define TM_ALARM_MIN_DELAY 2
#endif

#ifndef ADC_FILTER_BUFFER_SIZE_LOG
#define ADC_FILTER_BUFFER_SIZE_LOG 5
#endif

#ifndef ADC_FREQ_DIVIDER
#define ADC_FREQ_DIVIDER 8
#endif

#ifndef ADC_ADMUX_VALUE
#define ADC_ADMUX_VALUE (_BV(MUX3)|_BV(MUX2))
#endif

#ifndef EQ_QUEUE_SIZE
#define EQ_QUEUE_SIZE 5
#endif

#ifndef DEBOUNCER_ITERATIONS
#define DEBOUNCER_ITERATIONS 3
#endif

#ifndef DEBOUNCER_DELAY
#define DEBOUNCER_DELAY 2
#endif

#ifndef PWM_FREQ_DIVIDER
#define PWM_FREQ_DIVIDER 1
#endif

#ifndef BTN_LONG_PRESS_MS
#define BTN_LONG_PRESS_MS 1000
#endif

#ifndef BTN_DOWN_IS_PIN_LOW
#define BTN_DOWN_IS_PIN_LOW 1
#endif

#ifndef VCC_MONITOR_PERIOD_MS
#define VCC_MONITOR_PERIOD_MS 1000
#endif

#ifndef PWMA_FULL_TRANSITION_TIME_MS
#define PWMA_FULL_TRANSITION_TIME_MS 512U
#endif

#ifndef PWMA_TICK_TIME_MS
#define PWMA_TICK_TIME_MS 20U
#endif

#ifndef DEBUG_TRACE_BUFFER_SIZE
// if set to 0 debugTrace2 calls are eliminated
#define DEBUG_TRACE_BUFFER_SIZE 10
#endif

#ifndef DEBUG_PIN_0
#define DEBUG_PIN_0 PB0
#endif

#ifndef DEBUG_PIN_1
#define DEBUG_PIN_1 PB2
#endif

#ifndef DEBUG_PIN_0_ENABLED
#define DEBUG_PIN_0_ENABLED 0
#endif

#ifndef DEBUG_PIN_1_ENABLED
#define DEBUG_PIN_1_ENABLED 0
#endif

#pragma once

struct Event;

void tmHandleAlarm(struct Event* e);
void handleAdc(struct Event* e);

#define EVENT_LIST                                                     \
X(alarm,     Alarm,     1, EL_EMPTY,        tmHandleAlarm,   SEP)      \
X(adc,       Adc,       2, uint16_t value;, handleAdc,       LAST_SEP)

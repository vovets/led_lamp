#pragma once

struct Event;

void tmHandleAlarm(struct Event* e);

#define EVENT_LIST                                                     \
X(alarm,     Alarm,     1, EL_EMPTY,        tmHandleAlarm,     SEP)

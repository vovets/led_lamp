#pragma once

struct Event;

void alarm(struct Event* e);

#define EVENT_LIST                                                     \
X(alarm,     Alarm,     1, EL_EMPTY,        alarm,     SEP)

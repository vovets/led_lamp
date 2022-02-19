#pragma once

#include <lib/sys_time.h>

#include <stdint.h>
#include <string.h>

#include <event_list.h>

#define EL_EMPTY

#define SEP ,
#define LAST_SEP
#define X(a, A, id, data, handler, sep) ev##A = id sep

typedef enum {
    evUnused = 0,
    EVENT_LIST
} EventType;

#undef X
#undef SEP
#undef LAST_SEP

#define SEP ,
#define LAST_SEP
#define X(a, A, id, data, handler, sep) struct A { data } a;

typedef struct Event {
    EventType type;
    SysTimePoint time;
    union {
        uint16_t data;
        EVENT_LIST
    };
} Event;

#undef X
#undef SEP
#undef LAST_SEP

// 1MHz -O2: 33 us
static inline void evCopy(const Event* src, Event* dst) {
    dst->type = src->type;
    dst->time = src->time;
    dst->data = src->data;
}

// 1MHz -O2: 47 us
//static inline void evCopy(const Event* src, Event* dst) {
//    *dst = *src;
//}

// 1MHz -O2: 33 us
//#define evCopy(src,dst) do { dst.type = src.type; dst.time = src.time; dst.data = src.data; } while (false)

// 1MHz -O2: 47 us
//static inline void evCopy(const Event* src, Event* dst) {
//    memcpy(dst, src, sizeof(Event));
//}

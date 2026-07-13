#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
typedef struct { uint16_t type; uint16_t source; uint32_t arg; } event_t;
typedef struct { event_t *items; size_t capacity; volatile size_t head,tail; size_t high_water; uint32_t dropped; } event_queue_t;
bool event_queue_init(event_queue_t*,event_t*,size_t);
bool event_queue_post(event_queue_t*,event_t);
bool event_queue_get(event_queue_t*,event_t*);
size_t event_queue_count(const event_queue_t*);
#endif

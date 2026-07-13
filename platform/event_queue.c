#include "event_queue.h"
bool event_queue_init(event_queue_t*q,event_t*s,size_t c){if(!q||!s||c<2u)return false;*q=(event_queue_t){.items=s,.capacity=c};return true;}
size_t event_queue_count(const event_queue_t*q){return q?((q->head+q->capacity-q->tail)%q->capacity):0u;}
bool event_queue_post(event_queue_t*q,event_t e){if(!q)return false;size_t n=(q->head+1u)%q->capacity;if(n==q->tail){q->dropped++;return false;}q->items[q->head]=e;q->head=n;size_t c=event_queue_count(q);if(c>q->high_water)q->high_water=c;return true;}
bool event_queue_get(event_queue_t*q,event_t*e){if(!q||!e||q->tail==q->head)return false;*e=q->items[q->tail];q->tail=(q->tail+1u)%q->capacity;return true;}

#include "scheduler.h"
#include "timebase.h"
void scheduler_init(scheduler_t*s,scheduled_task_t*t,size_t c){if(s)*s=(scheduler_t){.tasks=t,.capacity=c};for(size_t i=0;i<c;i++)t[i].active=0;}
int scheduler_add(scheduler_t*s,task_fn_t f,void*c,uint32_t first,uint32_t period){if(!s||!f)return -1;for(size_t i=0;i<s->capacity;i++)if(!s->tasks[i].active){s->tasks[i]=(scheduled_task_t){.fn=f,.ctx=c,.next_ms=first,.period_ms=period,.active=1};return (int)i;}return -1;}
void scheduler_run_due(scheduler_t*s,uint32_t now){if(!s)return;for(size_t i=0;i<s->capacity;i++){scheduled_task_t*t=&s->tasks[i];if(t->active&&time_after_eq_u32(now,t->next_ms)){uint32_t delay=now-t->next_ms;if(delay>s->longest_delay_ms)s->longest_delay_ms=delay;t->fn(t->ctx);t->runs++;if(t->period_ms)t->next_ms+=t->period_ms;else t->active=0;}}}

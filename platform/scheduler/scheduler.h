#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <stddef.h>
#include <stdint.h>
typedef void (*task_fn_t)(void*);
typedef struct {task_fn_t fn;void*ctx;uint32_t next_ms,period_ms,runs,overruns;uint8_t active;} scheduled_task_t;
typedef struct {scheduled_task_t*tasks;size_t capacity;uint32_t longest_delay_ms;} scheduler_t;
void scheduler_init(scheduler_t*,scheduled_task_t*,size_t);
int scheduler_add(scheduler_t*,task_fn_t,void*,uint32_t,uint32_t);
void scheduler_run_due(scheduler_t*,uint32_t);
#endif

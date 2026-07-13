#include <stdint.h>
#include "project_config.h"
#include "scheduler.h"
#include "health.h"
static volatile uint32_t g_ms;
void SysTick_Handler(void){g_ms++;}
static void heartbeat(void*ctx){health_kick((health_supervisor_t*)ctx,HEALTH_SCHEDULER);}
int main(void){scheduled_task_t tasks[4];scheduler_t scheduler;health_supervisor_t health;scheduler_init(&scheduler,tasks,4);health_init(&health,HEALTH_SCHEDULER);(void)scheduler_add(&scheduler,heartbeat,&health,0,100);for(;;){scheduler_run_due(&scheduler,g_ms);if((g_ms%1000u)==0u)(void)health_window_complete(&health);__asm volatile("wfi");}}

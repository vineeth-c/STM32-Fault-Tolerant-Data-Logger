#ifndef HEALTH_H
#define HEALTH_H
#include <stdint.h>
typedef enum {HEALTH_ACQUISITION=1u<<0,HEALTH_COMMUNICATION=1u<<1,HEALTH_STORAGE=1u<<2,HEALTH_SCHEDULER=1u<<3,HEALTH_SENSOR=1u<<4} health_bit_t;
typedef struct {uint32_t required,seen,refresh_count,withheld_count,missed_windows;} health_supervisor_t;
void health_init(health_supervisor_t*,uint32_t);
void health_kick(health_supervisor_t*,uint32_t);
int health_window_complete(health_supervisor_t*);
#endif

#ifndef TIMEBASE_H
#define TIMEBASE_H
#include <stdint.h>
static inline int time_after_eq_u32(uint32_t now,uint32_t deadline){return (int32_t)(now-deadline)>=0;}
static inline uint32_t time_elapsed_u32(uint32_t now,uint32_t then){return now-then;}
#endif

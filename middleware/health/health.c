#include "health.h"
void health_init(health_supervisor_t*h,uint32_t r){if(h)*h=(health_supervisor_t){.required=r};}
void health_kick(health_supervisor_t*h,uint32_t b){if(h)h->seen|=b;}
int health_window_complete(health_supervisor_t*h){if(!h)return 0;int ok=(h->seen&h->required)==h->required;if(ok)h->refresh_count++;else{h->withheld_count++;h->missed_windows++;}h->seen=0;return ok;}

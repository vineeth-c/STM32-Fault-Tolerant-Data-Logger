#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "ring_buffer.h"
#include "event_queue.h"
#include "crc32.h"
#include "protocol.h"
#include "persistent_log.h"
#include "health.h"
#include "timebase.h"
static int fails;
#define CHECK(x) do{if(!(x)){printf("FAIL %s:%d: %s\n",__FILE__,__LINE__,#x);fails++;}}while(0)
int main(void){uint8_t m[8],o[8];ring_buffer_t r;CHECK(ring_buffer_init(&r,m,8));CHECK(ring_buffer_write(&r,(uint8_t*)"abc",3)==3);CHECK(ring_buffer_read(&r,o,3)==3&&memcmp(o,"abc",3)==0);CHECK(crc32_compute((uint8_t*)"123456789",9)==0xCBF43926u);CHECK(time_after_eq_u32(1u,0xFFFFFFFEu));event_t es[4],e;event_queue_t q;CHECK(event_queue_init(&q,es,4));CHECK(event_queue_post(&q,(event_t){1,2,3}));CHECK(event_queue_get(&q,&e)&&e.arg==3);protocol_frame_t f={.version=1,.type=1,.length=3,.payload={1,2,3}},g;uint8_t enc[64];size_t n;CHECK(protocol_encode(&f,enc,sizeof enc,&n)==STATUS_OK);protocol_parser_t p;protocol_parser_init(&p);int ready=0;for(size_t i=0;i<n;i++)CHECK(protocol_parser_feed(&p,enc[i],&g,&ready)==STATUS_OK);CHECK(ready&&g.length==3&&g.payload[2]==3);uint8_t media[256]={0};persistent_log_t l;persistent_log_init(&l,media,sizeof media);CHECK(persistent_log_append(&l,10,(uint8_t*)"xyz",3)==STATUS_OK);persistent_log_t l2;persistent_log_init(&l2,media,sizeof media);CHECK(persistent_log_scan(&l2)==STATUS_OK&&l2.recovered_records==1);health_supervisor_t h;health_init(&h,3);health_kick(&h,1);health_kick(&h,2);CHECK(health_window_complete(&h));printf("%s\n",fails?"TESTS FAILED":"ALL TESTS PASSED");return fails?1:0;}

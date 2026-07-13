#include "ring_buffer.h"
static bool is_pow2(size_t x){return x>1u && (x&(x-1u))==0u;}
bool ring_buffer_init(ring_buffer_t *rb,uint8_t *storage,size_t capacity){if(!rb||!storage||!is_pow2(capacity))return false;*rb=(ring_buffer_t){.data=storage,.capacity=capacity};return true;}
size_t ring_buffer_size(const ring_buffer_t *rb){return rb?((rb->head-rb->tail)&(rb->capacity-1u)):0u;}
size_t ring_buffer_write(ring_buffer_t *rb,const uint8_t *data,size_t length){if(!rb||!data)return 0u;size_t n=0;while(n<length){size_t next=(rb->head+1u)&(rb->capacity-1u);if(next==rb->tail){rb->overflow_count++;break;}rb->data[rb->head]=data[n++];rb->head=next;}return n;}
size_t ring_buffer_read(ring_buffer_t *rb,uint8_t *data,size_t capacity){if(!rb||!data)return 0u;size_t n=0;while(n<capacity&&rb->tail!=rb->head){data[n++]=rb->data[rb->tail];rb->tail=(rb->tail+1u)&(rb->capacity-1u);}return n;}

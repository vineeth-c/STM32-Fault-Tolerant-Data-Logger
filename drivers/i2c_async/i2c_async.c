#include "i2c_async.h"
#include "timebase.h"
i2c_result_t i2c_submit(i2c_async_t*i,const i2c_transaction_t*t){if(!i||!t||!t->buffer||!t->length)return I2C_RESULT_INVALID_ARGUMENT;uint8_t n=(uint8_t)((i->head+1u)%8u);if(n==i->tail)return I2C_RESULT_BUSY;i->queue[i->head]=*t;i->head=n;return I2C_RESULT_OK;}
void i2c_process(i2c_async_t*i,uint32_t now){if(!i)return;if(!i->busy&&i->tail!=i->head)i->busy=1;if(i->busy){i2c_transaction_t*t=&i->queue[i->tail];if(time_after_eq_u32(now,t->deadline_ms)){i->timeout_count++;i->tail=(uint8_t)((i->tail+1u)%8u);i->busy=0;}}}

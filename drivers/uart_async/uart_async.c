#include "uart_async.h"
void uart_async_init(uart_async_t*u,uint8_t*r,size_t rc,uint8_t*t,size_t tc){if(u){ring_buffer_init(&u->rx,r,rc);ring_buffer_init(&u->tx,t,tc);u->rx_bytes=u->tx_bytes=0;}}
size_t uart_write_async(uart_async_t*u,const uint8_t*d,size_t n){size_t w=u?ring_buffer_write(&u->tx,d,n):0; if(u)u->tx_bytes+=(uint32_t)w;return w;}
size_t uart_read(uart_async_t*u,uint8_t*d,size_t n){size_t r=u?ring_buffer_read(&u->rx,d,n):0;if(u)u->rx_bytes+=(uint32_t)r;return r;}

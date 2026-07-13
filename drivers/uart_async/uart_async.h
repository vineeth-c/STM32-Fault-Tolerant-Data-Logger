#ifndef UART_ASYNC_H
#define UART_ASYNC_H
#include <stddef.h>
#include <stdint.h>
#include "ring_buffer.h"
typedef struct {ring_buffer_t rx,tx;uint32_t rx_bytes,tx_bytes;} uart_async_t;
void uart_async_init(uart_async_t*,uint8_t*,size_t,uint8_t*,size_t);
size_t uart_write_async(uart_async_t*,const uint8_t*,size_t);
size_t uart_read(uart_async_t*,uint8_t*,size_t);
#endif

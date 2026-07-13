#ifndef SPI_ASYNC_H
#define SPI_ASYNC_H
#include <stddef.h>
#include <stdint.h>
typedef enum {SPI_OK,SPI_BUSY,SPI_TIMEOUT,SPI_INVALID_ARGUMENT} spi_result_t;
typedef struct {const uint8_t*tx;uint8_t*rx;uint16_t length;uint32_t deadline_ms;uint8_t chip_select;} spi_transaction_t;
typedef struct {spi_transaction_t q[8];uint8_t head,tail;uint32_t transfers,timeouts;} spi_async_t;
spi_result_t spi_submit(spi_async_t*,const spi_transaction_t*);
#endif

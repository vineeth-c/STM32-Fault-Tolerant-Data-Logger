#include "spi_async.h"
spi_result_t spi_submit(spi_async_t*s,const spi_transaction_t*t){if(!s||!t||!t->length||(!t->tx&&!t->rx))return SPI_INVALID_ARGUMENT;uint8_t n=(uint8_t)((s->head+1u)%8u);if(n==s->tail)return SPI_BUSY;s->q[s->head]=*t;s->head=n;s->transfers++;return SPI_OK;}

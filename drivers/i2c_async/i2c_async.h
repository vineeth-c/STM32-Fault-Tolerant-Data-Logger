#ifndef I2C_ASYNC_H
#define I2C_ASYNC_H
#include <stddef.h>
#include <stdint.h>
typedef enum {I2C_RESULT_OK,I2C_RESULT_BUSY,I2C_RESULT_TIMEOUT,I2C_RESULT_ADDRESS_NACK,I2C_RESULT_DATA_NACK,I2C_RESULT_ARBITRATION_LOST,I2C_RESULT_BUS_ERROR,I2C_RESULT_OVERRUN,I2C_RESULT_RECOVERY_FAILED,I2C_RESULT_INVALID_ARGUMENT} i2c_result_t;
typedef struct {uint8_t address,reg;uint8_t*buffer;uint16_t length;uint32_t deadline_ms;uint8_t read;} i2c_transaction_t;
typedef struct {i2c_transaction_t queue[8];uint8_t head,tail,busy;uint32_t nack_count,timeout_count,recovery_count;} i2c_async_t;
i2c_result_t i2c_submit(i2c_async_t*,const i2c_transaction_t*);
void i2c_process(i2c_async_t*,uint32_t now_ms);
#endif

#ifndef PERSISTENT_LOG_H
#define PERSISTENT_LOG_H
#include <stddef.h>
#include <stdint.h>
#include "status.h"
#define LOG_MAGIC 0x4C4F4731u
#define LOG_COMMIT 0xC0DE17EDu
typedef struct {uint32_t magic,sequence,timestamp_ms;uint16_t version,payload_length;uint32_t payload_crc,header_crc,commit;} log_header_t;
typedef struct {uint8_t*media;size_t size,write_offset;uint32_t next_sequence,recovered_records,crc_failures;} persistent_log_t;
void persistent_log_init(persistent_log_t*,uint8_t*,size_t);
status_t persistent_log_append(persistent_log_t*,uint32_t,const uint8_t*,uint16_t);
status_t persistent_log_scan(persistent_log_t*);
#endif

#ifndef SAMPLE_H
#define SAMPLE_H
#include <stdint.h>
typedef struct {uint8_t format_version,validity_flags;uint16_t health_flags;uint32_t sequence,timestamp_ms,boot_counter;uint16_t adc_raw;int16_t temperature_centi_c;uint32_t crc32;} sample_record_t;
#endif

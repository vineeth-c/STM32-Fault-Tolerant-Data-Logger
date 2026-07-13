#ifndef RING_BUFFER_H
#define RING_BUFFER_H
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
typedef struct { uint8_t *data; size_t capacity; volatile size_t head; volatile size_t tail; uint32_t overflow_count; } ring_buffer_t;
bool ring_buffer_init(ring_buffer_t *rb, uint8_t *storage, size_t capacity);
size_t ring_buffer_write(ring_buffer_t *rb, const uint8_t *data, size_t length);
size_t ring_buffer_read(ring_buffer_t *rb, uint8_t *data, size_t capacity);
size_t ring_buffer_size(const ring_buffer_t *rb);
#endif

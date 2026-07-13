#ifndef FIRMWARE_IMAGE_H
#define FIRMWARE_IMAGE_H
#include <stddef.h>
#include <stdint.h>
#include "status.h"
#define IMAGE_MAGIC 0x494D4731u
typedef struct {uint32_t magic,hardware_id,load_address,image_size,crc32;uint16_t major,minor,patch,reserved;uint8_t build_id[16];} firmware_image_header_t;
status_t firmware_image_validate(const firmware_image_header_t*,const uint8_t*,size_t,uint32_t,uint32_t,uint32_t);
#endif

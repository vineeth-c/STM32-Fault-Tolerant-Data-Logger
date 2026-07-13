#include "firmware_image.h"
#include "crc32.h"
status_t firmware_image_validate(const firmware_image_header_t*h,const uint8_t*i,size_t n,uint32_t hw,uint32_t lo,uint32_t hi){if(!h||!i)return STATUS_INVALID_ARGUMENT;if(h->magic!=IMAGE_MAGIC||h->hardware_id!=hw)return STATUS_UNSUPPORTED;if(h->image_size!=n||h->load_address<lo||h->load_address+n>hi)return STATUS_CORRUPT;return crc32_compute(i,n)==h->crc32?STATUS_OK:STATUS_CRC_ERROR;}

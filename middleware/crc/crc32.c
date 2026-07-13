#include "crc32.h"
uint32_t crc32_compute(const uint8_t*d,size_t n){uint32_t c=0xFFFFFFFFu;for(size_t i=0;i<n;i++){c^=d[i];for(unsigned b=0;b<8;b++)c=(c>>1)^((0u-(c&1u))&0xEDB88320u);}return ~c;}

#include <stdint.h>
#define APP_BASE 0x08004000u
static int vector_valid(const uint32_t*v){return v[0]>=0x20000000u&&v[0]<0x20005000u&&v[1]>=APP_BASE&&v[1]<0x08010000u;}
int main(void){const uint32_t*v=(const uint32_t*)APP_BASE;if(vector_valid(v)){void(*app)(void)=(void(*)(void))v[1];__asm volatile("msr msp,%0"::"r"(v[0]):);app();}for(;;){__asm volatile("wfi");}}

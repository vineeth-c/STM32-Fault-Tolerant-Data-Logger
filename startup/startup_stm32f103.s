.syntax unified
.cpu cortex-m3
.thumb
.global g_pfnVectors
.global Reset_Handler
.section .isr_vector,"a",%progbits
g_pfnVectors:
.word _estack
.word Reset_Handler
.word Default_Handler
.word Default_Handler
.word Default_Handler
.word Default_Handler
.word Default_Handler
.word 0
.word 0
.word 0
.word 0
.word Default_Handler
.word Default_Handler
.word 0
.word Default_Handler
.word SysTick_Handler
.rept 60
.word Default_Handler
.endr
.section .text.Reset_Handler,"ax",%progbits
Reset_Handler:
ldr r0,=_sidata
ldr r1,=_sdata
ldr r2,=_edata
1: cmp r1,r2
ittt lt
ldrlt r3,[r0],#4
strlt r3,[r1],#4
blt 1b
ldr r1,=_sbss
ldr r2,=_ebss
movs r3,#0
2: cmp r1,r2
itt lt
strlt r3,[r1],#4
blt 2b
bl main
b .
.thumb_func
Default_Handler: b .
.weak SysTick_Handler
.thumb_set SysTick_Handler,Default_Handler

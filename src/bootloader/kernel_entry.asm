; ============================================
; kernel_jump.asm
; Bridge between kernel and bootloader code
;
; Author: Ioane Baidoshvili
; Date: 06-Sep-24
; ============================================


[BITS 32] ; We are in protected mode

global _start 
extern kernel_main ; External symbol of kernel_main.cpp

_start:

    call kernel_main ; Connecting to kernel_main.cpp (void kernel_main())
    
hltloop:
    hlt 
    jmp hltloop
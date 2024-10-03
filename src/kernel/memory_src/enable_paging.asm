; =====================================
; enablee_paging.cpp
; Enables paging for virtual memory
;
; Author: Ioane Baidoshvili
; Date 03-Oct-24
; =====================================

section .bss
    page_directory resb 4096  ; Reserve 4KB for the page directory

section .text
    global enable_32bit_paging

enable_32bit_paging:
    ; Load the address of the page directory into EAX
    mov eax, page_directory   ; Get the address of the page directory
    mov cr3, eax              ; Set CR3 to the address of the page directory

    ; Enable paging by modifying CR0
    mov eax, cr0              ; Load CR0 into EAX
    or eax, 0x80000001       ; Set bit 31 (paging enabled) and bit 0 (write protect)
    mov cr0, eax              ; Write back to CR0

    ret                        ; Return from the function
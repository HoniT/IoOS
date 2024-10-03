section .text
    global enable_32bit_paging

; Function to enable paging by setting CR3 and CR0
enable_32bit_paging:
    ; Load the PML4 address into CR3
    mov eax, [esp + 4]   ; Load the address of PML4 into eax
    mov cr3, eax         ; Load CR3 with the address of the PML4

    ; Enable paging by setting the PG bit in CR0
    mov eax, cr0
    or eax, 0x80000000   ; Set the 31st bit (PG - Paging Enabled)
    mov cr0, eax

    ret
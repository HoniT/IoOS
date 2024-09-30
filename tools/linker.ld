/* =====================================
// linker.ld
// Linker script
//
// Author: Ioane Baidoshvili
// Date 06-Sep-24
// ===================================== */

OUTPUT_ARCH(i386)
ENTRY(_start)

SECTIONS
{
    /* Bootloader section at 0x7C00 (BIOS loads the bootloader here) */
    . = 0x7C00;

    .boot : {
        *(.boot)        /* Include all .text sections for bootloader code */
    }

    . = 0x7DFE;
    .bootsig : {
        SHORT(0xAA55);
    }

    REAL_BASE = .;

    /* Align to 1 MiB (where kernel starts) */
    . = 0x100000;
    __kernelreal_diff = . - REAL_BASE; /* Difference to kernel from real mode */

    

    /* Kernel sections */
    .text : AT(ADDR(.text) - __kernelreal_diff) ALIGN(4096)
    {
        __kernel_start = .;  /* This is the start address of the kernel */
        *(.text*)
    }

    .rodata : AT(ADDR(.rodata) - __kernelreal_diff) ALIGN(4096)
    {
        *(.rodata*)
        KEEP(*(.magic))
    }

    .data : AT(ADDR(.data) - __kernelreal_diff) ALIGN(4096)
    {
        *(.data)
    }

    __kernel_load_end = . ; /* Last loaded memory address of kernel */

    .bss : AT(ADDR(.bss) - __kernelreal_diff) ALIGN(4096)
    {
        __kernel_bss_start = .;
        *(COMMON)
        *(.bss)
    }



    __kernel_end = .;  /* This is the end address of the kernel */

    __kernel_bss_sizeb = __kernel_end - __kernel_bss_start;
    __kernel_load_sizeb = __kernel_load_end - __kernel_start;
    
    __kernel_sectors = (__kernel_load_sizeb + 511) / 512;
                       /* Number of sectors the kernel takes on disk */
}

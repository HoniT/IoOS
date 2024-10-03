// =======================================================
// paging.hpp
// Header file for paging virtual memory
//
// Author: Ioane Baidoshvili
// Date 03-Oct-24
// =======================================================

#pragma once

#ifndef PAGING_HPP
#define PAGING_HPP

#include <stdint.h>

// Defining needed macros
#define PAGE_PRESENT (1 << 0) // Is present
#define PAGE_WRITE (1 << 1) // Is writable
#define PAGE_USER (1 << 2) // User-mode access allowed
#define PAGE_SIZE 4096 // 4 KiB

// Structs

// Struct representing single page table entry
struct PageTableEntry {
    uint64_t present   : 1;
    uint64_t writable  : 1;
    uint64_t user      : 1;
    uint64_t reserved  : 9; // Reserved bits for future use
    uint64_t address   : 52; // Address of the page frame (physical memory)
};

// Page Table itself (512 entries)
struct PageTable {
    PageTableEntry entries[512];
};

extern "C" {
    // ASM function
    extern void enable_32bit_paging();
}


// Function declarations
void initPaging(); // Initializing paging from kernel_main.cpp

#endif
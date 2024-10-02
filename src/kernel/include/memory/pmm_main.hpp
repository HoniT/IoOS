// ====================================================
// pmm_main.cpp
// Main header file for the physical memory manager
//
// Author: Ioane Baidoshvili
// Date 01-Oct-24
// ====================================================

#ifndef PMM_MAIN_HPP
#define PMM_MAIN_HPP

#include <stdint.h>
#include <stdbool.h>

// Blocks and memory
#define BLOCK_SIZE 4096 // 4KiB blocks
#define TOTAL_MEMORY 0x10000000 // 256 MiB total memory
#define NUM_BLOCKS (TOTAL_MEMORY / BLOCK_SIZE) // Total number of blocks

// Memory bitmap array
extern uint8_t memory_bitmap[NUM_BLOCKS / 8];


// Functions defined in pmm_main.cpp
void initPmm(); // Initializes the Physical Memory Manager (PMM)

void set_block_free(const uint32_t block_number, const uint32_t quantity = 1); // Sets block free
bool is_block_free(const uint32_t block_number); // Checks if a block is free
void* allocate_block(const uint32_t num_blocks); // Allocates a block
void free_block(const void* address, const uint32_t quantity = 1); // Freeing a block

#endif
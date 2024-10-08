// ==========================================
// pmm_main.cpp
// Main file for the physical memory manager
//
// Author: Ioane Baidoshvili
// Date 01-Oct-24
// ==========================================

#include <memory/pmm_main.hpp>
#include <drivers/vga_print.hpp>
#include <util.hpp>

// Gets rid of block 0 address problem
uint8_t allocation_num = 0;

// Memory Bitmap to track free and used blocks
uint8_t memory_bitmap[NUM_BLOCKS / 8];


#pragma region Helper Functions

// Noting that the specific block has been allocated
void set_block_allocated(const uint32_t block_number) {
    // This performes a bitwise OR and modifies the lvalue
    memory_bitmap[block_number / 8] |= (1 << (block_number % 8));
}


#pragma endregion


#pragma region Global Function

// Noting that the specific block has been freed
void set_block_free(const uint32_t block_number, const uint32_t quantity) {
    for(uint32_t i = 0; i < quantity; i++) {
        // This performes a bitwise AND and modifies the lvalue
        memory_bitmap[(block_number + i) / 8] &= ~(1 << ((block_number + i) % 8));
    }
}

// Checks if a block is free
bool is_block_free(const uint32_t block_number) {
    /* Returns true if free
    // Returns false if being used */
    return !(memory_bitmap[block_number / 8] & ((1 << (block_number % 8))));
}

void initPmm() {
    memset(memory_bitmap, 0, sizeof(memory_bitmap));
}


void* allocate_block(const uint32_t num_blocks) {

    // Searching for a contiguous range of free blocks
    for (uint32_t i = 0; i <= NUM_BLOCKS - num_blocks; i++) {
        bool all_free = true; /* This is used to indicate that all of the amount of blocks
        // referenced by the parameter are all available */

        // Check if all blocks in the range [i, i + num_blocks) are free
        for (uint32_t j = 0; j < num_blocks; j++) {
            if (!is_block_free(i + j)) {
                all_free = false;
                break; // Exit the inner loop if a block is already allocated
            }
        }

        // If all blocks are free, allocate them
        if (all_free) {
            for (uint32_t j = 0; j < num_blocks; j++) {
                set_block_allocated(i + j);
            }

            print_str("Allocated block range starting at index: ");
            print_hex(i);
            print_str(", physical address:");
            print_hex(i * BLOCK_SIZE); // Prints actual address
            print_char('\n');

            if(allocation_num < 2) 
                allocation_num++;

            return (void*)(i * BLOCK_SIZE); // Returning the starting physical address
        }
    }

    return nullptr; // Out of memory or no contiguous blocks available
}


void free_block(const void* address, const uint32_t quantity) {
    uint32_t block_number = (uint32_t)address / BLOCK_SIZE; // Turning memory address into a unsigned int
    set_block_free(block_number, quantity);
}

#pragma endregion
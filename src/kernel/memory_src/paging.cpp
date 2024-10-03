// =======================================================
// paging.cpp
// Main file for paging virtual memory
//
// Author: Ioane Baidoshvili
// Date 03-Oct-24
// =======================================================

#include <memory/paging.hpp>
#include <memory/pmm_main.hpp>
#include <drivers/vga_print.hpp>

// Functions

// Allocates a page table using our PMM
PageTable* allocate_page_table(const char* error_message = "") { // Optionary error message
    void* physical_address = allocate_block(1); // Allocates 1 block because each table needs 4KiB (4096 bytes)
    if(physical_address == nullptr) {
        print_set_color(PRINT_COLOR_RED, PRINT_COLOR_BLUE);
        print_str("Out of memory ");
        print_str(error_message);
        print_str(": ");
        print_set_color(PRINT_COLOR_CYAN, PRINT_COLOR_BLUE);
        print_str("Failed to allocate page table!\n");
        return nullptr;
    }

    return reinterpret_cast<PageTable*>(physical_address); // Returns address
}

/* This function allocates and links PDPT, PD, PT
// Each entry in the PT points to a physical page (4 KiB) and sets flags */
void setup_identity_mapping(PageTable* pml4) {
    // Allocating Page Directory Pointer Table (PDPT), Page Directory (PD) and Page Table (PT)
    PageTable* pdpt = allocate_page_table("PDPT");
    PageTable* pd = allocate_page_table("PD");
    PageTable* pt = allocate_page_table("PT");

    // Identity mapping (Maps virtual addresses to the same physical address)
    for(uint64_t i = 0; i < 512; i++) {
        // Maps all 512 elements of entries array
        pt->entries[i] = PageTableEntry {
            // Setting up flags
            .present = 1, // Present in memory 
            .writable = 1, // Is writable
            .user = 0, // Is in kernel-mode
            .address = i
        };
    }


    // Link the page tables: PT -> PD -> PDPT - > PML4

    // Page Directory
    pd->entries[0] = PageTableEntry{
        .present = 1,
        .writable = 1,
        .user = 0,
        .address = (uint64_t)pt >> 12  // Right shift to remove the lower 12 bits (alignment)
    };

    // Page Directory Pointer Table
    pdpt->entries[0] = PageTableEntry{
        .present = 1,
        .writable = 1,
        .user = 0,
        .address = (uint64_t)pd >> 12
    };

    // Page Map Level 4
    pml4->entries[0] = PageTableEntry{
        .present = 1,
        .writable = 1,
        .user = 0,
        .address = (uint64_t)pdpt >> 12
    };
}


void page_fault_handler() {

}


// Initializing paging in kernel_main
void initPaging() {
    PageTable* pml4 = allocate_page_table("PML4");
    // Check memory
    if(pml4 == nullptr) {
        print_set_color(PRINT_COLOR_RED, PRINT_COLOR_BLUE);
        print_str("Paging initialization failed! ");

        print_set_color(PRINT_COLOR_CYAN, PRINT_COLOR_BLUE);
        print_str("No memory for PML4!\n");
        return;
    }

    // Sets up identity mapping
    setup_identity_mapping(pml4);

    // Inable paging via enable_paging.asm file
    enable_32bit_paging(reinterpret_cast<uint64_t>(pml4));
    
}
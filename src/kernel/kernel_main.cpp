// =====================================
// kernel_main.cpp
// Main file for the kernel
//
// Author: Ioane Baidoshvili
// Date 06-Sep-24
// =====================================

#include <kernel_main.hpp> 
#include <drivers/vga_print.hpp>
#include <interrupts/idt_main.hpp>
#include <memory/pmm_main.hpp>
#include <memory/paging.hpp>


// ========================================
// Function declarations and variables
// ========================================

void setUpMainText();
void testPmm();


#pragma region Magic Number

// Defining magic number to kernel for error debugging
extern "C" {

    const unsigned int KERNEL_MAGIC_NUMBER __attribute__((section(".magic"))) = 0xDEADBEEF;
}

#pragma endregion

extern "C" void kernel_main() {
    // Innitializing every needed manager
    #pragma region Initialization

    initIdt(); // Interrupt Descriptor Table
    setUpMainText(); // Setting up text labels and testing
    initPmm(); // Physical Memory Manager

    initPaging(); // Virtual Memory Paging
    #pragma endregion

    // Testing
    testPmm();

    // Infinite loop
    while(true) {}
    return;
}


/* Set up text labels using print functions
// defined in drivers_src/print_src/print.cpp */
void setUpMainText() {
    // Clearing and setting up colors
    print_set_color(PRINT_COLOR_CYAN, PRINT_COLOR_BLUE);
    print_clear();

    print_str(" ------------------------------------ IoOS ------------------------------------ \n");

    //print_char((char)1/0); // Test for IDT
}


#pragma region Debugging Functions

void testPmm() {
    // Printing PMM test passing
    print_str("\n--PMM-Tests--\n");

    bool all_tests_passed = true, passed_test1 = true; // If this turns false it will display a message

    // Creating test blocks to test PMM

    // Test 1: Allocating one block
    void* block1 = allocate_block(1);
    if(block1 != nullptr) {
        print_str("Test 1 Passed! Allocated single block at address: ");
        print_hex((uint32_t)block1);
        print_char('\n');
    } else if(allocation_num > 1) {
        print_set_color(PRINT_COLOR_RED, PRINT_COLOR_BLUE);
        print_str("Test 1 Failed! ");

        print_set_color(PRINT_COLOR_CYAN, PRINT_COLOR_BLUE);
        print_str("Failed to allocate block! \n");

        all_tests_passed = false;
        passed_test1 = false;
    }

    // Test 2: Allocating multiple blocks
    void* block2 = allocate_block(5);
    if(block2 != nullptr) {
        print_str("Test 2 Passed! Allocated five blocks at address: ");
        print_hex((uint32_t)block2);
        print_char('\n');
    } else if(allocation_num > 1) {
        print_set_color(PRINT_COLOR_RED, PRINT_COLOR_BLUE);
        print_str("Test 2 Failed! ");

        print_set_color(PRINT_COLOR_CYAN, PRINT_COLOR_BLUE);
        print_str("Failed to allocate blocks! \n");

        all_tests_passed = false;
    }

    // Test 3: Free the first block
    if(passed_test1) {
        free_block(block1, 1);

        if(is_block_free((uint32_t)block1 / BLOCK_SIZE)) { // Checking memory bitmap
            print_str("Test 3 Passed! Successfully freed up block at: ");
            print_hex((uint32_t)block1);
            print_char('\n');
        } else {
            print_set_color(PRINT_COLOR_RED, PRINT_COLOR_BLUE);
            print_str("Test 3 Failed! ");

            print_set_color(PRINT_COLOR_CYAN, PRINT_COLOR_BLUE);
            print_str("Failed to free up block!\n");

            all_tests_passed = false;
        }
    } else {
        print_set_color(PRINT_COLOR_RED, PRINT_COLOR_BLUE);
        print_str("Test 3 Failed! ");

        print_set_color(PRINT_COLOR_CYAN, PRINT_COLOR_BLUE);
        print_str("Did not find allocated block- \"Block 1\"\n");

        all_tests_passed = false;
    }

    // Test 4: Allocate a block after freeing
    void* block3 = allocate_block(1);
    if(block3 != nullptr) {
        print_str("Test 4 Passed! Allocated block after freeing at address: ");
        print_hex((uint32_t)block3);
        print_char('\n');
    } else if(allocation_num > 1) {
        print_set_color(PRINT_COLOR_RED, PRINT_COLOR_BLUE);
        print_str("Test 4 Failed! ");

        print_set_color(PRINT_COLOR_CYAN, PRINT_COLOR_BLUE);
        print_str("Failed to allocate block after freeing! \n");

        all_tests_passed = false;
    }



    // Final message
    if(!all_tests_passed) {
        print_set_color(PRINT_COLOR_RED, PRINT_COLOR_BLUE);
        print_str("PMM test/s failed!\n");
        print_set_color(PRINT_COLOR_CYAN, PRINT_COLOR_BLUE);
    } else {
        print_set_color(PRINT_COLOR_GREEN, PRINT_COLOR_BLUE);
        print_str("PMM tests passed!\n");
        print_set_color(PRINT_COLOR_CYAN, PRINT_COLOR_BLUE);
    }

    // Free up allocated memory
    set_block_free(0, NUM_BLOCKS);
}

#pragma endregion

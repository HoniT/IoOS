// =====================================
// kernel_main.cpp
// Main file for the kernel
//
// Author: Ioane Baidoshvili
// Date 06-Sep-24
// =====================================

#include <kernel_main.hpp> 

bool PMM_TestPassed = true;


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
    initPmm(); // Physical Memory Manager
    #pragma endregion

    // Setting up text labels
    setUpMainText();
    if(PMM_TestPassed)
        testPmm();

    // Infinite loop
    while(true) {}
    return;
}


// Set up text labels using print functions
// defined in drivers_src/print_src/print.cpp
void setUpMainText() {
    // Clearing and setting up colors
    print_set_color(PRINT_COLOR_GREEN, PRINT_COLOR_BLUE);
    print_clear();

    print_char('\n');
    print_str(" ------------------------------------ IoOS ------------------------------------ ");

    //print_char((char)1/0); // Test for IDT
}


#pragma region Debugging Functions

void testPmm() {
    // Printing PMM test passing
    print_str("\n\n--PMM-Tests--\n");
    print_str("Test 1 Passed Successfully! \n");
    print_str("Test 2 Passed Successfully! \n");
    print_str("Test 3 Passed Successfully! \n");
}

#pragma endregion
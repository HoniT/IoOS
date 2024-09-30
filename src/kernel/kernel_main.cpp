// =====================================
// kernel_main.cpp
// Main file for the kernel
//
// Author: Ioane Baidoshvili
// Date 06-Sep-24
// =====================================

#include <kernel_main.hpp> 


// ========================================
// Function declarations and variables
// ========================================

void setUpText();


#pragma region Magic Number

// Defining magic number to kernel for error debugging
extern "C" {

    const unsigned int KERNEL_MAGIC_NUMBER __attribute__((section(".magic"))) = 0xDEADBEEF;
}

#pragma endregion

extern "C" void kernel_main() {
    // Innitializing Interrupt Descriptor Table
    initIdt();

    // Setting up text labels
    setUpText();

    // Infinite loop
    while(true) {}
    return;
}


// Set up text labels using print functions
// defined in drivers_src/print_src/print.cpp
void setUpText() {
    // Clearing and setting up colors
    print_set_color(PRINT_COLOR_GREEN, PRINT_COLOR_BLUE);
    print_clear();

    print_char('\n');
    print_str(" ------------------------------------ IoOS ------------------------------------ ");
    print_char('>');

    //print_char((char)1/0); // Test for IDT
}
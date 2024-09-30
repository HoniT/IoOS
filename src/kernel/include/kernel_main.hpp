// =====================================
// kernel_main.hpp
// Main header for the kernel
//
// Author: Ioane Baidoshvili
// Date 06-Sep-24
// =====================================

#pragma once

#ifndef KERNEL_MAIN_HPP
#define KERNEL_MAIN_HPP

/* Needed Headers
 * kernel_main.hpp connects every needed header file into one file */

#include <drivers/vga_print.hpp>
#include <interrupts/idt_main.hpp>

extern "C" void kernel_main();

#endif

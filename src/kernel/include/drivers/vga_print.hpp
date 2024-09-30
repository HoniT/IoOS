// =======================================================
// vga_print.hpp
// Header file for printing text through kernel to BIOS
//
// Author: Ioane Baidoshvili
// Date 16-Sep-24
// =======================================================

#pragma once

#ifndef VGA_PRINT_HPP
#define VGA_PRINT_HPP

#include <stdint.h>
#include <stddef.h>


// 16 available colors with VGA
enum VGA_Print_Colors {

    PRINT_COLOR_BLACK = 0,
	PRINT_COLOR_BLUE = 1,
	PRINT_COLOR_GREEN = 2,
	PRINT_COLOR_CYAN = 3,
	PRINT_COLOR_RED = 4,
	PRINT_COLOR_MAGENTA = 5,
	PRINT_COLOR_BROWN = 6,
	PRINT_COLOR_LIGHT_GRAY = 7,
	PRINT_COLOR_DARK_GRAY = 8,
	PRINT_COLOR_LIGHT_BLUE = 9,
	PRINT_COLOR_LIGHT_GREEN = 10,
	PRINT_COLOR_LIGHT_CYAN = 11,
	PRINT_COLOR_LIGHT_RED = 12,
	PRINT_COLOR_PINK = 13,
	PRINT_COLOR_YELLOW = 14,
	PRINT_COLOR_WHITE = 15

};


// Printing functions

void print_clear();
void print_char(const char character);
void print_str(const char* str);
void print_set_color(const uint8_t foreground, const uint8_t background);


#endif
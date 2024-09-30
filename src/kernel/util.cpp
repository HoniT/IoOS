// =====================================
// util.cpp
// Contains function memset
//
// Author: Ioane Baidoshvili
// Date 28-Sep-24
// =====================================

#include <util.hpp>

// Memset sets a block of memory to a specific value for a given number of bytes
void memset(const void *dest, const char val, uint32_t count){
    char *temp = (char*) dest;
    for (; count != 0; count--){
        *temp++ = val;
    }

}

// Sends a 8-bit value to a specified I/O port
void outPortB(const uint16_t Port, const uint8_t Value) {
    asm volatile ("outb %1, %0" : : "dN" (Port), "a" (Value));
}
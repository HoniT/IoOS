// =====================================
// util.hpp
// Header file for util.cpp
//
// Author: Ioane Baidoshvili
// Date 28-Sep-24
// =====================================

#pragma once

#ifndef UTIL_HPP
#define UTIL_HPP

#include <stdint.h>

// Functions defined in util.cpp
void memset(const void *dest, const char val, uint32_t count);
void outPortB(const uint16_t Port, const uint8_t Value);

// Registers related to an interrupt
struct InterruptRegisters{
    uint32_t cr2;
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t interr_no, err_code;
    uint32_t eip, csm, eflags, useresp, ss;
};

#endif
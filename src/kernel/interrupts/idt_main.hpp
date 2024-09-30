// =====================================
// idt_main.hpp
// Header for implementation of the IDT
//
// Author: Ioane Baidoshvili
// Date 27-Sep-24
// =====================================

#pragma once

#ifndef IDT_MAIN_HPP
#define IDT_MAIN_HPP

#include <stdint.h>


// Structs for each entry of the IDT
#pragma region Structs

// Entry struct
struct idt_entry {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t flags;
    uint16_t offset_high;
} __attribute__((packed));

// Pointer struct
struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

#pragma endregion

#pragma region IDT Functions

void initIdt();
void setIdtGate(const uint8_t num, const uint32_t base, const uint16_t selector, const uint8_t flags);

extern "C" void isr_handler(struct InterruptRegisters* regs);


// ========================================
// Interrupt Service Routines
// ========================================

extern "C" {

    extern void isr0();
    extern void isr1();
    extern void isr2();
    extern void isr3();
    extern void isr4();
    extern void isr5();
    extern void isr6();
    extern void isr7();
    extern void isr8();
    extern void isr9();
    extern void isr10();
    extern void isr11();
    extern void isr12();
    extern void isr13();
    extern void isr14();
    extern void isr15();
    extern void isr16();
    extern void isr17();
    extern void isr18();
    extern void isr19();
    extern void isr20();
    extern void isr21();
    extern void isr22();
    extern void isr23();
    extern void isr24();
    extern void isr25();
    extern void isr26();
    extern void isr27();
    extern void isr28();
    extern void isr29();
    extern void isr30();
    extern void isr31();
    // Syscalls
    extern void isr128();
    extern void isr177();

// ========================================
// Interrupt Requests
// ========================================

    extern void irq0();
    extern void irq1();
    extern void irq2();
    extern void irq3();
    extern void irq4();
    extern void irq5();
    extern void irq6();
    extern void irq7();
    extern void irq8();
    extern void irq9();
    extern void irq10();
    extern void irq11();
    extern void irq12();
    extern void irq13();
    extern void irq14();
    extern void irq15();
}

#pragma endregion

#endif
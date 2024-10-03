# ==========================================
# Makefile
# For building the project
#
# Author: Ioane Baidoshvili
# Date: 02-Sep-24
# ==========================================

# Directories
BOOTLOADER_DIR = src/bootloader
KERNEL_DIR = src/kernel

BIN = $(CURDIR)/bin
BUILD = $(CURDIR)/build

# HPP include directories
INCLUDE = -I src/kernel/include -I src/kernel

# Tools
ASM = nasm
OBJCOPY = i686-elf-objcopy

CXX = i686-elf-g++
CXX_FLAGS = $(INCLUDE) -g -Wall -O2 -ffreestanding -mgeneral-regs-only \
           -fno-exceptions -fno-rtti -fno-pic -fno-asynchronous-unwind-tables

ELF_LD = i686-elf-ld
ELF_LD_FLAGS =

GCC = i686-elf-gcc
GCC_LINK_FLAGS = -nostdlib -nostartfiles -nodefaultlibs -no-pie -Wl,--build-id=none

# Output files
OS_BIN = $(BIN)/os.bin # Combined binary file
OS_ELF = $(BIN)/os.elf # Combined ELF file
DISK_IMG = $(BIN)/disk.img # Disk Image

BOOT_OBJ = $(BUILD)/boot.o
KERNEL_ENTRY_OBJ = $(BUILD)/kernel_entry.o

KERNEL_OBJ = $(BUILD)/kernel_main.o
PRINT_OBJ = $(BUILD)/print.o
UTIL_OBJ = $(BUILD)/util.o 
IDT_MAIN_OBJ = $(BUILD)/idt_main.o
IDT_OBJ = $(BUILD)/idt.o
PMM_MAIN_OBJ = $(BUILD)/pmm_main.o
ENABLE_PAGING_OBJ = $(BUILD)/enable_paging.o 
PAGING_OBJ = $(BUILD)/paging.o

all:

# Compiling ASM files
	$(ASM) -f elf -g $(BOOTLOADER_DIR)/boot.asm -o $(BOOT_OBJ)
	$(ASM) -f elf -g $(BOOTLOADER_DIR)/kernel_entry.asm -o $(KERNEL_ENTRY_OBJ)
	$(ASM) -f elf -g $(KERNEL_DIR)/interrupts/idt.asm -o $(IDT_OBJ)
	$(ASM) -f elf -g $(KERNEL_DIR)/memory_src/enable_paging.asm -o $(ENABLE_PAGING_OBJ)

# Compiling CPP files
	$(CXX) -I./src $(CXX_FLAGS) -std=c++23 -c $(KERNEL_DIR)/kernel_main.cpp -o $(KERNEL_OBJ)
	$(CXX) -I./src $(CXX_FLAGS) -std=c++23 -c $(KERNEL_DIR)/drivers_src/vga_print.cpp -o $(PRINT_OBJ)
	$(CXX) -I./src $(CXX_FLAGS) -std=c++23 -c $(KERNEL_DIR)/util.cpp -o $(UTIL_OBJ)
	$(CXX) -I./src $(CXX_FLAGS) -std=c++23 -c $(KERNEL_DIR)/interrupts/idt_main.cpp -o $(IDT_MAIN_OBJ)
	$(CXX) -I./src $(CXX_FLAGS) -std=c++23 -c $(KERNEL_DIR)/memory_src/pmm_main.cpp -o $(PMM_MAIN_OBJ)
	$(CXX) -I./src $(CXX_FLAGS) -std=c++23 -c $(KERNEL_DIR)/memory_src/paging.cpp -o $(PAGING_OBJ)

# Link all object files (bootloader + kernel) into an ELF file and binary file
	$(GCC) $(GCC_LINK_FLAGS) -T tools/linker.ld -o $(OS_ELF) \
		$(BOOT_OBJ) $(KERNEL_ENTRY_OBJ) $(KERNEL_OBJ) $(PRINT_OBJ) $(UTIL_OBJ) $(IDT_MAIN_OBJ) $(IDT_OBJ) $(PMM_MAIN_OBJ) $(ENABLE_PAGING_OBJ) $(PAGING_OBJ)
	$(OBJCOPY) -O binary $(OS_ELF) $(OS_BIN)

# Create 10MiB disk image
	dd if=/dev/zero of=$(DISK_IMG) bs=1M count=10
	dd if=$(OS_BIN) of=$(DISK_IMG) seek=0 conv=notrunc

# Cleaning the build
clean:
	rm -f $(OS_BIN)
	rm -f $(OS_ELF)
	rm -f $(DISK_IMG)

	rm -f $(KERNEL_ENTRY_OBJ) 
	rm -f $(BOOT_OBJ) 
	rm -f $(KERNEL_OBJ)
	rm -f $(PRINT_OBJ) 
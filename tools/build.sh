
# Preparation

export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

# Making project

make clean
make all

# Running QEMU

qemu-system-i386 -drive file=bin/os.bin,format=raw

# Author: Ioane Baidoshvili
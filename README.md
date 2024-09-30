# IoOS

IoOS is a simple operating system designed for testing and educational reasons.

![License](LICENSE)


## Table of contents
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)


# Installation

1. Clone the repository:
    ``` bash
    git clone https://www.github.com/HoniT/IoOS
    ```

2. Install dependencies:
    - On Linux:
        Installing QEMU
        ``` bash
        sudo apt install qemu qemu-system-i386
        ```

        Installing compilers
        ``` bash
        sudo apt install nasm gcc g++ gdb
        ```
    
    - On Windows:
        You will need to use package managers such as MinGW or Cygwin.
        To install NASM and QEMU, visit they're site and follow instructions.

3. Install the GCC cross-compiler:
    Follow instructions on the [OSDevOrg](https://www.wiki.osdev.org/GCC_Cross-Compiler).


# Usage

To use this project simply use the bash script located in tools. To do so:

    ``` bash
    bash ./tools/build.sh
    ```


## Features

- 32-bit Operating System
- Kernel written in C++
- Interrupt Descriptor Table

(More will come in future)


# Contributing

Contributioners are welcome to submit there version of my code on my [GitHub](https://www.github.com/HoniT/IoOS).


# License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.



## Credits
- Thanks to [Michael Petch](https://www.github.com/mpetch) for contributing to this project.
- Project author: [Ioane Baidoshvili](https://www.github.com/HoniT).
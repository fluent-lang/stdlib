/*
    These files are part of the Surf's standard library.
    They're bundled with the main program by the compiler
    which is then converted to machine code.

    -----
    License notice:

    This code is released under the GNU GPL v3 license.
    The code is provided as is without any warranty
    Copyright (c) 2024 Rodrigo R. & all Surf contributors
*/

#ifndef PRINT_H
#define PRINT_H

#include <iostream>

template <typename T>
void print(const T& str) {
    std::cout << str;
}

template <typename T>
void println(const T& str) {
    // Check if the type is a pointer
    if constexpr (std::is_pointer_v<T>) {
        std::cout << *str << std::endl;
        return;
    }

    std::cout << str << std::endl;
}

#endif

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

#include <iostream>
#include "panic.h"

void panic(const char* message, const char* file, int line) {
    std::cerr << 
        "Panic: " << message << std::endl
        << "    Thread panicked at '" << file << "'" << std::endl
        << "      line " << line << std::endl;
    exit(EXIT_FAILURE);
}
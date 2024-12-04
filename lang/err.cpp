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

#include "err.hpp"

#include <iostream>
#include <string>

GenericErr::GenericErr(std::string message, const char* file, int f_line) : message(std::move(message)) {}

std::string GenericErr::get_message(const char* file, int f_line) const {
    return message;
}

std::ostream& operator<<(std::ostream& os, const GenericErr& err) {
    os << "Err(" << err.get_message("", 0) << ")";
    return os;
}
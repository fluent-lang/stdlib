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
#include "../lang/string.hpp"

GenericErr::GenericErr(const char* message) : message(message) {}

String GenericErr::get_message() const {
    return message;
}

std::ostream& operator<<(std::ostream& os, const GenericErr& err) {
    os << "Err(" << err.get_message().to_str() << ")";
    return os;
}
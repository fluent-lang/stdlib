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

#ifndef ERR_H
#define ERR_H

#include <iostream>
#include "../lang/string.hpp"

class GenericErr {
    String message;

    public:
        explicit GenericErr(const char* message);
        String get_message() const;
};

std::ostream& operator<<(std::ostream& os, const GenericErr& err);

#endif

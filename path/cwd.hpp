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

#ifndef CWD_H
#define CWD_H

#include <string>
#include "../lang/result.hpp"
#include "../lang/err.hpp"
#include "../lang/string.hpp"

Result<String, GenericErr> get_cwd();

#endif
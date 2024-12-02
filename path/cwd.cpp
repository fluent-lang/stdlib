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

#include "cwd.h"

#include <iostream>
#include <unistd.h>
#include <limits.h>
#include "../lang/result.h"

Result<std::string> get_cwd() {
    // Allocate a buffer for the current working directory
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        return Result(std::string(cwd), optional<Err>());
    }

    return Result(
        std::string(""), 
        optional<Err>(Err("Failed to get current working directory"))
    );
}
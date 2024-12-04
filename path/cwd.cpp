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

#include "cwd.hpp"

#include <iostream>
#include <unistd.h>
#include <limits.h>
#include "../lang/result.hpp"

using namespace std;

Result<string, GenericErr> get_cwd(const char* file, int f_line) {
    // Allocate a buffer for the current working directory
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        return Result<string, GenericErr>(string(cwd), nullopt);
    }

    return Result(
        string(""), 
        optional<GenericErr>(GenericErr("Failed to get current working directory"))
    );
}
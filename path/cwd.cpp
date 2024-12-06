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
#include "../lang/string.hpp"
#include "../lang/opt.hpp"

using namespace std;

Result<String, GenericErr> get_cwd() {
    // Allocate a buffer for the current working directory
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        return Result<String, GenericErr>(String(cwd), None<GenericErr>());
    }

    return Result(
        String(""),
        Some<GenericErr>(GenericErr("Failed to get current working directory"))
    );
}
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

#include "env.hpp"

#include <string>
#include "../lang/result.hpp"
#include "../lang/err.hpp"
#include "../lang/string.hpp"

using namespace std;

Result<String, GenericErr> get_env(const char* key) {
    char* value = getenv(key);

    if (value == NULL) {
        return Result(
            String(""), 
            optional<GenericErr>(GenericErr("Environment variable not found"))
        );
    }

    return Result<String, GenericErr>(String(value), nullopt);
}

Result<bool, GenericErr> set_env(const char* key, const char* value) {
    if (setenv(key, value, 1) != 0) {
        return Result(
            false, 
            optional<GenericErr>(GenericErr("Failed to set environment variable"))
        );
    }

    return Result<bool, GenericErr>(true, nullopt);
}
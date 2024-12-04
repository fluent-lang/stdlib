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

using namespace std;

Result<string, GenericErr> get_env(const string* key, const char* file, int f_line) {
    char* value = getenv(key->c_str());

    if (value == NULL) {
        return Result(
            string(""), 
            optional<GenericErr>(GenericErr("Environment variable not found", file, f_line))
        );
    }

    return Result<string, GenericErr>(string(value), nullopt);
}

Result<bool, GenericErr> set_env(const string* key, const string* value, const char* file, int f_line) {
    if (setenv(key->c_str(), value->c_str(), 1) != 0) {
        return Result(
            false, 
            optional<GenericErr>(GenericErr("Failed to set environment variable", file, f_line))
        );
    }

    return Result<bool, GenericErr>(true, nullopt);
}
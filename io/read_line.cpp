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

#include "read_line.hpp"
#include "../lang/result.hpp"
#include "../lang/err.hpp"
#include "../lang/string.hpp"
#include <iostream>
#include <string>
#include <optional>

using namespace std;

Result<String, GenericErr> read_line() {
    try {
        string line;

        getline(cin, line);
        return Result<String, GenericErr>(move(String(line.c_str())), nullopt);
    } catch(const exception& e) {
        return Result<String, GenericErr>(String(""), optional<GenericErr>(GenericErr(e.what())));
    }
    
}
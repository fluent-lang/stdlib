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

#ifndef FILES_H
#define FILES_H

#include <iostream>
#include <string>
#include <vector>
#include "../lang/result.hpp"
#include "../lang/err.hpp"
#include "../lang/string.hpp"
#include "../lang/vec.hpp"

Result<bool, GenericErr> write_file(const char* path, const char* content);
Result<String, GenericErr> read_file(const char* path);
Result<bool, GenericErr> delete_file(const char* path);
Result<bool, GenericErr> remove_dir(const char* path);
Result<Vec<String>, GenericErr> walk_dir(const char* path);

#endif
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

#include "join.hpp"

#include <string>

String get_path_separator() {
    #ifdef _WIN32
        return String("\\");
    #else
        return String("/");
    #endif
}

String join_path(const char* path1, const char* path2) {
    String path = String(path1);
    String separator = get_path_separator();
    int length = strnlen(path1, sizeof(path) - 1);

    if (path.at(length - 1) != separator.at(0)) {
        path.push_string(separator);
    }

    path.push_raw(path2);

    return path;
}
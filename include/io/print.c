/*
    This file is part of the Fluent Language Standard Library (Fluent-Standard)
    This code is released under the GNU General Public License (GPL) v3.0.
    For more information, please refer to the LICENSE file.
    ----------------------------------------------------------
    Copyright (C) 2024 Rodrigo R. & All Fluent Contributors
    This program comes with ABSOLUTELY NO WARRANTY; for details type `fluent license`.
    This is free software, and you are welcome to redistribute it under certain conditions;
    type `fluent license --full` for details.
*/

#include <stdio.h>

/**
    * @brief Prints the given argument to the standard output.
    * @param str The string to be printed.
    * @return void
*/
void print(const char* str) {
    printf("%s", str);
}

/**
    * @brief Prints the given argument with a newline to the standard output.
    * @param str The string to be printed.
    * @return void
*/
void println(const char* str) {
    printf("%s\n", str);
}

extern void print(const char* str);
extern void println(const char* str);
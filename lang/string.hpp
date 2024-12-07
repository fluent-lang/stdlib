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

#ifndef STRING_HPP
#define STRING_HPP

#include <string>
#include <cstring>
#include "./vec.hpp"

class String {

    std::string data;
    public:
        explicit String(const char* data);

        const char* to_str() const;
        void push_raw(const char* additional_data);
        void push_string(String another_string);
        void clear();
        char at(int index);
        int length();
        bool is_empty();
        bool starts_with(const char* prefix);
        bool ends_with(const char* suffix);
        String substring(int start, int end);
        String replace(const char* old_str, const char* new_str);
        String to_upper();
        String to_lower();
        String trim();
        String trim_start();
        String trim_end();
        String reverse();
        String repeat(int times);
        String slice(int start, int end);
        String pad_start(int length, const char* pad);
        String pad_end(int length, const char* pad);
        String remove(int start, int end);
        String remove_all(const char* str);
        String remove_prefix(const char* prefix);
        String remove_suffix(const char* suffix);
        String insert(int index, const char* str);
        String insert_all(int index, const char* str);
        String insert_prefix(const char* prefix);
        String insert_suffix(const char* suffix);
        Vec<String> split(const char* delimiter);
        bool compare_raw(const char* str) const;
        bool compare_string(String another_string) const;
        // Makes a new string joining the current string with another string
        String join(String other_str);

        friend bool operator==(const String& obj1, const String& obj2);
};

std::ostream& operator<<(std::ostream& os, const String& res);

#endif
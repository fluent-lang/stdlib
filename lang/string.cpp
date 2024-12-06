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

#include "string.hpp"

String::String(const char* str) {
    data = std::string(str);
}

const char* String::to_data() const {
    return data.c_str();
}

void String::push_raw(const char* additional_data) {
    data += additional_data;
}

void String::push_string(String another_string) {
    data += another_string.to_data();
}

void String::clear() {
    data.clear();
}

char String::at(int index) {
    return data.at(index);
}

int String::length() {
    return data.length();
}

bool String::is_empty() {
    return data.empty();
}

bool String::starts_with(const char* prefix) {
    return data.rfind(prefix, 0) == 0;
}

bool String::ends_with(const char* suffix) {
    return data.rfind(suffix) == data.length() - 1;
}

String String::substring(int start, int end) {
    return String(data.substr(start, end).c_str());
}

String String::replace(const char* old_str, const char* new_str) {
    return String(data.replace(data.find(old_str), strlen(old_str), new_str).c_str());
}

String String::to_upper() {
    std::string upper_data = data;
    for (char& c : upper_data) {
        c = toupper(c);
    }
    return String(upper_data.c_str());
}

String String::to_lower() {
    std::string lower_data = data;
    for (char& c : lower_data) {
        c = tolower(c);
    }
    return String(lower_data.c_str());
}

String String::trim() {
    std::string trimmed_data = data;
    trimmed_data.erase(0, trimmed_data.find_first_not_of(" \t\n\r\f\v"));
    trimmed_data.erase(trimmed_data.find_last_not_of(" \t\n\r\f\v") + 1);
    return String(trimmed_data.c_str());
}

String String::trim_start() {
    std::string trimmed_data = data;
    trimmed_data.erase(0, trimmed_data.find_first_not_of(" \t\n\r\f\v"));
    return String(trimmed_data.c_str());
}

String String::trim_end() {
    std::string trimmed_data = data;
    trimmed_data.erase(trimmed_data.find_last_not_of(" \t\n\r\f\v") + 1);
    return String(trimmed_data.c_str());
}

String String::reverse() {
    std::string reversed_data = data;
    std::reverse(reversed_data.begin(), reversed_data.end());
    return String(reversed_data.c_str());
}

String String::repeat(int times) {
    std::string repeated_data = data;
    for (int i = 0; i < times; i++) {
        repeated_data += data;
    }
    return String(repeated_data.c_str());
}

String String::slice(int start, int end) {
    return String(data.substr(start, end).c_str());
}

String String::pad_start(int length, const char* pad) {
    std::string padded_data = data;
    while (padded_data.length() < length) {
        padded_data = pad + padded_data;
    }
    return String(padded_data.c_str());
}

String String::pad_end(int length, const char* pad) {
    std::string padded_data = data;
    while (padded_data.length() < length) {
        padded_data += pad;
    }
    return String(padded_data.c_str());
}

String String::remove(int start, int end) {
    return String(data.erase(start, end).c_str());
}

String String::remove_all(const char* str) {
    std::string removed_data = data;
    size_t pos = 0;
    while ((pos = removed_data.find(str, pos)) != std::string::npos) {
        removed_data.erase(pos, strlen(str));
    }
    return String(removed_data.c_str());
}

String String::remove_prefix(const char* prefix) {
    return String(data.substr(strlen(prefix)).c_str());
}

String String::remove_suffix(const char* suffix) {
    return String(data.substr(0, data.length() - strlen(suffix)).c_str());
}

String String::insert(int index, const char* str) {
    return String(data.insert(index, str).c_str());
}

String String::insert_all(int index, const char* str) {
    return String(data.insert(index, str).c_str());
}

String String::insert_prefix(const char* prefix) {
    return String(data.insert(0, prefix).c_str());
}

String String::insert_suffix(const char* suffix) {
    return String(data.insert(data.length(), suffix).c_str());
}

Vec<String> String::split(const char* delimiter) {
    Vec<String> splitted_data = Vec<String>();

    std::string data_copy = data;
    size_t pos = 0;

    while ((pos = data_copy.find(delimiter)) != std::string::npos) {
        splitted_data.push(String(data_copy.substr(0, pos).c_str()));
        data_copy.erase(0, pos + strlen(delimiter));
    }
    
    splitted_data.push(String(data_copy.c_str()));
    return splitted_data;
}

bool String::compare_raw(const char* str) const {
    return data.compare(str) == 0;
}

bool String::compare_string(String another_string) const {
    return data.compare(another_string.to_data()) == 0;
}

String String::join(String other_str) {
    return String((data + other_str.to_data()).c_str());
}

std::ostream& operator<<(std::ostream& os, const String& res) {
    os << "String(";
    os << "\"";
    os << res.to_data();
    os << "\"";
    os << ")";

    return os;
}
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

#ifndef OPT_HPP
#define OPT_HPP

#include "../lang/panic.h"
#include <optional>
#include <iostream>

template <typename T>
class Optional {
    private:
        std::optional<T> value;
    public:
        Optional(T value);
        T&& unwrap();
        bool is_some();
        bool is_none();
};

template <typename T>
Optional<T>::Optional(T value) {
    this->value = std::optional<T>(value);
}

template <typename T>
T&& Optional<T>::unwrap() {
    if (!this->value.has_value()) {
        panic("Called unwrap on an empty optional");
    }

    return std::move(this->value.value());
}

template <typename T>
bool Optional<T>::is_some() {
    return this->value.has_value();
}

template <typename T>
bool Optional<T>::is_none() {
    return !this->is_some();
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Optional<T>& res) {
    os << "Optional(";

    if (res.is_some()) {
        os << res.unwrap();
    } else {
        os << "None";
    }

    os << ")";
    
    return os;
}

template <typename T>
Optional<T> Some(T value) {
    return Optional<T>(value);
}

template <typename T>
Optional<T> None() {
    return Optional<T>();
}

#endif
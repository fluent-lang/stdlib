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

#ifndef RESULT_H
#define RESULT_H

#include "err.hpp"
#include "panic.h"
#include <optional>
#include <utility>
#include <iostream>

template <typename T, typename E = GenericErr>
class Result {
private:
    T value;
    std::optional<E> error;

public:
    // Constructor
    Result(T&& value, std::optional<E> error = std::nullopt)
        : value(std::move(value)), error(error) {}

    // Methods
    bool has_error() const { return error.has_value(); }

    const T& unwrap() const {
        if (has_error()) {
            panic(error.value().get_message().c_str());
        }
        return value;
    }

    T unwrap_or(const T& default_value) const {
        return has_error() ? default_value : value;
    }

    const GenericErr& get_error() const {
        if (!has_error()) {
            panic("Attempted to get error from a successful Result");
        }
        return error.value();
    }
};

template <typename T, typename E = GenericErr>
Result<T, E> Ok(T&& value) {
    return Result<T, E>(std::forward<T>(value), std::nullopt);
}

template <typename E, typename T = void>
Result<T, E> Err(E&& value) {
    return Result<T, E>(T{}, std::optional<E>(std::forward<E>(value)));
}

template <typename T, typename E>
std::ostream& operator<<(std::ostream& os, const Result<T, E>& res) {
    os << "Result(";
    if (res.has_error()) {
        os << "None, Err(" << res.get_error() << "))";
    } else {
        os << "Some(" << res.unwrap() << "), None)";
    }
    return os;
}

#endif

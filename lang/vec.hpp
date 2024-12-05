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

#ifndef VEC_HPP
#define VEC_HPP

#include <vector>
#include "./opt.hpp"

template <typename T>
class Vec {

    private:
        std::vector<T> data;

    public:
        Vec();
        ~Vec();

        void push(T item);
        void push_all(Vec<T> other);
        void clear();
        Optional<T> at(int index);
        int length();
        bool is_empty();
        Vec<T> slice(int start, int end);
        Vec<T> remove(int start, int end);
        Vec<T> remove_all(T item);
        Vec<T> insert(int index, T item);
        Vec<T> insert_all(int index, Vec<T> items);
};

template <typename T>
Vec<T>::Vec() {
    data = std::vector<T>();
}

template <typename T>
Vec<T>::~Vec() {
    data.clear();
}

template <typename T>
void Vec<T>::push(T item) {
    data.push_back(item);
}

template <typename T>
void Vec<T>::push_all(Vec<T> other) {
    for (T item : other.data) {
        data.push_back(item);
    }
}

template <typename T>
void Vec<T>::clear() {
    data.clear();
}

template <typename T>
Optional<T> Vec<T>::at(int index) {
    if (index < 0 || index >= data.size()) {
        return Optional<T>();
    }

    return Optional<T>(data.at(index));
}

template <typename T>
int Vec<T>::length() {
    return data.size();
}

template <typename T>
bool Vec<T>::is_empty() {
    return data.empty();
}

template <typename T>
Vec<T> Vec<T>::slice(int start, int end) {
    Vec<T> sliced_vec = Vec<T>();

    for (int i = start; i < end; i++) {
        sliced_vec.push(data.at(i));
    }

    return sliced_vec;
}

template <typename T>
Vec<T> Vec<T>::remove(int start, int end) {
    Vec<T> removed_vec = Vec<T>();

    for (int i = 0; i < data.size(); i++) {
        if (i < start || i >= end) {
            removed_vec.push(data.at(i));
        }
    }

    return removed_vec;
}

template <typename T>
Vec<T> Vec<T>::remove_all(T item) {
    Vec<T> removed_vec = Vec<T>();

    for (T current_item : data) {
        if (current_item != item) {
            removed_vec.push(current_item);
        }
    }

    return removed_vec;
}

template <typename T>
Vec<T> Vec<T>::insert(int index, T item) {
    Vec<T> inserted_vec = Vec<T>();

    for (int i = 0; i < data.size(); i++) {
        if (i == index) {
            inserted_vec.push(item);
        }

        inserted_vec.push(data.at(i));
    }

    return inserted_vec;
}

template <typename T>
Vec<T> Vec<T>::insert_all(int index, Vec<T> items) {
    Vec<T> inserted_vec = Vec<T>();

    for (int i = 0; i < data.size(); i++) {
        if (i == index) {
            for (T item : items.data) {
                inserted_vec.push(item);
            }
        }

        inserted_vec.push(data.at(i));
    }

    return inserted_vec;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vec<T>& res) {
    os << "Vec[";

    int size = res.length();
    int iterated_items = 0;

    for (const auto& item : res) {
        os << item;

        if (iterated_items != size - 1) {
            os << ", ";
        }

        iterated_items++;
    }

    os << "]";
    
    return os;
}

#endif
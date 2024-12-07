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

#ifndef HEAP_HPP
#define HEAP_HPP

#include <utility>
#include <iostream>
#include "../lang/panic.h"

template <typename T>
class Heap {
    public:
        Heap(const Heap& other);
        Heap& operator=(const Heap& other);
        Heap(Heap&& other) noexcept;
        Heap& operator=(Heap&& other) noexcept;
        T* heap_data;
    public:
        Heap(T stack_allocated_value);
        ~Heap();
        T& unwrap() const {
            if (!heap_data) {
                panic(
                    "Thread attempted to access an invalid memory reference.\nSurf has exited with a Segmentation Fault (core dumped)."
                );
            }
            return *heap_data;
        }
};

template <typename T>
Heap<T>::Heap(T stack_allocated_value) {
    heap_data = new T(stack_allocated_value); 
}
template <typename T>
Heap<T>::Heap(const Heap& other) {
    heap_data = new T(*other.heap_data);
}

template <typename T>
Heap<T>& Heap<T>::operator=(const Heap& other) {
    if (this != &other) {
        delete heap_data;
        heap_data = new T(*other.heap_data);
    }
    return *this;
}

template <typename T>
Heap<T>::Heap(Heap&& other) noexcept : heap_data(other.heap_data) {
    other.heap_data = nullptr;
}

template <typename T>
Heap<T>& Heap<T>::operator=(Heap&& other) noexcept {
    if (this != &other) {
        delete heap_data;
        heap_data = other.heap_data;
        other.heap_data = nullptr;
    }
    return *this;
}

template <typename T>
Heap<T>::~Heap() {
    delete heap_data;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Heap<T>& res) {
    os << "Heap(";
    os << "(Native memory); ";
    os << res.unwrap();
    os << ")";
    return os;
}

#endif
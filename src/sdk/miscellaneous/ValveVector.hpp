#ifndef ANIUM_VALVEVECTOR_HPP
#define ANIUM_VALVEVECTOR_HPP

#include "ValveMemory.hpp"

template <typename T, typename A = ValveMemory<T>>
class ValveVector {
private:
    A memory;
    int size;
    T* elements;

public:
    A& GetMemory() const {
        return this->memory;
    }

    int GetSize() const {
        return this->size;
    }

    T& GetElements() {

    }

};

#endif  // ANIUM_VALVEVECTOR_HPP

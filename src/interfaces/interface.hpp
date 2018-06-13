#ifndef ANIUM_INTERFACE_HPP
#define ANIUM_INTERFACE_HPP

#include "../utils/sourcelib.hpp"

template <typename T>
class Interface {
private:
    T* interface = nullptr;

public:
    void AssignFromInterface(SourceLib lib, std::string interface, int version) {
        T* target = lib.GrabInterface<T>(interface, version);

        if (target != nullptr) {
            this->interface = target;
        }
    }

    void AssignFromPointer(T* pointer) {
        if (pointer != nullptr) {
            this->interface = pointer;
        }
    }

    T* operator->() {
        return this->interface;
    }

    operator T*() {
        return this->interface;
    }

    bool IsAssigned() {
        return this->interface != nullptr;
    }

    T* GetInterface() {
        return this->interface;
    }

};

#endif  // ANIUM_INTERFACE_HPP

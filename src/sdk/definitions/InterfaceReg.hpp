#ifndef ANIUM_INTERFACEREG_HPP
#define ANIUM_INTERFACEREG_HPP

using InstantiateInterfaceFn = void* (*)();

struct InterfaceReg {
    InstantiateInterfaceFn create;
    const char* name;
    InterfaceReg* next;

};

#endif  // ANIUM_INTERFACEREG_HPP

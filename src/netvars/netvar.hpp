#ifndef ANIUM_NETVAR_HPP
#define ANIUM_NETVAR_HPP

#include <cstdint>
#include <string>
#include <vector>
#include "netvartree.hpp"

// For this whole NetVar system, I took inspiration and parts of blue's NetVar system from F1ssi0n.
// Credit, huge thanks and a shout out to him for being a chill and cool guy and providing a smart way of doing netvars.

// Pre-declare
class NetVar;
static NetVar* head;

class NetVar {
private:
    uintptr_t offset;
    std::vector<std::string> tables;

    NetVar* next; // Recursion

    static NetVarTree tree;

    void Init() {
        this->offset = this->tree.FindOffset(this->tables);
    }

public:
    template <typename... A>
    NetVar(A... args) {
        this->tables = { args... };

        this->next = head;
        head = this;
    }

    static void InitAll() {
        tree.Init();

        for (NetVar* netvar = head; netvar != nullptr; netvar = netvar->next) {
            netvar->Init();
        }
    }

    template <typename T>
    T& Get(void* instance) {
        return *reinterpret_cast<T*>(((char*) instance) + this->offset);
    }

};

#endif  // ANIUM_NETVAR_HPP

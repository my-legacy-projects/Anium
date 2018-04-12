#ifndef ANIUM_IBASECLIENTDLL_HPP
#define ANIUM_IBASECLIENTDLL_HPP

#include <cstdint>
#include "../../hooks/vfunc.hpp"
#include "../definitions/EClassIds.hpp"
#include "../miscellaneous/Recv.hpp"

class IClientNetworkable;

using CreateClientClassFn = IClientNetworkable* (*)(int, int);
using CreateEventFn = IClientNetworkable* (*)();

class ClientClass {
public:
    CreateClientClassFn createFunc;
    CreateEventFn* createEventFunc;
    char* networkName;
    RecvTable* recvTable;
    ClientClass* next;
    EClassIds classID;

};

class IBaseClientDLL {
public:
    ClientClass* GetAllClasses() {
        using oGetAllClasses = ClientClass* (*)(void*);
        return VFunc(this, 8, 8, 8).GetFunction<oGetAllClasses>()(this);
    }

};

#endif  // ANIUM_IBASECLIENTDLL_HPP

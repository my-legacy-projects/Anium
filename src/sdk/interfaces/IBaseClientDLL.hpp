#ifndef ANIUM_IBASECLIENTDLL_HPP
#define ANIUM_IBASECLIENTDLL_HPP

#include <cstdint>
#include "../../hooks/vfunc.hpp"
#include "../definitions/EClassIds.hpp"
#include "../miscellaneous/Recv.hpp"

class IClientNetworkable;

typedef IClientNetworkable* (*CreateClientClassFn)(int entity, int serial);
typedef IClientNetworkable* (*CreateEventFn)();

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
        typedef ClientClass* (*oGetAllClasses)(void*);
        return VFunc(this, 8, 8, 8).GetFunction<oGetAllClasses>()(this);
    }

};

#endif  // ANIUM_IBASECLIENTDLL_HPP

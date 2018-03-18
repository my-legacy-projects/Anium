#ifndef ANIUM_ANIUM_HPP
#define ANIUM_ANIUM_HPP

#include <cstdlib>
#include <thread>
#include "events/eventbus.hpp"
#include "hooks/hooker.hpp"
#include "netvars/netvar.hpp"
#include "utils/logging.hpp"
#include "utils/platformutils.hpp"
#include "vmt/vmt.hpp"

#if defined(_WIN32)
    #include <Windows.h>
#elif defined(__linux__) || defined(__APPLE__)
    // Define Windows-only calling convention to default to nothing on *nix
    #define __fastcall
    #define __thiscall
    #define __stdcall
    #define __cdecl
    #define HMODULE void*
#endif

#if defined(_WIN32)
    extern HMODULE aniumModule;
#endif

namespace Anium {

    int Init(HMODULE self = nullptr);

    int Destroy();

    // Exit() may be called for self shutting down from for example the UI
    void Exit();

}

#endif //ANIUM_ANIUM_HPP

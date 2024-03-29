#ifndef ANIUM_ANIUM_HPP
#define ANIUM_ANIUM_HPP

#include <clocale>
#include <cstdlib>
#include <thread>
#include "hooks/hooker.hpp"
#include "netvars/netvar.hpp"
#include "utils/logging.hpp"
#include "utils/platforms.hpp"
#include "vmt/vmt.hpp"

#if defined(_WIN32)
    #define WIN32_LEAN_AND_MEAN
    #include <Windows.h>

    // CreateFont and DrawText are defined by WinAPI
    // Our ISurface uses these methods, so let's undefine them so we can use them
    #undef CreateFont
    #undef DrawText

    // interface is defined to a struct by WinAPI
    // Our Valve interfaces wrapper uses that name though, so let's undefine them so we can use them
    #undef interface
#elif defined(__linux__) || defined(__APPLE__)
    // Define Windows-only calling convention to default to nothing on *nix
    #define __fastcall
    #define __thiscall
    #define __stdcall
    #define __cdecl
#endif

#if defined(_WIN32)
    extern void* aniumModule;
    extern bool aniumActive;
#endif

namespace Anium {

    int Init(void* self = nullptr);

    int Destroy();

    // Exit() may be called for self shutting down from for example the UI
    void Exit();

}

#endif //ANIUM_ANIUM_HPP

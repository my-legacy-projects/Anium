#ifndef ANIUM_ANIUM_HPP
#define ANIUM_ANIUM_HPP

#include <cstdlib>
#include <thread>
#include "common.hpp"
#include "hooks/hooker.hpp"

#if defined(__unix__) || defined(__APPLE__)
    #define ANIUM_UNIX true

    // Define Windows-only calling convention to default to nothing on *nix
    #define __fastcall
    #define __stdcall
    #define __cdecl

    #if defined(__APPLE__)
        #define ANIUM_MAC true
    #else
        #define ANIUM_LINUX true
    #endif
#else
    #define ANIUM_WINDOWS true
    #include <Windows.h>
#endif

namespace Anium {

    int Init();

    int Destroy();

}

#endif //ANIUM_ANIUM_HPP

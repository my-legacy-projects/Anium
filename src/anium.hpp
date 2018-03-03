#ifndef ANIUM_ANIUM_HPP
#define ANIUM_ANIUM_HPP

#include <cstdlib>
#include <thread>
#include "common.hpp"
#include "hooks/hooker.hpp"

#if defined(_WIN32)
    #include <Windows.h>
#elif defined(__linux__) || defined(__APPLE__)
    // Define Windows-only calling convention to default to nothing on *nix
    #define __fastcall
    #define __stdcall
    #define __cdecl
    #define HMODULE void*
#endif

namespace Anium {

    int Init(HMODULE self = nullptr);

    int Destroy(HMODULE self = nullptr);

}

#endif //ANIUM_ANIUM_HPP

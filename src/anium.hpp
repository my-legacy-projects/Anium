#ifndef ANIUM_ANIUM_HPP
#define ANIUM_ANIUM_HPP

#include <cstdlib>
#include <thread>
#include <iostream>
#include "interfaces/interfaces.hpp"

#if defined(__unix__) || defined(__APPLE__)
    #define ANIUM_UNIX

    // Define Windows-only calling convention to default to nothing on *nix
    #define __fastcall
    #define __stdcall
    #define __cdecl

    #if defined(__APPLE__)
        #define ANIUM_MAC
    #else
        #define ANIUM_LINUX
    #endif
#else
    #define ANIUM_WINDOWS
    #include <Windows.h>
#endif

namespace Anium {

    int Init();

    int Destroy();

}

#endif //ANIUM_ANIUM_HPP

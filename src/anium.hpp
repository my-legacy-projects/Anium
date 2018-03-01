#ifndef ANIUM_ANIUM_HPP
#define ANIUM_ANIUM_HPP

#include <cstdlib>
#include <thread>
#include "common.hpp"
#include "hooks/hooker.hpp"

#if defined(__linux__) || defined(__APPLE__)
    // Define Windows-only calling convention to default to nothing on *nix
    #define __fastcall
    #define __stdcall
    #define __cdecl
#endif

namespace Anium {

    int Init();

    int Destroy();

}

#endif //ANIUM_ANIUM_HPP

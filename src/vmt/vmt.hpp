#ifndef ANIUM_VMT_HPP
#define ANIUM_VMT_HPP

#include "vmthook.hpp"
#include "impl/framestagenotify.hpp"
#include "../hooks/pattern.hpp"
#include "../interfaces/interfaces.hpp"

extern VMTHook* clientVMT;

namespace VMT {

    void Init();

    void Grab();

    void Release();

}

#endif //ANIUM_VMT_HPP

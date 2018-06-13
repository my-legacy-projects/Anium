#ifndef ANIUM_VMT_HPP
#define ANIUM_VMT_HPP

#include "vmthook.hpp"
#include "impl/framestagenotify.hpp"
#include "impl/paint.hpp"
#include "../hooks/pattern.hpp"
#include "../interfaces/iface.hpp"

extern VMTHook* clientVMT;
extern VMTHook* engineVGuiVMT;

namespace VMT {

    void Init();

    void Release();

}

#endif //ANIUM_VMT_HPP

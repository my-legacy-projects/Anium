#ifndef ANIUM_IFACE_HPP
#define ANIUM_IFACE_HPP

#include "../sdk/interfaces/IBaseClientDLL.hpp"
#include "../sdk/interfaces/ICvar.hpp"
#include "../sdk/interfaces/IEngineVGui.hpp"
#include "../sdk/interfaces/ISurface.hpp"
#include "interface.hpp"

namespace IFace {

    static Interface<IBaseClientDLL> client;
    static Interface<ICvar> cvar;
    static Interface<IEngineVGui> engineVGui;
    static Interface<ISurface> surface;

}

#endif  // ANIUM_IFACE_HPP

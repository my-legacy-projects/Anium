#ifndef ANIUM_INTERFACES_HPP
#define ANIUM_INTERFACES_HPP

#include "../sdk/interfaces/IBaseClientDLL.hpp"
#include "../sdk/interfaces/ICvar.hpp"
#include "../sdk/interfaces/IEngineVGui.hpp"
#include "../sdk/interfaces/ISurface.hpp"
#include "sourcelib.hpp"

extern SourceLib clientLib;
extern SourceLib vStdLib;
extern SourceLib materialSystemLib;
extern SourceLib engineLib;
extern SourceLib vGuiMatSurface;

extern IBaseClientDLL* client;
extern ICvar* cvar;
extern IEngineVGui* engineVGui;
extern ISurface* surface;

namespace Interfaces {

    void Find();

}

#endif //ANIUM_INTERFACES_HPP

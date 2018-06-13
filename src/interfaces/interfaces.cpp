#include "interfaces.hpp"

void Interfaces::Init() {
    // Cross-platform shit
    IFace::client.AssignFromInterface(Libraries::client, "VClient", 18);
    IFace::engineVGui.AssignFromInterface(Libraries::engine, "VEngineVGui", 1);
    IFace::surface.AssignFromInterface(Libraries::vGuiMatSurface, "VGUI_Surface", 31);

    // Thanks Valve
    #if defined(_WIN32)
        IFace::cvar.AssignFromInterface(Libraries::vStdLib, "VEngineCvar", 7);
    #elif defined(__APPLE__) || defined(__linux__)
        IFace::cvar.AssignFromInterface(Libraries::materialSystem, "VEngineCvar", 7);
    #endif
}

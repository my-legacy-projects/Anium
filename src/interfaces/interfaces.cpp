#include "interfaces.hpp"

SourceLib clientLib = SourceLib("./csgo/bin/client.dll",
                                "./csgo/bin/osx64/client.dylib",
                                "./csgo/bin/linux64/client_client.so");
SourceLib vStdLib = SourceLib("./bin/vstdlib.dll",
                              "./bin/osx64/libvstdlib.dylib",
                              "./bin/linux64/libvstdlib.so");
SourceLib materialSystemLib = SourceLib("./bin/materialsystem.dll",
                                        "./bin/osx64/materialsystem.dylib",
                                        "./bin/linux64/materialsystem_client.so");

IBaseClientDLL* client = nullptr;
ICvar* cvar = nullptr;

void Interfaces::Find() {
    // Cross-platform shit
    client = clientLib.GrabInterface<IBaseClientDLL>("VClient018");

    // Thanks Valve
    #if defined(_WIN32)
        cvar = vStdLib.GrabInterface<ICvar>("VEngineCvar007");
    #elif defined(__APPLE__) || defined(__linux__)
        cvar = materialSystemLib.GrabInterface<ICvar>("VEngineCvar007");
    #endif
}

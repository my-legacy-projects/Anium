#include "interfaces.hpp"

SourceLib clientLib = SourceLib("./csgo/bin/client.dll",
                                "./csgo/bin/osx64/client.dylib",
                                "./csgo/bin/linux64/client_client.so");

IBaseClientDLL* client = nullptr;

void Interfaces::Find() {
    client = clientLib.GrabInterface<IBaseClientDLL>("VClient018");
}

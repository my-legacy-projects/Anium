#ifndef ANIUM_LIBRARIES_HPP
#define ANIUM_LIBRARIES_HPP

#include "sourcelib.hpp"

namespace Libraries {

    static SourceLib client = SourceLib("./csgo/bin/client.dll",
                                        "./csgo/bin/osx64/client.dylib",
                                        "csgo/bin/linux64/client_client.so");

    static SourceLib vStdLib = SourceLib("./bin/vstdlib.dll",
                                         "./bin/osx64/libvstdlib.dylib",
                                         "./bin/linux64/libvstdlib.so");

    static SourceLib materialSystem = SourceLib("./bin/materialsystem.dll",
                                                "./bin/osx64/materialsystem.dylib",
                                                "./bin/linux64/materialsystem_client.so");

    static SourceLib engine = SourceLib("./bin/engine.dll",
                                        "./bin/osx64/engine.dylib",
                                        "./bin/linux64/engine_client.so");

    static SourceLib vGuiMatSurface = SourceLib("./bin/vguimatsurface.dll",
                                                "./bin/osx64/vguimatsurface.dylib",
                                                "./bin/linux64/vguimatsurface_client.so");

}

#endif  // ANIUM_LIBRARIES_HPP

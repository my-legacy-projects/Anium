#include "anium.hpp"

#if defined(__unix__)
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

int __attribute__((constructor)) Anium::Init() {
    std::thread aniumThread([&]() -> void {
        std::cout << "Welcome to Anium!" << std::endl;
    });
    aniumThread.detach();

    return EXIT_SUCCESS;
}

int __attribute__((destructor)) Anium::Destroy() {

    return EXIT_SUCCESS;
}

#ifdef ANIUM_WINDOWS

__declspec(dllexport) BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved) {
    switch (reason) {
        case DLL_PROCESS_ATTACH:
            CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE) Anium::Init, module, 0, nullptr);
        case DLL_PROCESS_DETACH:
            if (reserved == nullptr) {
                return (bool) Anium::Destroy();
            }
    }

    return true;
}

#endif

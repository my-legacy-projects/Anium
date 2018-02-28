#include "anium.hpp"

int __attribute__((constructor)) Anium::Init() {
    std::thread aniumThread([&]() -> void {
        Interfaces::Find(); // This method will block and wait until it finds all the interfaces.

        std::cout << "Welcome to Anium." << std::endl;
    });
    aniumThread.detach();

    return EXIT_SUCCESS;
}

int __attribute__((destructor)) Anium::Destroy() {

    return EXIT_SUCCESS;
}

#if defined(ANIUM_WINDOWS)

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

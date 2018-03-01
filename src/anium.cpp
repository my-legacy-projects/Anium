#include "anium.hpp"

int __attribute__((constructor)) Anium::Init() {
    std::thread aniumThread([&]() -> void {
        Interfaces::Find(); // This method will block and wait until it finds all the interfaces.

        Hooker::Init(); // Sig scanning

        Hooker::Hook(); // VMT Hooking

        // Seed random number generator with current time
        srand((unsigned int) time(nullptr));

        std::cout << "Welcome to Anium." << std::endl;
    });
    aniumThread.detach();

    return EXIT_SUCCESS;
}

int __attribute__((destructor)) Anium::Destroy() {
    Hooker::Restore();

    std::cout << "Thank you and have a nice day." << std::endl;

    return EXIT_SUCCESS;
}

#if defined(_WIN32)

__declspec(dllexport) BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved) {
    switch (reason) {
        case DLL_PROCESS_ATTACH:
            CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE) Anium::Init, module, 0, nullptr);
        case DLL_PROCESS_DETACH:
            if (reserved == nullptr) {
                return !((bool) Anium::Destroy());
            }
    }

    return true;
}

#endif

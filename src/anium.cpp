#include "anium.hpp"

// Global logger should be initialized with highest priority so we can start logging directly and early
Logger __attribute__((init_priority(101))) logger("Anium");

int Anium::Init(HMODULE self) {
    std::thread aniumThread([&]() -> void {
        Interfaces::Find(); // This method will block and wait until it finds all the interfaces.

        Hooker::Init(); // Sig scanning

        Hooker::Hook(); // VMT Hooking

        // Seed random number generator with current time
        srand((unsigned int) time(nullptr));

        logger.log("Welcome to Anium.");
    });
    aniumThread.detach();

    return EXIT_SUCCESS;
}

int Anium::Destroy(HMODULE self) {
    Hooker::Restore();

    logger.log("Thank you and have a nice day.");

    #if defined(_WIN32)
        FreeLibraryAndExitThread(self, EXIT_SUCCESS);
    #elif defined(__APPLE__) || defined(__linux__)
        if (self == nullptr)
            return EXIT_SUCCESS;

        dlclose(self);
        dlclose(self);
    #endif

    return EXIT_SUCCESS;
}

#if defined(_WIN32)

bool __stdcall DllMain(HMODULE module, DWORD reason, LPVOID reserved) {
    switch (reason) {
        case DLL_PROCESS_ATTACH:
            CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE) Anium::Init, module, 0, nullptr);
            break;
        case DLL_PROCESS_DETACH:
            if (reserved == nullptr) {
                return !((bool) Anium::Destroy(module));
            }
            break;
    }

    return true;
}

#elif defined(__APPLE__) || defined(__linux__)

int __attribute__((constructor)) Init() {
    return Anium::Init(dlopen(nullptr, RTLD_NOW | RTLD_NOLOAD));
}

int __attribute__((destructor)) Destroy() {
    return Anium::Destroy(dlopen(nullptr, RTLD_NOW | RTLD_NOLOAD));
}

#endif

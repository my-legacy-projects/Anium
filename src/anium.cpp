#include "anium.hpp"

#if defined(_WIN32)
    Logger logger("Anium");
    HMODULE aniumModule = nullptr;
#elif defined(__APPLE__) || defined(__linux__)
    // Global logger should be initialized with highest priority so we can start logging directly and early
    Logger __attribute__((init_priority(101))) logger("Anium");
#endif

int Anium::Init(HMODULE self) {
    std::thread aniumThread([&]() -> void {
        #if defined(_WIN32)
            aniumModule = self; // May be nullptr but we check for that in Exit()
        #endif

        Interfaces::Find(); // This method will block and wait until it finds all the interfaces.

        VMT::Init();

        EventBus::Init();

        // Seed random number generator with current time
        srand((unsigned int) time(nullptr));

        logger.log("Welcome to Anium.");
    });
    aniumThread.detach();

    return EXIT_SUCCESS;
}

int Anium::Destroy() {
    VMT::Release();

    logger.log("Thank you and have a nice day.");

    return EXIT_SUCCESS;
}

// The platform specific calls will invoke Anium::Destroy using their platform native destructors.
// If invoking the platform native destructor isn't possible for some reason, we're calling Anium::Destroy() directly.
// This won't remove us from the loaded libs but will unload in-game stuff, so that'll hopefully be fine.
void Anium::Exit() {
    #if defined(_WIN32)
        if (aniumModule == nullptr) {
            Anium::Destroy();
            return;
        }

        FreeLibraryAndExitThread(aniumModule, EXIT_SUCCESS);
    #elif defined(__APPLE__) || defined(__linux__)
        void* self = dlopen(nullptr, RTLD_NOW | RTLD_NOLOAD);

        if (self == nullptr) {
            Anium::Destroy();
            return;
        }

        dlclose(self);
        dlclose(self);
        dlclose(self);
    #endif
}

#if defined(_WIN32)

bool __stdcall DllMain(HMODULE module, DWORD reason, LPVOID reserved) {
    switch (reason) {
        case DLL_PROCESS_ATTACH:
            return CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE) Anium::Init, module, 0, nullptr) != nullptr;
        case DLL_PROCESS_DETACH:
            if (reserved == nullptr) {
                return !((bool) Anium::Destroy());
            }
            break;
    }

    return true; // If other reason's are called, just return true ¯\_(ツ)_/¯
}

#elif defined(__APPLE__) || defined(__linux__)

int __attribute__((constructor)) Init() {
    return Anium::Init(dlopen(nullptr, RTLD_NOW | RTLD_NOLOAD));
}

int __attribute__((destructor)) Destroy() {
    return Anium::Destroy();
}

#endif

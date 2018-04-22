#include "anium.hpp"

#if defined(_WIN32)
    Logger logger("Anium");
    void* aniumModule = nullptr;
    bool aniumActive = false;
#elif defined(__APPLE__) || defined(__linux__)
    // Global logger should be initialized with highest priority so we can start logging directly and early
    Logger __attribute__((init_priority(101))) logger("Anium");
#endif

int Anium::Init(void* self) {
    std::thread aniumThread([&]() -> void {
        #if defined(_WIN32)
            aniumModule = self; // May be nullptr but we check for that in Anium::Exit()
            aniumActive = true;
        #elif defined(__APPLE__) || defined(__linux__)
            Dl_info dlInfo;

            if (dladdr((void*) Anium::Init, &dlInfo) != 0) {
                logger.log("Found ourselves in %s, assigning module handle.", dlInfo.dli_fname);
            } else {
                logger.log("Unable to found ourselves. No module handle assigned.");
            }
        #endif

        Interfaces::Find(); // This method will block and wait until it finds all the interfaces.

        VMT::Init();

        EventBus::Init();

        NetVar::InitAll();

        Hooker::Init();

        srand((unsigned int) time(nullptr)); // Seed random number generator with current time

        logger.log("Welcome to Anium on %s.", Platforms::GetPlatformName().c_str());
        logger.log("Module has been created on %s at %s.", __DATE__, __TIME__);
    });
    aniumThread.detach();

    #if defined(_WIN32)
        while (aniumActive)
            std::this_thread::yield();

        FreeLibraryAndExitThread((HMODULE) aniumModule, EXIT_SUCCESS);
    #elif defined(__APPLE__) || defined(__linux__)
        return EXIT_SUCCESS;
    #endif
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
        aniumActive = false;

        if (aniumModule == nullptr) {
            Anium::Destroy();
            return;
        }

        FreeLibraryAndExitThread((HMODULE) aniumModule, EXIT_SUCCESS);
    #elif defined(__APPLE__) || defined(__linux__)
        Dl_info dlInfo;

        if (dladdr((void*) Anium::Init, &dlInfo) == 0) {
            Anium::Destroy();
            return;
        }

        void* handle = dlopen(dlInfo.dli_fname, RTLD_NOW | RTLD_NOLOAD);

        if (handle == nullptr) {
            // For whatever reason, we found ourselves but couldn't open ourselves
            // How does this even happen, who's fault is this? Can we even recover from this?
            // Somebody save this program. Somebody save me from my depression.
            Anium::Destroy();
            return;
        }

        logger.log("Anium has been loaded as %s.", dlInfo.dli_fname);

        dlclose(handle);
        dlclose(handle);
        dlclose(handle);

        // This code won't be executed if unloading was successful
        logger.log("Anium was unable to unload itself, unloading forcefully.");
        logger.log("Error: %s", dlerror());

        Anium::Destroy();
    #endif
}

#if defined(_WIN32)

bool __stdcall DllMain(void* module, unsigned long reason, void* reserved) {
    switch (reason) {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls((HMODULE) module);
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
    return Anium::Init();
}

int __attribute__((destructor)) Destroy() {
    return Anium::Destroy();
}

#endif

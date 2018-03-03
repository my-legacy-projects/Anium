#ifndef ANIUM_SOURCELIB_HPP
#define ANIUM_SOURCELIB_HPP

#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <chrono>

#if defined(_WIN32)
    #include <Windows.h>
    #include <Psapi.h>
#elif defined(__APPLE__)
    #include <sys/types.h>
    #include <mach/error.h>
    #include <mach/vm_types.h>
    #include <mach-o/dyld.h>
    #include <mach-o/getsect.h>
    #include <mach/mach.h>
    #include <sys/stat.h>
#elif defined(__linux__)
    #include <link.h>
#endif

#if defined(__APPLE__) || defined(__linux__)
    #include <dlfcn.h>
#endif

typedef void* (*InstantiateInterfaceFn)();

struct InterfaceReg {

    InstantiateInterfaceFn m_CreateFn;
    const char* m_pName;
    InterfaceReg* m_pNext;

};

class SourceLib {
private:
    std::string name;
    std::string module;
    InterfaceReg* reg = nullptr;

    uintptr_t address = 0;
    size_t size = 0;

public:
    SourceLib(std::string _windows, std::string _mac, std::string _linux) {
        #if defined(_WIN32)
            this->name = std::move(_windows);
        #elif defined(__APPLE__)
            this->name = std::move(_mac);
        #elif defined(__linux__)
            this->name = std::move(_linux);
        #endif

        if (this->name.empty())
            return;

        // Parse the full path of the library into the last one, e.g "client.dll", "client.dylib", "client_client.so"
        this->module = this->name.substr(this->name.find_last_of('/') + 1);

        Init(); // Try to load the reg now - deal with it later if it doesn't work yet
    }

    std::string GetLibraryName() {
        return this->name;
    }

    bool Init() {
        #if defined(__APPLE__) || defined(__linux__)
            void* lib = dlopen(GetLibraryName().c_str(), RTLD_NOLOAD | RTLD_NOW | RTLD_LOCAL);

            if (lib == nullptr)
                return false;

            void* reg = dlsym(lib, "s_pInterfaceRegs");

            dlclose(lib);

            if (reg == nullptr)
                return false;

            this->reg = *reinterpret_cast<InterfaceReg**>(reg);
        #endif

        #if defined(_WIN32)
            // Credit: https://github.com/emskye96/chameleon-ng/blob/master/src/FindPattern.hpp#L44
            MODULEINFO info = { 0 };

            GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(this->module.c_str()), &info, sizeof(MODULEINFO));

            this->address = (uintptr_t) info.lpBaseOfDll;
            this->size = (size_t) info.SizeOfImage;
        #elif defined(__APPLE__)
            // Credit: https://github.com/scen/libembryo/blob/master/src/mem/module.cpp#L15
            for (int i = 0; i < _dyld_image_count(); i++) {
                mach_header* header = (mach_header*) _dyld_get_image_header(i);

                std::string name(_dyld_get_image_name(i));
                if (name.empty())
                    continue;

                if (name.find(this->module) != std::string::npos) {
                    struct stat sb;
                    stat(name.c_str(), &sb);

                    this->address = (uintptr_t) header;
                    this->size = (size_t) sb.st_size;
                }
            }
        #elif defined(__linux__)
            // Credit: https://github.com/aixxe/cstrike-basehook-linux/blob/master/src/Utilities/Linker.cpp#L20
            dl_iterate_phdr([](struct dl_phdr_info* info, size_t, void* self) {
                std::string name = std::string(info->dlpi_name);

                if (name.find(((SourceLib*) self)->module) != std::string::npos) {
                    ((SourceLib*) self)->address = info->dlpi_addr + info->dlpi_phdr[0].p_vaddr;
                    ((SourceLib*) self)->size = info->dlpi_phdr[0].p_memsz;
                }

                return 0;
            }, (void*) this);
        #endif

        return this->address != 0 && this->size != 0;
    }

    template <typename T>
    T* GrabInterface(std::string _windows, std::string _mac, std::string _linux) {
        #if defined(_WIN32)
            std::string target = std::move(_windows);
        #elif defined(__APPLE__)
            std::string target = std::move(_mac);
        #elif defined(__linux__)
            std::string target = std::move(_linux);
        #endif

        if (this->reg == nullptr) {
            // The reg is null - let's try to get it
            if (!Init())
                std::this_thread::sleep_for(std::chrono::seconds(2));

            // If it looks stupid but it isn't stupid, it ain't stupid
            return this->GrabInterface<T>(target, target, target);
        }

        #if defined(_WIN32)
            typedef void* (*CreateInterfaceFn) (const char*, int*);
            CreateInterfaceFn func = (CreateInterfaceFn) GetProcAddress(
                    GetModuleHandleA(this->module.c_str(), "CreateInterface")
            );

            return reinterpret_cast<T*>(CreateInterface(this->target.c_str(), nullptr));
        #elif defined(__APPLE__) || defined(__linux__)
            InterfaceReg* current;

            for (current = this->reg; current; current = current->m_pNext) {
                if (strcmp(current->m_pName, target.c_str()) == 0 &&
                    strlen(current->m_pName) - 3 == strlen(target.c_str())) {
                    return reinterpret_cast<T*>(current->m_CreateFn);
                }
            }
        #endif

        return nullptr;
    }

    uintptr_t GetAddress() {
        return this->address;
    }

    size_t GetSize() {
        return this->size;
    }

};

#endif //ANIUM_SOURCELIB_HPP

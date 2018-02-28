#ifndef ANIUM_SOURCELIB_HPP
#define ANIUM_SOURCELIB_HPP

#include <dlfcn.h> // dlfcn is also available for Windows, just needs to be installed
#include <cstring>
#include <cstdlib>
#include "../common.hpp"

#include <link.h> // TODO: Make this Windows compatible

typedef void* (*InstantiateInterfaceFn)();

struct InterfaceReg {

    InstantiateInterfaceFn m_CreateFn;
    const char* m_pName;
    InterfaceReg* m_pNext;

};

class SourceLib {
private:
    std::string name;
    InterfaceReg* reg = nullptr;

    uintptr_t address = 0;
    size_t size = 0;

public:
    SourceLib(std::string _windows, std::string _mac, std::string _linux) {
        #if defined(ANIUM_WINDOWS)
            this->name = std::move(_windows);
        #elif defined(ANIUM_MAC)
            this->name = std::move(_mac);
        #elif defined(ANIUM_LINUX)
            this->name = std::move(_linux);
        #endif

        Init(); // Try to load the reg now - deal with it later if it doesn't work yet
    }

    std::string GetLibraryName() {
        return name;
    }

    bool Init() {
        void* lib = dlopen(GetLibraryName().c_str(), RTLD_NOLOAD | RTLD_NOW | RTLD_LOCAL);

        if (lib == nullptr)
            return false;

        void* reg = dlsym(lib, "s_pInterfaceRegs");

        dlclose(lib);

        if (reg == nullptr)
            return false;

        this->reg = *reinterpret_cast<InterfaceReg**>(reg);

        std::tuple<std::string, uintptr_t, size_t> args = {};

        // Credit: https://github.com/aixxe/cstrike-basehook-linux/blob/master/src/Utilities/Linker.cpp#L20
        // TODO: Find a way to make this more performing (we're looping through every library with every SourceLib)
        dl_iterate_phdr([](struct dl_phdr_info* info, size_t, void* self) {
            std::string module = ((SourceLib*) self)->name.substr(((SourceLib*) self)->name.find_last_of("/") + 1);

            if (strcmp(info->dlpi_name, module.c_str())) {
                ((SourceLib*) self)->address = info->dlpi_addr + info->dlpi_phdr[0].p_vaddr;
                ((SourceLib*) self)->size = info->dlpi_phdr[0].p_memsz;
            }

            return 0;
        }, (void*) this);

        // [DEBUG]
        std::cout << GetLibraryName() << " - Address: " << this->address << " / Size: " << this->size << std::endl;

        return this->address != 0 && this->size != 0;
    }

    template <typename T>
    T* GrabInterface(const std::string& target) {
        if (this->reg == nullptr) {
            // The reg is null - let's try to get it
            if (!Init())
                std::this_thread::sleep_for(std::chrono::seconds(2));

            return this->GrabInterface<T>(target);
        }

        InterfaceReg* current;

        for (current = this->reg; current; current = current->m_pNext) {
            if (strcmp(current->m_pName, target.c_str()) == 0 &&
                strlen(current->m_pName) - 3 == strlen(target.c_str())) {
                return reinterpret_cast<T*>(current->m_CreateFn);
            }
        }

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

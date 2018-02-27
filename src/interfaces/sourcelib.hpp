#ifndef ANIUM_SOURCELIB_HPP
#define ANIUM_SOURCELIB_HPP

#include <dlfcn.h> // dlfcn is also available for Windows, just needs to be installed
#include <cstring>
#include <cstdlib>
#include <thread>

typedef void* (*InstantiateInterfaceFn)();

struct InterfaceReg {

    InstantiateInterfaceFn m_CreateFn;
    const char* m_pName;
    InterfaceReg* m_pNext;

};

class SourceLib {
private:
    std::string windowsName;
    std::string macName;
    std::string linuxName;
    InterfaceReg* reg = nullptr;

public:
    SourceLib(std::string windows, std::string mac, std::string _linux) {
        this->windowsName = std::move(windows);
        this->macName = std::move(mac);
        this->linuxName = std::move(_linux);
        Init(); // Try to load the reg now - deal with it later if it doesn't work yet
    }

    std::string GetLibraryName() {
        #if defined(ANIUM_WINDOWS)
            return this->windowsName;
        #elif defined(ANIUM_MAC)
            return this->macName;
        #elif defined(ANIUM_LINUX)
            return this->linuxName;
        #endif

        return "";
    }

    bool Init() {
        void* lib = dlopen(GetLibraryName().c_str(), RTLD_NOLOAD | RTLD_NOW | RTLD_LOCAL);

        if (lib == nullptr)
            return false;

        void* reg = dlsym(lib, "s_pInterfaceRegs");

        dlclose(lib);

        if (reg == nullptr) {
            return false;
        }

        this->reg = *reinterpret_cast<InterfaceReg**>(reg);

        return true;
    }

    template <typename Interface>
    Interface* GrabInterface(const std::string& target) {
        if (this->reg == nullptr) {
            // The reg is null - let's try to get it
            if (!Init())
                std::this_thread::sleep_for(std::chrono::seconds(2));

            return this->GrabInterface<Interface>(target);
        }

        InterfaceReg* current;

        for (current = this->reg; current; current = current->m_pNext) {
            if (strcmp(current->m_pName, target.c_str()) == 0 &&
                strlen(current->m_pName) - 3 == strlen(target.c_str())) {
                return reinterpret_cast<Interface*>(current->m_CreateFn);
            }
        }

        return nullptr;
    }

};

#endif //ANIUM_SOURCELIB_HPP

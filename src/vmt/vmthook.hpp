#ifndef ANIUM_VMTHOOK_HPP
#define ANIUM_VMTHOOK_HPP

#include <cassert>
#include <cstring>
#include <memory>
#include <vector>
#include "../utils/logging.hpp"

class VMTHook {
private:
    uintptr_t** instance;
    size_t count = 0;

    uintptr_t* original;
    std::unique_ptr<uintptr_t[]> replacement;

    std::vector<std::pair<int, void*>> hookedFuncs;

public:
    VMTHook(void* instance) {
        this->instance = (uintptr_t**) instance;

        while ((*this->instance)[this->count]) {
            this->count++;
        }

        logger.log("Found %i virtual methods in %p.", this->count, &this->instance);

        this->original = *this->instance;
        this->replacement = std::make_unique<uintptr_t[]>(this->count);

        memcpy(this->replacement.get(), this->original, this->count * sizeof(uintptr_t));

        *this->instance = this->replacement.get();
    }

    ~VMTHook() {
        *this->instance = this->original;
        this->hookedFuncs.clear();
    }

    void Hook(int _windows, int _mac, int _linux, void* replacement) {
        #if defined(_WIN32)
            int index = _windows;
        #elif defined(__APPLE__)
            int index = _mac;
        #elif defined(__linux__)
            int index = _linux;
        #endif

        this->replacement[index] = reinterpret_cast<uintptr_t>(replacement);
        this->hookedFuncs.emplace_back(std::pair<int, void*>(index, replacement));

        logger.log("Hooked #%i in %p to %p.", index, &this->instance, &replacement);
    }

    void Release(int _windows, int _mac, int _linux) {
        #if defined(_WIN32)
            int index = _windows;
        #elif defined(__APPLE__)
            int index = _mac;
        #elif defined(__linux__)
            int index = _linux;
        #endif

        this->replacement[index] = this->original[index];

        for (int i = 0; i < (int) this->hookedFuncs.size(); i++) {
            std::pair<int, void*> pair = this->hookedFuncs[i];

            if (pair.first == index) {
                this->hookedFuncs.erase(this->hookedFuncs.begin() + i);
            }
        }

        logger.log("Released hook #%i in %p.", index, &this->instance);
    }

    void ReleaseAll() {
        for (std::pair<int, void*> pair : this->hookedFuncs) {
            Release(pair.first, pair.first, pair.first);
        }
    }

    template <typename T>
    T GetOriginal(int _windows, int _mac, int _linux) {
        #if defined(_WIN32)
            int index = _windows;
        #elif defined(__APPLE__)
            int index = _mac;
        #elif defined(__linux__)
            int index = _linux;
        #endif

        return reinterpret_cast<T>(this->original[index]);
    }

    size_t GetAmount() {
        return this->count;
    }

};

#endif //ANIUM_VMTHOOK_HPP

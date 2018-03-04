#ifndef ANIUM_VFUNC_HPP
#define ANIUM_VFUNC_HPP

#include <cstddef>

class VFunc {
private:
    void* base;
    size_t index;
    size_t offset;

public:
    VFunc(void* base, size_t _windows, size_t _mac, size_t _linux, size_t winOffset = 0, size_t macOffset = 0, size_t linuxOffset = 0) {
        #if defined(_WIN32)
            this->index = _windows;
            this->offset = winOffset;
        #elif defined(__APPLE__)
            this->index = _mac;
            this->offset = macOffset;
        #elif defined(__linux__)
            this->index = _linux;
            this->offset = linuxOffset;
        #endif

        this->base = base;
    }

    template <typename T>
    T GetFunction() {
        return (*(T**) this->base)[this->index];
    }

};

#endif

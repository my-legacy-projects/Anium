#ifndef ANIUM_PLATFORMUTILS_HPP
#define ANIUM_PLATFORMUTILS_HPP

#include <string>

#if defined(__APPLE__) || defined(__linux__)
    #include <sys/utsname.h>
#endif

namespace PlatformUtils {

    std::string GetPlatformName();

    // This may come in handy at a later point. Credit to Onee Chan for this smart boy way.
    template <typename T>
    constexpr T Platform(T _windows, T _mac, T _linux);

}

#endif //ANIUM_PLATFORMUTILS_HPP

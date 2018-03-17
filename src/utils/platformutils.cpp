#include "platformutils.hpp"

std::string PlatformUtils::GetPlatformName() {
    #if defined(_WIN32)
        // I'd have use GetVersion and GetVersionEx here but that has sadly been deprecated in Windows 8+.
        // Anium wants to support all versions ranging from Windows 7 up to Windows 10.
        // The replacement function VerifyVersionInfo does not fill in the same role.
        // TODO: Requires a workaround in the near future
        return "Windows";
    #elif defined(__APPLE__) || defined(__linux__)
        struct utsname uts;
        uname(&uts);
        return std::string(uts.sysname);
    #endif
}

template <typename T>
constexpr T PlatformUtils::Platform(T _windows, T _mac, T _linux) {
    #if defined(_WIN32)
        return _windows;
    #elif defined(__APPLE__)
        return _mac;
    #elif defined(__linux__)
        return _linux;
    #endif
}

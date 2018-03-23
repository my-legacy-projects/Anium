#include "platforms.hpp"

std::string Platforms::GetPlatformName() {
    #if defined(_WIN32)
        // MSDN warning: GetVersionEx may be altered or unavailable for releases after Windows 8.1
        // The replacement, IsWindowsVersionOrGreater, don't fill into our purpose
        // For now, this is only _deprecated_ and not fully removed.
        // If this gets removed in the future, ask Windows why it is so backwards compatible but not in this case

        OSVERSIONINFOEX info;
        ZeroMemory(&info, sizeof(OSVERSIONINFOEX));
        info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

        GetVersionEx((LPOSVERSIONINFO) &info);

        return "Windows " + std::string(info.dwMajorVersion) + "." + std::string(info.dwMinorVersion);
    #elif defined(__APPLE__) || defined(__linux__)
        struct utsname uts;
        uname(&uts);
        return std::string(uts.sysname) + " " + std::string(uts.version);
    #endif
}

template <typename T>
constexpr T Platforms::Platform(T _windows, T _mac, T _linux) {
    #if defined(_WIN32)
        return _windows;
    #elif defined(__APPLE__)
        return _mac;
    #elif defined(__linux__)
        return _linux;
    #endif
}

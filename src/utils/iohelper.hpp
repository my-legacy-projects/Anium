#ifndef ANIUM_IOHELPER_HPP
#define ANIUM_IOHELPER_HPP

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>

#if defined(_WIN32)
    #define WIN32_LEAN_AND_MEAN
    #include <Windows.h>
#endif

#if defined(__APPLE__) || defined(__linux__)
    #include <dlfcn.h>
    #include <pwd.h>
    #include <sys/stat.h>
    #include <unistd.h>
#endif

#if defined(__linux__)
    #include <link.h>

    // "bfd" is a internal library and shouldn't be used by other projects
    // Well the maintainers can suck my ass because I'll use it anyways
    // It'll error without defines below so let's define them
    #define PACKAGE
    #define PACKAGE_VERSION
    #include <bfd.h>
#endif

#if defined(__APPLE__)
    #include <dirent.h>
    #include <mach/error.h>
    #include <sys/errno.h>
    #include <sys/syslimits.h>

    // AppleClang doesn't have filesystem at all?
    //#include <boost/filesystem>
    //namespace fs = boost::filesystem;
#else
    #if defined(__has_include)
        #if __has_include(<filesystem>)
            #include <filesystem>

            #if defined(_WIN32)
                // Workaround for Windows: https://docs.microsoft.com/en-us/cpp/standard-library/filesystem
                namespace fs = std::experimental::filesystem::v1;
            #else
                namespace fs = std::filesystem;
            #endif
        #else
            #include <experimental/filesystem>
            namespace fs = std::experimental::filesystem;
        #endif
    #else
        // Compiler doesn't support C++17 __has_include so we can expect filesystem is in experimental state
        #include <experimental/filesystem>
        namespace fs = std::experimental::filesystem;
    #endif
#endif

namespace io {

    // File IO

    bool Create(std::string path);

    bool Delete(std::string path);

    bool Exists(std::string path);

    char GetPathSeparator();

    std::string GetUserDirectory();

    std::string GetTempDirectory();

    std::string GetWorkingDirectory();

    // Gets the directory where Anium will save custom files
    std::string GetAniumDirectory();

    // Converts "/" to cross-platform file separators
    void Convert(std::string& path);

    // Libraries IO

    bool FindLibrary(std::string path, std::string file, char* out);

    bool FindLibrary(uintptr_t address, char* out);

}

#endif //ANIUM_IOHELPER_HPP

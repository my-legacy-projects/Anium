#ifndef ANIUM_IOHELPER_HPP
#define ANIUM_IOHELPER_HPP

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>

#if defined(__APPLE__) || defined(__linux__)
    #include <pwd.h>
    #include <sys/stat.h>
    #include <unistd.h>
#endif

#if defined(__APPLE__)
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

}

#endif //ANIUM_IOHELPER_HPP

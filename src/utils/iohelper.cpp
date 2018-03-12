#include "iohelper.hpp"

bool io::Create(std::string path) {
    io::Convert(path);

    if (io::Exists(path))
        return true;

    #if defined(__APPLE__)
        return mkdir(path.c_str(), S_IRWXU) == 0;
    #else
        return fs::create_directories(fs::u8path(path));
    #endif
}

bool io::Delete(std::string path) {
    io::Convert(path);

    if (!io::Exists(path))
        return true;

    #if defined(__APPLE__)
        return remove(path.c_str()) == 0;
    #else
        return fs::remove(fs::u8path(path));
    #endif
}

bool io::Exists(std::string path) {
    io::Convert(path);

    #if defined(__APPLE__)
        struct stat buffer;
        return stat(path.c_str(), &buffer) == 0;
    #else
        return fs::exists(fs::u8path(path));
    #endif
}

char io::GetPathSeparator() {
    #if defined(__APPLE__)
        return '/';
    #else
        return fs::path::preferred_separator;
    #endif
}

std::string io::GetUserDirectory() {
    #if defined(_WIN32)
        const char* dir = getenv("USERPROFILE");
        if (dir == nullptr)
            return strcat(getenv("HOMEDRIVE"), getenv("HOMEPATH"));

        return dir;
    #else
        const char* dir = getenv("HOME");
        if (dir == nullptr) {
            passwd* pwd = getpwuid(getuid());
            if (pwd == nullptr)
                return io::GetWorkingDirectory();

            return pwd->pw_dir;
        }

        return dir;
    #endif
}

std::string io::GetTempDirectory() {
    #if defined(__APPLE__)
        return "/tmp/";
    #else
        return fs::temp_directory_path().u8string();
    #endif
}

std::string io::GetWorkingDirectory() {
    #if !defined(__APPLE__)
        char buffer[PATH_MAX];
        getcwd(buffer, sizeof(buffer));

        if (buffer == nullptr)
            return "./";

        return std::string(buffer);
    #else
        return fs::current_path().u8string();
    #endif

}

std::string io::GetAniumDirectory() {
    std::string path(io::GetUserDirectory() + io::GetPathSeparator() + "Anium");
    if (!io::Create(path))
        return io::GetWorkingDirectory();

    return path;
}

void io::Convert(std::string& path) {
    std::replace(path.begin(), path.end(), '/', io::GetPathSeparator());
}

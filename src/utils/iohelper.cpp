#include "iohelper.hpp"

bool io::Create(std::string path) {
    io::Convert(path);

    if (io::Exists(path))
        return true;

    #if defined(__APPLE__)
        // This function is expected to create directories recursively.
        // filesystem::create_directories does that, but macOS sadly doesn't have that :(
        // Credit to https://gist.github.com/JonathonReinhart/8c0d90191c38af2dcadb102c4e202950
        char buffer[PATH_MAX];

        strcpy(buffer, path.c_str());

        for (char* c = buffer + 1; c != nullptr; c++) {
            if (*c == io::GetPathSeparator()) {
                if (mkdir(path.c_str(), S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) != 0) {
                    if (errno != EEXIST)
                        return false;
                }
            }
        }

        return mkdir(path.c_str(), S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) == 0;
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
        struct stat sb;
        return stat(path.c_str(), &sb) == 0;
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
        if (dir != nullptr)
            return std::string(getenv("HOMEDRIVE")) + io::GetPathSeparator() + std::string(getenv("HOMEPATH"));

        return dir;
    #else
        const char* dir = getenv("HOME");
        if (dir == nullptr) {
            passwd* pwd = getpwuid(getuid());
            if (pwd == nullptr || pwd->pw_dir == nullptr)
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
    #if defined(__APPLE__)
        char buffer[PATH_MAX];
        char* result = getcwd(buffer, sizeof(buffer));

        if (result == nullptr)
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

bool io::FindLibrary(std::string path, std::string file, char* out) {
    io::Convert(path);
    io::Convert(file);
    std::memset(out, 0, strlen(out));

    #if defined(__APPLE__)
        DIR* dir = opendir(path.c_str());
        struct dirent* entity;

        if (dir != nullptr) {
            while ((entity = readdir(dir)) != nullptr) {
                if (std::strcmp(entity->d_name, file.c_str()) == 0) {
                    // macOS has the same problem as Linux (see description below)
                    // I haven't found out a smart way to check if the dylib is 64-bit
                    // yet so we'll push this back for later. TODO

                    std::sprintf(out, "%s", entity->d_name);
                    break;
                }
            }

            closedir(dir);
        }
    #else
        for (const fs::directory_entry& iterator : fs::directory_iterator(fs::u8path(path))) {
            if (iterator.path().u8string().find(file) != std::string::npos) {
                std::string foundPath = iterator.path().u8string();

                #if defined(__linux__)
                    // Linux CS:GO is 64-bit but still contains the 32-bit libraries for some reason
                    bfd* bfdFile = bfd_openr(foundPath.c_str(), nullptr);
                    if (bfdFile == nullptr)
                        continue;

                    const char* arch = bfd_printable_arch_mach(bfd_get_arch(bfdFile), bfd_get_mach(bfdFile));

                    bfd_close(bfdFile);

                    // Skip the library if it isn't a 64-bit library
                    if (std::strcmp(arch, "i386:x86-64") != 0)
                        continue;
                #endif

                // We found what we were looking for
                std::sprintf(out, "%s", foundPath.c_str());
                break;
            }
        }
    #endif

    return out[0] != 0 && out[1] != 0;
}

bool io::FindLibrary(uintptr_t address, char* out) {
    std::memset(out, 0, strlen(out));

    #if defined(_WIN32)
        HMODULE module;

        if (GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCTSTR) address, &module)) {
            if (GetModuleFileName(module, out, strlen(out)) != 0)
                return true;
        }
    #elif defined(__APPLE__) || defined(__linux__)
        Dl_info dlInfo;

        if (dladdr(reinterpret_cast<void*>(address), &dlInfo) == 0) {
            std::snprintf(out, strlen(out), "%s", dlInfo.dli_fname);
            return true;
        }
    #endif

    return false;
}

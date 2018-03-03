#ifndef ANIUM_LOGGING_HPP
#define ANIUM_LOGGING_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <ctime>
#include <sstream>
#include <cstdarg>

#if !defined(__APPLE__)
    #include <experimental/filesystem>
    namespace fs = std::experimental::filesystem;
#endif

class Logger {
private:
    std::string name;
    bool withTime;
    std::ofstream stream;

public:
    Logger(std::string name, bool time = true) {
        this->name = std::move(name);
        this->withTime = time;

        // Apple Clang doesn't have support for <filesystem> nor <experimental/filesystem>
        // So we'll just hard code the path to the temp. directory
        #if defined(__APPLE__)
            this->stream.open("/tmp/" + this->name + ".log");
        #else
            char separator = fs::path::preferred_separator;

            std::stringstream logFilePath("");
            logFilePath << fs::temp_directory_path().u8string() << separator << this->name << ".log";

            this->stream.open(logFilePath.str());
        #endif
    }

    ~Logger() {
        this->stream.close();
    }

    void log(std::string message, ...) {
        std::string currentTime = []() -> std::string {
            struct tm timeStruct;
            char buffer[80];

            time_t now = time(nullptr);
            timeStruct = *localtime(&now);

            strftime(buffer, sizeof(buffer), "%d.%m.%Y %X", &timeStruct);

            return std::string(buffer);
        }();

        std::stringstream stream("");

        if (this->withTime)
            stream << currentTime;

        char buffer[512];
        va_list varargs;
        va_start(varargs, message);
        sprintf(buffer, message.c_str(), varargs);
        va_end(varargs);

        stream << " - " << this->name << " - " << buffer << std::endl;

        std::cout << stream.str();
        this->stream << stream.str();
    }

};

extern Logger logger;

#endif //ANIUM_LOGGING_HPP

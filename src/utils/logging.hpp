#ifndef ANIUM_LOGGING_HPP
#define ANIUM_LOGGING_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <ctime>
#include <sstream>
#include <cstdarg>
#include "iohelper.hpp"

class Logger {
private:
    std::string name;
    bool withTime;
    std::ofstream stream;

public:
    explicit Logger(const std::string& name, bool time = true) {
        this->name = std::move(name);
        this->withTime = time;

        std::stringstream logFilePath(io::GetTempDirectory());
        logFilePath << io::GetPathSeparator() << this->name << ".log";

        this->stream.open(logFilePath.str());
    }

    ~Logger() {
        this->stream.flush();
        this->stream.close();
    }

    void log(const std::string& message, ...) {
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
        this->stream.flush();
    }

};

extern Logger logger;

#endif //ANIUM_LOGGING_HPP

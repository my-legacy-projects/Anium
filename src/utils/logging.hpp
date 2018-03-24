#ifndef ANIUM_LOGGING_HPP
#define ANIUM_LOGGING_HPP

#include <cstdarg>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "../interfaces/interfaces.hpp"
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

        this->stream.open(io::GetTempDirectory() + io::GetPathSeparator() + this->name + ".log");
    }

    ~Logger() {
        this->stream.flush();
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

        char buffer[512]; // If you print over 512 chars go to hell
        va_list varargs;
        va_start(varargs, message);
        vsnprintf(buffer, sizeof(buffer), message.c_str(), varargs);
        va_end(varargs);

        stream << " - " << this->name << " - " << buffer << std::endl;

        if (cvar != nullptr) {
            std::stringstream engineConsole("");
            engineConsole << " - " << currentTime << " - " << buffer << std::endl;

            cvar->ConsoleColorPrintf(Color(255, 169, 10), "Anium");
            cvar->ConsoleColorPrintf(Color(255, 255, 255), engineConsole.str().c_str());
        }

        std::cout << stream.str();
        this->stream << stream.str();
        this->stream.flush();
    }

};

extern Logger logger;

#endif //ANIUM_LOGGING_HPP

#ifndef ANIUM_PATTERN_HPP
#define ANIUM_PATTERN_HPP

#include "../interfaces/interfaces.hpp"
#include "../utils/hex.hpp"
#include "../utils/logging.hpp"

class Pattern {
private:
    SourceLib module;
    std::string signature;

    // Credit: https://github.com/learn-more/findpattern-bench/blob/master/patterns/learn_more.h
    uintptr_t FindPattern() {
        const char* pattern = this->signature.c_str();
        uintptr_t firstMatch = 0;

        uintptr_t start = this->module.GetAddress();
        uintptr_t end = start + this->module.GetSize();

        for (uintptr_t pos = start; pos < end; pos++) {
            if (*pattern == 0)
                return firstMatch;

            const uint8_t currentPattern = *reinterpret_cast<const uint8_t*>(pattern);
            const uint8_t currentMemory = *reinterpret_cast<const uint8_t*>(pos);

            if (currentPattern == '\?' || currentMemory == Hex::GetBytes(pattern)) {
                if (firstMatch == 0)
                    firstMatch = pos;

                if (pattern[2] == 0) {
                    logger.log("Found pattern \"%s\" in %s at 0x%08X.",
                               this->signature.c_str(), this->module.GetModuleName().c_str(), &firstMatch);
                    return firstMatch;
                }

                pattern += currentPattern != '\?' ? 3 : 2;
            } else {
                pattern = this->signature.c_str();
                firstMatch = 0;
            }
        }

        logger.log("Unable to find pattern \"%s\" in %s.",
                   this->signature.c_str(), this->module.GetModuleName().c_str());
        return 0;
    }

public:
    Pattern(SourceLib module, std::string _windows, std::string _mac, std::string _linux) : module(module) {
        this->module = module;

        #if defined(_WIN32)
            this->signature = std::move(_windows);
        #elif defined(__APPLE__)
            this->signature = std::move(_mac);
        #elif defined(__linux__)
            this->signature = std::move(_linux);
        #endif
    }

    template <typename T>
    T Find(int _win = 0, int _mac = 0, int _linux = 0) {
        if (this->module.GetAddress() == 0 || this->module.GetSize() == 0) {
            logger.log("The address or size of the SourceLib weren't initialized before trying"
                       "to scan for a pattern in it.");

            return nullptr;
        }

        #if defined(_WIN32)
            int offset = _win;
        #elif defined(__APPLE__)
            int offset = _mac;
        #elif defined(__linux__)
            int offset = _linux;
        #endif

        return reinterpret_cast<T>(FindPattern() + offset);
    }

};

#endif //ANIUM_PATTERN_HPP

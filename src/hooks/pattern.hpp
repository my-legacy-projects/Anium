#ifndef ANIUM_PATTERN_HPP
#define ANIUM_PATTERN_HPP

#include "../interfaces/interfaces.hpp"
#include "../utils/logging.hpp"

#define INRANGE(x, a, b) ((x) >= (a) && (x) <= (b))
#define getBits(x) (INRANGE(x, '0', '9') ? ((x) - '0') : (((x) & (~0x20)) - 'A' + 0xa))
#define getByte(x) (getBits((x)[0]) << 4 | getBits((x)[1]))

class Pattern {
private:
    SourceLib module;
    std::string signature;

    // Credit: https://github.com/learn-more/findpattern-bench/blob/master/patterns/learn_more.h
    uintptr_t FindPattern(const uintptr_t& start, const uintptr_t& size) {
        const char* pattern = this->signature.c_str();
        uintptr_t firstMatch = 0;

        for (uintptr_t pos = start; pos < (start + size); pos++) {
            if (*pattern == 0)
                return firstMatch;

            const uint8_t currentPattern = *reinterpret_cast<const uint8_t*>(pattern);
            const uint8_t currentMemory = *reinterpret_cast<const uint8_t*>(pos);

            if (currentPattern == '\?' || currentMemory == getByte(pattern)) {
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

    uintptr_t Find(int _win = 0, int _mac = 0, int _linux = 0) {
        if (this->module.GetAddress() == 0 || this->module.GetSize() == 0) {
            logger.log("The address or size of the SourceLib weren't initialized before trying"
                       "to scan for a pattern in it.");

            return 0;
        }

        #if defined(_WIN32)
            int offset = _win;
        #elif defined(__APPLE__)
            int offset = _mac;
        #elif defined(__linux__)
            int offset = _linux;
        #endif

        return FindPattern(this->module.GetAddress(), this->module.GetSize()) + offset;
    }

};

#endif //ANIUM_PATTERN_HPP

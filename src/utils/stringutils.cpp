#include "stringutils.hpp"

bool StringHelper::StartsWith(const std::string &string, const std::string &prefix) {
    return string.compare(0, prefix.length(), prefix) == 0;
}

bool StringHelper::EndsWith(const std::string &string, const std::string &suffix) {
    return string.compare(string.length() - suffix.length(), suffix.length(), suffix) == 0;
}

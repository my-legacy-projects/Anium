#ifndef ANIUM_STRINGUTILS_HPP
#define ANIUM_STRINGUTILS_HPP

#include <string>

namespace StringHelper {

    bool StartsWith(const std::string& string, const std::string& prefix);

    bool EndsWith(const std::string& string, const std::string& suffix);

}

#endif //ANIUM_STRINGUTILS_HPP

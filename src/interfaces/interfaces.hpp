#ifndef ANIUM_INTERFACES_HPP
#define ANIUM_INTERFACES_HPP

#include "../sdk/interfaces/IBaseClientDLL.hpp"
#include "../sdk/interfaces/ICvar.hpp"
#include "sourcelib.hpp"

extern SourceLib clientLib;
extern SourceLib vStdLib;
extern SourceLib materialSystemLib;

extern IBaseClientDLL* client;
extern ICvar* cvar;

namespace Interfaces {

    void Find();

}

#endif //ANIUM_INTERFACES_HPP

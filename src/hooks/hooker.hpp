#ifndef ANIUM_HOOKER_HPP
#define ANIUM_HOOKER_HPP

#include "pattern.hpp"

using oStartDrawing = void (*)(void*);
using oFinishDrawing = void (*)(void*);

extern oStartDrawing StartDrawing;
extern oFinishDrawing FinishDrawing;

namespace Hooker {

    void Init();

}

#endif //ANIUM_HOOKER_HPP

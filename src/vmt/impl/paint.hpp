#ifndef ANIUM_PAINT_HPP
#define ANIUM_PAINT_HPP

#include "../../interfaces/iface.hpp"
#include "../../sdk/definitions/PaintMode.hpp"
#include "../../sdk/definitions/SurfaceFontFlags.hpp"
//#include "../../events/impl/paintevent.hpp"
//#include "../../events/eventbus.hpp"
#include "../../utils/logging.hpp"
#include "../../anium.hpp"
#include "../vmt.hpp"

namespace Hooks {

    #if defined(_WIN32)
        void __stdcall Paint(PaintMode mode);
    #elif defined(__APPLE__) || defined(__linux__)
        void Paint(void*, PaintMode mode);
    #endif

}

#endif //ANIUM_PAINT_HPP

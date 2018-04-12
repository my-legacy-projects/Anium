#ifndef ANIUM_CEFFECTS_HPP
#define ANIUM_CEFFECTS_HPP

#include "../../hooks/vfunc.hpp"
#include "../definitions/Model.hpp"
#include "../definitions/Dlight.hpp"

class CEffects {
public:
    dlight AllocateDlight(int key) {
        using oAllocateDlight = dlight (*)(void*, int);
        return VFunc(this, 4, 4, 4).GetFunction<oAllocateDlight>()(this, key);
    }

};

#endif  // ANIUM_CEFFECTS_HPP

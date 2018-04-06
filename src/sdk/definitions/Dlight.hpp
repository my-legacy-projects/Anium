#ifndef ANIUM_DLIGHT_HPP
#define ANIUM_DLIGHT_HPP

#include "../miscellaneous/Vector.hpp"
#include "../miscellaneous/misc.hpp"

struct dlight {
    int flags;
    Vector origin;
    float radius;
    ColorExp color;
    float lifetime;
    float decay;
    float min;
    int key;
    int style;
    Vector direction;
    float innerAngle;
    float outerAngle;

};

#endif  // ANIUM_DLIGHT_HPP

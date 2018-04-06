#ifndef ANIUM_CUSERCMD_HPP
#define ANIUM_CUSERCMD_HPP

#include "../miscellaneous/Vector.hpp"

struct CUserCmd {
private:
    virtual ~CUserCmd() {};

public:
    int commandNumber;
    int tickCount;
    Vector viewAngles;
    Vector aimDirection;
    float forward;
    float side;
    float up;
    int buttons;
    unsigned char impulse;
    int selectedWeapon;
    int weaponSubType;
    int randomSeed;
    short mouseX;
    short mouseY;
    bool predicted;
    Vector headAngles;
    Vector headOffset;

};

#endif  // ANIUM_CUSERCMD_HPP

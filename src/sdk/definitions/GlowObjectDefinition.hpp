#ifndef ANIUM_GLOWOBJECTDEFINITION_HPP
#define ANIUM_GLOWOBJECTDEFINITION_HPP

struct GlowObjectDefinition {
    C_BaseEntity* entity;
    float color[3];
    float alpha;
    char _pad0[4];
    float _pad1;
    float bloomAmount;
    float zeroPoint;
    bool renderOccluded;
    bool renderUnoccluded;
    bool renderFullBloom;
    char _pad2[1];
    int fullBloomStencilTestValue;
    int _pad3;
    int splitScreenSlot;
    int nextFreeSlot;

    bool IsUnused() const {
        return this->nextFreeSlot != -2;
    }

};

#endif  // ANIUM_GLOWOBJECTDEFINITION_HPP

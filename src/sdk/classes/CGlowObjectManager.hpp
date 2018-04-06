#ifndef ANIUM_CGLOWOBJECTMANAGER_HPP
#define ANIUM_CGLOWOBJECTMANAGER_HPP

#include <cstring>
#include <vector>
#include "../definitions/GlowObjectDefinition.hpp"
#include "../miscellaneous/Color.hpp"

class CGlowObjectManager {
private:
    std::vector<GlowObjectDefinition> objects;
    int firstFreeSlot;

public:
    int Register(C_BaseEntity* entity, Color color = WHITE, bool renderOccluded = false,
                 bool renderUnoccluded = false, int splitScreenSlot = 0) {
        if (this->firstFreeSlot == -1)
            return -1;

        int index = this->firstFreeSlot;
        this->firstFreeSlot = this->objects[index].nextFreeSlot;

        this->objects[index].entity = entity;
        this->objects[index].color[0] = color.GetRed();
        this->objects[index].color[1] = color.GetGreen();
        this->objects[index].color[2] = color.GetBlue();
        this->objects[index].alpha = color.GetAlpha();
        this->objects[index].renderOccluded = renderOccluded;
        this->objects[index].renderUnoccluded = renderUnoccluded;
        this->objects[index].splitScreenSlot = splitScreenSlot;
        this->objects[index].nextFreeSlot = -2;

        return index;
    }

    void Unregister(int index) {
        this->objects[index].nextFreeSlot = this->firstFreeSlot;
        this->objects[index].entity = nullptr;

        this->firstFreeSlot = index;
    }

    bool IsGlowing(C_BaseEntity* entity) {
        for (GlowObjectDefinition g : this->objects) {
            if (g.entity == entity && !g.IsUnused()) {
                return true;
            }
        }

        return false;
    }

};

#endif  // ANIUM_CGLOWOBJECTMANAGER_HPP

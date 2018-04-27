#ifndef ANIUM_IENGINEVGUI_HPP
#define ANIUM_IENGINEVGUI_HPP

#include "../definitions/VGuiPanel.hpp"

class IEngineVGui {
public:
    virtual ~IEngineVGui() {}
    virtual unsigned long long GetPanel(VGuiPanel type) = 0;
    virtual bool IsGameUIVisible() = 0;
};

#endif  // ANIUM_IENGINEVGUI_HPP

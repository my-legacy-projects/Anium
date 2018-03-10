#include "framestagenotify.hpp"

void Hooks::FrameStageNotify(int frametime) {
    logger.log("Frame stage: %d", frametime);

    typedef void (__thiscall*oFrameStageNotify)(void*, int);
    clientVMT->GetOriginal<oFrameStageNotify>(36, 36, 36)(client, frametime);
}

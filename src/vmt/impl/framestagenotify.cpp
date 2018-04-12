#include "framestagenotify.hpp"

void Hooks::FrameStageNotify(ClientFrameStage_t stage) {
    FrameStageNotifyEvent event = eventBus.publish<FrameStageNotifyEvent>(stage);

    if (!event.IsCancelled()) {
        using oFrameStageNotify = void (__thiscall*)(void*, ClientFrameStage_t);
        clientVMT->GetOriginal<oFrameStageNotify>(36, 36, 36)(client, stage);
    }
}

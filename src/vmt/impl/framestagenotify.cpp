#include "framestagenotify.hpp"

#if defined(_WIN32)
void __stdcall Hooks::FrameStageNotify(ClientFrameStage_t stage) {
#elif defined(__APPLE__) || defined(__linux__)
void Hooks::FrameStageNotify(void*, ClientFrameStage_t stage) {
#endif
    FrameStageNotifyEvent event = eventBus.publish<FrameStageNotifyEvent>(stage);

    if (!event.IsCancelled()) {
        using oFrameStageNotify = void (__thiscall*)(void*, ClientFrameStage_t);
        clientVMT->GetOriginal<oFrameStageNotify>(36, 36, 36)(client, stage);
    }
}

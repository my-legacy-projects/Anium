#include "vmt.hpp"

VMTHook* clientVMT = nullptr;
VMTHook* engineVGuiVMT = nullptr;

void VMT::Init() {
    clientVMT = new VMTHook(IFace::client);
    clientVMT->Hook(36, 36, 36, (void*) Hooks::FrameStageNotify);

    engineVGuiVMT = new VMTHook(IFace::engineVGui);
    engineVGuiVMT->Hook(14, 15, 15, (void*) Hooks::Paint);
}

void VMT::Release() {
    delete clientVMT;
    delete engineVGuiVMT;
}

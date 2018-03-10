#include "vmt.hpp"

VMTHook* clientVMT = nullptr;

void VMT::Init() {
    clientVMT = new VMTHook(client);
    clientVMT->Hook(36, 36, 36, (void*) Hooks::FrameStageNotify);
}

void VMT::Release() {
    clientVMT->ReleaseAll();
    delete(clientVMT);
}

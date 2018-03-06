#include "vmt.hpp"

VMTHook clientVMT = nullptr;

void VMT::Init() {
    clientVMT = new VMTHook(client);


}

void VMT::Grab() {

}

void VMT::Release() {
    clientVMT.ReleaseAll();
    delete clientVMT;
}

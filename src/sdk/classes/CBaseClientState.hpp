#ifndef ANIUM_CBASECLIENTSTATE_HPP
#define ANIUM_CBASECLIENTSTATE_HPP

#include <string>

class CBaseClientState {
private:
    #if defined(_WIN32)
        char _pad0[376];
    /*#elif defined(__APPLE__)
        char _pad0[516];*/
    #elif defined(__APPLE__) || defined(__linux__)
        char _pad0[524];
    #endif
    int deltaTick;
    bool paused;
    char _pad1[3];
    int viewEntity;
    int playerSlot;
    char levelName[260];
    char levelNameShort[40];
    char groupName[40];

public:
    int GetDeltaTick() const {
        return this->deltaTick;
    }

    void SetDeltaTick(int deltaTick) {
        this->deltaTick = deltaTick;
    }

    void ForceFullUpdate() {
        this->deltaTick = -1;
    }

    bool IsPaused() const {
        return this->paused;
    }

    int GetViewEntity() const {
        return this->viewEntity;
    }

    int GetPlayerSlot() const {
        return this->playerSlot;
    }

    std::string GetLevelName() const {
        return this->levelName;
    }

    std::string GetShortLevelName() const {
        return this->levelNameShort;
    }

    std::string GetGroupName() const {
        return this->groupName;
    }

};

#endif  // ANIUM_CBASECLIENTSTATE_HPP

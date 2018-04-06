#ifndef ANIUM_CGLOBALVARS_HPP
#define ANIUM_CGLOBALVARS_HPP

class CGlobalVars {
private:
    float realTime;
    int frameCount;
    float absoluteFrameTime;
    float absoluteFrameStartTime;
    float currentTime;
    float frameTime;
    int maxClients;
    int tickCount;
    float intervalPerTick;
    float interpolationTime;
    int simulationTicks;
    int protocol;
    void* saveData;
    bool client;
    bool remoteClient;
    int timeStampNetworkingBase;
    int timeStampRandomizedWindow;

public:
    float GetRealTime() const {
        return this->realTime;
    }

    float GetFrameCount() const {
        return this->frameCount;
    }

    float GetAbsoluteFrameTime() const {
        return this->absoluteFrameTime;
    }

    float GetAbsoluteFrameStartTime() const {
        return this->absoluteFrameStartTime;
    }

    float GetCurrentTime() const {
        return this->currentTime;
    }

    float GetFrameTime() const {
        return this->frameTime;
    }

    int GetMaxClients() const {
        return this->maxClients;
    }

    int GetTickCount() const {
        return this->tickCount;
    }

    float GetIntervalPerTick() const {
        return this->intervalPerTick;
    }

    float GetInterpolationTime() const {
        return this->interpolationTime;
    }

    int GetSimulationTicks() const {
        return this->simulationTicks;
    }

    int GetProtocol() const {
        return this->protocol;
    }

    void* GetSaveData() const {
        return this->saveData;
    }

    bool IsClient() const {
        return this->client;
    }

    bool IsRemoteClient() const {
        return this->remoteClient;
    }

    void SetTickCount(int tickCount) {
        this->tickCount = tickCount;
    }

};

#endif  // ANIUM_CGLOBALVARS_HPP

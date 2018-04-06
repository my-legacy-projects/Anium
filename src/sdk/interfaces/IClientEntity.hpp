#ifndef ANIUM_ICLIENTENTITY_HPP
#define ANIUM_ICLIENTENTITY_HPP

#include "../definitions/DataUpdateType.hpp"
#include "../definitions/Matrix.hpp"
#include "../definitions/Model.hpp"
#include "../sdk.hpp"

class IHandleEntity {
public:
    virtual ~IHandleEntity() {};
};

class IClientUnknown : public IHandleEntity {};

class IClientRenderable {
public:
    virtual ~IClientRenderable() {};

    model* GetModel() {
        typedef model* (*oGetModel)(void*);
        return VFunc(this, 8, 8, 8).GetFunction<oGetModel>()(this);
    }

    bool SetupBones(matrix3x4* boneMatrix, int max, int mask, float time = 0) {
        typedef bool (*oSetupBones)(void*, matrix3x4*, int, int, float);
        return VFunc(this, 13, 13, 13).GetFunction<oSetupBones>()(this, boneMatrix, max, mask, time);
    }

};

class IClientNetworkable {
public:
    virtual ~IClientNetworkable() {};

    void Release() {
        typedef void (*oRelease)(void*);
        VFunc(this, 1, 1, 1).GetFunction<oRelease>()(this);
    }

    ClientClass* GetClientClass() {
        typedef ClientClass* (*oGetClientClass)(void*);
        return VFunc(this, 2, 2, 2).GetFunction<oGetClientClass>()(this);
    }

    void PreDataUpdate(DataUpdateType type) {
        typedef void (*oPreDataUpdate)(void*, DataUpdateType);
        VFunc(this, 6, 6, 6).GetFunction<oPreDataUpdate>()(this, type);
    }

    bool IsDormant() {
        typedef bool (*oIsDormant)(void*);
        return VFunc(this, 8, 9, 9).GetFunction<oIsDormant>()(this);
    }

    int GetIndex() {
        typedef int (*oGetIndex)(void*);
        return VFunc(this, 9, 10, 10).GetFunction<oGetIndex>()(this);
    }

    void SetDestroyedOnRecreateEntities() {
        typedef void (*oSetDestroyedOnRecreateEntities)(void*);
        VFunc(this, 12, 13, 13).GetFunction<oSetDestroyedOnRecreateEntities>()(this);
    }

};

class IClientThinkable {
public:
    virtual ~IClientThinkable() {};
};

class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable {
public:
    virtual ~IClientEntity() {};
};

#endif  // ANIUM_ICLIENTENTITY_HPP

#ifndef ANIUM_CONVAR_HPP
#define ANIUM_CONVAR_HPP

#include "../../hooks/vfunc.hpp"

#define CVAR_NONE                   0

#define CVAR_UNREGISTERED			(1 << 0)
#define CVAR_DEVELOPMENTONLY		(1 << 1)
#define CVAR_GAMEDLL				(1 << 2)
#define CVAR_CLIENTDLL				(1 << 3)
#define CVAR_HIDDEN				    (1 << 4)

#define CVAR_PROTECTED				(1 << 5)
#define CVAR_SPONLY				    (1 << 6)
#define CVAR_ARCHIVE				(1 << 7)
#define CVAR_NOTIFY				    (1 << 8)
#define CVAR_USERINFO				(1 << 9)
#define CVAR_CHEAT					(1 << 14)

#define CVAR_PRINTABLEONLY			(1 << 10)
#define CVAR_UNLOGGED				(1 << 11)
#define CVAR_NEVER_AS_STRING		(1 << 12)
#define CVAR_RELEASE				(1 << 19)

#define CVAR_REPLICATED			    (1 << 13)
#define CVAR_DEMO					(1 << 16)
#define CVAR_DONTRECORD			    (1 << 17)

#define CVAR_NOT_CONNECTED			(1 << 22)
#define CVAR_ARCHIVE_XBOX			(1 << 24)
#define CVAR_SERVER_CAN_EXECUTE	    (1 << 28)
#define CVAR_SERVER_CANNOT_QUERY	(1 << 29)
#define CVAR_CLIENTCMD_CAN_EXECUTE	(1 << 30)

class ConVar {
private:
    char _pad0[4];
    ConVar* next;
    int32_t registered;
    char* name;
    char* helpString;
    int32_t flags;
    char _pad1[4];
    ConVar* parent;
    char* defaultValue;
    char* string;
    int32_t length;
    float floatValue;
    int32_t intValue;
    int32_t hasMin;
    float min;
    int32_t hasMax;
    float max;
    void* changeCallback;

public:
    float GetFloat() {
        typedef float (*oGetFloat)(void*);
        return VFunc(this, 12, 15, 15).GetFunction<oGetFloat>()(this);
    }

    int GetInt() {
        typedef int (*oGetInt)(void*);
        return VFunc(this, 13, 16, 16).GetFunction<oGetInt>()(this);
    }

    bool GetBool() {
        return (bool) GetInt();
    }

    const char* GetString() {
        const char* parentValue = this->parent->string;
        return parentValue ? parentValue : "";
    }

    void SetValue(const char* value) {
        typedef void (*oSetValue)(void*, const char*);
        VFunc(this, 14, 17, 17).GetFunction<oSetValue>()(this, value);
    }

    void SetValue(float value) {
        typedef void (*oSetValue)(void*, float);
        VFunc(this, 15, 18, 18).GetFunction<oSetValue>()(this, value);
    }

    void SetValue(int value) {
        typedef void (*oSetValue)(void*, int);
        VFunc(this, 16, 19, 19).GetFunction<oSetValue>()(this, value);
    }

    void SetValue(bool value) {
        SetValue((int) value);
    }

};

#endif  // ANIUM_CONVAR_HPP

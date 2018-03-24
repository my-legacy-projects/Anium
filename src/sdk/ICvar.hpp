#ifndef ANIUM_ICVAR_HPP
#define ANIUM_ICVAR_HPP

#include "../hooks/vfunc.hpp"
#include "ConCommandBase.hpp"
#include "Color.hpp"

class ICvar {
public:
    /*void RegisterConCommand(ConCommandBase* base) {
        typedef void (*oRegisterConCommand)(void*, ConCommandBase*);
        return VFunc(this, 10, 10, 10).GetFunction<oRegisterConCommand>()(this, base);
    }

    void UnregisterConCommand(CVarDLLIdentifier_t identifier) {
        typedef void (*oUnregisterConCommand)(void*, CVarDLLIdentifier_t);
        return VFunc(this, 12, 12, 12).GetFunction<oUnregisterConCommand>()(this, identifier);
    }

    ConVar* FindVar(const char* name) {
        typedef ConVar* (*oFindVar)(void*, const char*);
        return VFunc(this, 16, 15, 15).GetFunction<oFindVar>()(this, name);
    }*/

    template <typename... V>
    void ConsoleColorPrintf(const Color& color, const char* format, V... values) {
        typedef void (*oConsoleColorPrintf)(void*, const Color&, const char*, ...);
        return VFunc(this, 25, 25, 25).GetFunction<oConsoleColorPrintf>()(this, color, format, values...);
    }

    template <typename... V>
    void ConsoleDPrintf(const char* format, V... values) {
        typedef void (*oConsoleDPrintf)(void*, const char* format, ...);
        return VFunc(this, 27, 27, 27).GetFunction<oConsoleDPrintf>()(this, format, values...);
    }

};

#endif  // ANIUM_ICVAR_HPP

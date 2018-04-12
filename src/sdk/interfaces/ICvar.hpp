#ifndef ANIUM_ICVAR_HPP
#define ANIUM_ICVAR_HPP

#include "../../hooks/vfunc.hpp"
#include "../classes/ConCommandBase.hpp"
#include "../classes/ConVar.hpp"
#include "../miscellaneous/Color.hpp"

class ICvar {
public:
    void RegisterConCommand(ConCommandBase* base) {
        using oRegisterConCommand = void (*)(void*, ConCommandBase*);
        return VFunc(this, 10, 10, 10).GetFunction<oRegisterConCommand>()(this, base);
    }

    void UnregisterConCommand(int identifier) {
        using oUnregisterConCommand = void (*)(void*, int);
        return VFunc(this, 12, 12, 12).GetFunction<oUnregisterConCommand>()(this, identifier);
    }

    ConVar* FindVar(const char* name) {
        using oFindVar = ConVar* (*)(void*, const char*);
        return VFunc(this, 16, 15, 15).GetFunction<oFindVar>()(this, name);
    }

    template <typename... V>
    void ConsoleColorPrintf(const Color& color, const char* format, V... values) {
        using oConsoleColorPrintf = void (*)(void*, const Color&, const char*, ...);
        return VFunc(this, 25, 25, 25).GetFunction<oConsoleColorPrintf>()(this, color, format, values...);
    }

    template <typename... V>
    void ConsoleDPrintf(const char* format, V... values) {
        using oConsoleDPrintf = void (*)(void*, const char* format, ...);
        return VFunc(this, 27, 27, 27).GetFunction<oConsoleDPrintf>()(this, format, values...);
    }

};

#endif  // ANIUM_ICVAR_HPP

#ifndef ANIUM_ISURFACE_HPP
#define ANIUM_ISURFACE_HPP

#include "../../hooks/vfunc.hpp"
#include "../miscellaneous/Color.hpp"

// WinAPI defines these methods as macros so let's undefine them
#if defined(_WIN32)
    #undef CreateFont
    #undef DrawText
#endif

class ISurface {
public:
    void SetDrawColor(Color color) {
        using oSetDrawColor = void (*)(void*, int, int, int, int);
        VFunc(this, 15, 14, 14).GetFunction<oSetDrawColor>()(this, color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha());
    }

    void DrawFilledRect(int x, int y, int width, int height) {
        using oDrawFilledRect = void (*)(void*, int, int, int, int);
        VFunc(this, 16, 16, 16).GetFunction<oDrawFilledRect>()(this, x, y, width, height);
    }

    void DrawOutlinedRect(int x, int y, int width, int height) {
        using oDrawOutlinedRect = void (*)(void*, int, int, int, int);
        VFunc(this, 18, 18, 18).GetFunction<oDrawOutlinedRect>()(this, x, y, width, height);
    }

    void DrawLine(int startX, int startY, int endX, int endY) {
        using oDrawLine = void (*)(void*, int, int, int, int);
        VFunc(this, 19, 19, 19).GetFunction<oDrawLine>()(this, startX, startY, endX, endY);
    }

    void SetTextFont(unsigned long long font) {
        using oSetTextFont = void (*)(void*, unsigned long long);
        VFunc(this, 23, 23, 23).GetFunction<oSetTextFont>()(this, font);
    }

    void SetTextColor(Color color) {
        using oSetTextColor = void (*)(void*, int, int, int, int);
        VFunc(this, 25, 24, 24).GetFunction<oSetTextColor>()(this, color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha());
    }

    void SetTextPosition(int x, int y) {
        using oSetTextPosition = void (*)(void*, int, int);
        VFunc(this, 26, 26, 26).GetFunction<oSetTextPosition>()(this, x, y);
    }

    void DrawText(const wchar_t* text, int length, int type = 0) {
        using oDrawText = void (*)(void*, const wchar_t*, int, int);
        VFunc(this, 28, 28, 28).GetFunction<oDrawText>()(this, text, length, type);
    }

    unsigned int CreateFont() {
        using oCreateFont = unsigned int (*)(void*);
        return VFunc(this, 71, 71, 71).GetFunction<oCreateFont>()(this);
    }

    bool SetFontGlyphSet(unsigned int font, const char* name, int tall, int weight, int blur, int lines, int flags, int min = 0, int max = 0) {
        using oSetFontGlyphSet = bool (*)(void*, unsigned int, const char*, int, int, int, int, int, int, int);
        return VFunc(this, 72, 72, 72).GetFunction<oSetFontGlyphSet>()(this, font, name, tall, weight, blur, lines, flags, min, max);
    }

};

#endif  // ANIUM_ISURFACE_HPP

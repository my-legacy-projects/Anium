#ifndef ANIUM_SURFACEFONTFLAGS_HPP
#define ANIUM_SURFACEFONTFLAGS_HPP

enum SurfaceFontFlags {
    NONE,
    ITALIC	= 0x001,
    UNDERLINE = 0x002,
    STRIKEOUT = 0x004,
    SYMBOL = 0x008,
    ANTIALIAS = 0x010,
    GAUSSIANBLUR = 0x020,
    ROTARY = 0x040,
    DROPSHADOW	= 0x080,
    ADDITIVE = 0x100,
    OUTLINE = 0x200,
    CUSTOM	= 0x400,		            // custom generated font - never fall back to asian compatibility mode
    NO_FALLBACK_BITMAP	= 0x800,		// compiled bitmap font - no fallbacks

};

#endif  // ANIUM_SURFACEFONTFLAGS_HPP

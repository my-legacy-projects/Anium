#ifndef ANIUM_PAINTMODE_HPP
#define ANIUM_PAINTMODE_HPP

enum PaintMode : int {
    PAINT_UIPANELS = (1 << 0),
    PAINT_INGAMEPANELS = (1 << 1),
    PAINT_CURSOR = (1 << 2)
};

#endif  // ANIUM_PAINTMODE_HPP

#include "paint.hpp"

#if defined(_WIN32)
void __stdcall Hooks::Paint(PaintMode mode) {
#elif defined(__APPLE__) || defined(__linux__)
void Hooks::Paint(void*, PaintMode mode) {
#endif
    using oPaint = void (__thiscall*)(void*, PaintMode);
    engineVGuiVMT->GetOriginal<oPaint>(14, 15, 15)(engineVGui, mode);

    if (mode & PaintMode::PAINT_UIPANELS) {
        #if !defined(__APPLE__)
            StartDrawing(surface); // TODO Apple: Find sig for StartDrawing
        #endif

        /**/// Surface watermark is temporary for now, we'll draw with ImGui later

        static bool init = false;
        static unsigned int font = 0;

        if (!init) {
            font = surface->CreateFont();
            surface->SetFontGlyphSet(font, "IDONTEXISTSOITUSESDEFAULTFONTLOL", 20, 0, 0, 0, 0);

            init = true;
            logger.log("Font init complete");
        }

        wchar_t buffer[] = L"Anium";

        surface->SetTextFont(font);

        // Watermark
        surface->SetTextPosition(4, 1);
        surface->SetTextColor(ORANGE);
        surface->DrawText(buffer, std::size(buffer), SurfaceFontFlags::ANTIALIAS | SurfaceFontFlags::DROPSHADOW);

        //*/

        //PaintEvent event = eventBus.publish<PaintEvent>(mode);

        #if !defined(__APPLE__)
            FinishDrawing(surface); // TODO Apple: Find sig for FinishDrawing
        #endif
    }
}

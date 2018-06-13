#include "paint.hpp"

#if defined(_WIN32)
void __stdcall Hooks::Paint(PaintMode mode) {
#elif defined(__APPLE__) || defined(__linux__)
void Hooks::Paint(void*, PaintMode mode) {
#endif
    using oPaint = void (__thiscall*)(void*, PaintMode);
    engineVGuiVMT->GetOriginal<oPaint>(14, 15, 15)(IFace::engineVGui, mode);

    if (mode & PaintMode::PAINT_UIPANELS) {
        #if !defined(__APPLE__)
            StartDrawing(IFace::surface); // TODO Apple: Find sig for StartDrawing
        #endif

        /**/// Surface watermark is temporary for now, we'll draw with ImGui later

        static bool init = false;
        static unsigned int font = 0;

        if (!init) {
            font = IFace::surface->CreateFont();
            IFace::surface->SetFontGlyphSet(font, "IDONTEXISTSOITUSESDEFAULTFONTLOL", 20, 0, 0, 0, 0);

            init = true;
            logger.log("Font init complete");
        }

        wchar_t buffer[] = L"Anium";

        IFace::surface->SetTextFont(font);

        // Watermark
        IFace::surface->SetTextPosition(4, 1);
        IFace::surface->SetTextColor(ORANGE);
        IFace::surface->DrawText(buffer, std::size(buffer), SurfaceFontFlags::ANTIALIAS | SurfaceFontFlags::DROPSHADOW);

        //*/

        //PaintEvent event = eventBus.publish<PaintEvent>(mode);

        #if !defined(__APPLE__)
            FinishDrawing(IFace::surface); // TODO Apple: Find sig for FinishDrawing
        #endif
    }
}

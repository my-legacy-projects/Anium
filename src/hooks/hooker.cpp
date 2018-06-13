#include "hooker.hpp"

oStartDrawing StartDrawing = nullptr;
oFinishDrawing FinishDrawing = nullptr;

void FindDrawFunctions() {
    Pattern startPattern(Libraries::vGuiMatSurface, "83 EC 38 80",
                                                    "",
                                                    "55 48 89 E5 53 48 89 FB 48 83 EC 28 80");
    Pattern finishPattern(Libraries::vGuiMatSurface, "56 C6 05",
                                                     "",
                                                     "55 31 FF 48 89");

    StartDrawing = startPattern.Find<oStartDrawing>(-6, 0, 0);
    FinishDrawing = finishPattern.Find<oFinishDrawing>(-6, 0, 0);
}

void Hooker::Init() {
    FindDrawFunctions();
}

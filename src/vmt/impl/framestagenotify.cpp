#include "framestagenotify.hpp"

void FrameStageNotify::FrameStageNotifyHook(void *self, int frameStage) {
    logger.log("Frame stage: %i", frameStage);
}

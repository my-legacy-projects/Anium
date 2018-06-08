#ifndef ANIUM_FRAMESTAGENOTIFY_HPP
#define ANIUM_FRAMESTAGENOTIFY_HPP

#include "../../sdk/definitions/ClientFrameStage.hpp"
//#include "../../events/impl/framestagenotifyevent.hpp"
//#include "../../events/eventbus.hpp"
#include "../../utils/logging.hpp"
#include "../../anium.hpp"
#include "../vmt.hpp"

namespace Hooks {

    #if defined(_WIN32)
        void __stdcall FrameStageNotify(ClientFrameStage_t stage);
    #elif defined(__APPLE__) || defined(__linux__)
        void FrameStageNotify(void*, ClientFrameStage_t stage);
    #endif

}

#endif //ANIUM_FRAMESTAGENOTIFY_HPP

#ifndef ANIUM_FRAMESTAGENOTIFY_HPP
#define ANIUM_FRAMESTAGENOTIFY_HPP

#include "../../sdk/definitions/definitions.hpp"
#include "../../events/impl/framestagenotifyevent.hpp"
#include "../../events/eventbus.hpp"
#include "../../utils/logging.hpp"
#include "../../anium.hpp"
#include "../vmt.hpp"

namespace Hooks {

    void FrameStageNotify(ClientFrameStage_t stage);

}

#endif //ANIUM_FRAMESTAGENOTIFY_HPP

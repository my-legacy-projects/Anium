#ifndef ANIUM_EVENTBUS_HPP
#define ANIUM_EVENTBUS_HPP

#include "impl/events.hpp"
#include "bus.hpp"
#include "event.hpp"

extern eventpp::Bus<FrameStageNotifyEvent, PaintEvent> eventBus;

namespace EventBus {

    void Init();

}

#endif //ANIUM_EVENTBUS_HPP

#include "eventbus.hpp"

eventpp::Bus<FrameStageNotifyEvent, PaintEvent> eventBus = eventpp::Bus<FrameStageNotifyEvent, PaintEvent>();

void EventBus::Init() {

}

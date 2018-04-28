#ifndef ANIUM_FRAMESTAGENOTIFYEVENT_HPP
#define ANIUM_FRAMESTAGENOTIFYEVENT_HPP

#include "../../sdk/definitions/ClientFrameStage.hpp"
#include "../event.hpp"

struct FrameStageNotifyEvent : public eventpp::Event<FrameStageNotifyEvent> {
private:
    ClientFrameStage_t stage;

public:
    explicit FrameStageNotifyEvent(ClientFrameStage_t stage) {
        this->stage = stage;
    }

    ClientFrameStage_t GetFrameStage() {
        return this->stage;
    }

};

#endif  // ANIUM_FRAMESTAGENOTIFYEVENT_HPP

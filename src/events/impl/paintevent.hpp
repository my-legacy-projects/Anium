#ifndef ANIUM_PAINTEVENT_HPP
#define ANIUM_PAINTEVENT_HPP

#include "../../sdk/definitions/PaintMode.hpp"
#include "../event.hpp"

struct PaintEvent : public eventpp::Event<PaintEvent> {
private:
    PaintMode mode;

public:
    explicit PaintEvent(PaintMode mode) {
        this->mode = mode;
    }

    PaintMode GetPaintMode() {
        return this->mode;
    }

};

#endif  // ANIUM_PAINTEVENT_HPP

#pragma once

namespace eventpp {

struct BaseEvent {
    virtual ~BaseEvent() = 0;
};

inline BaseEvent::~BaseEvent() { }

template<class D>
struct Event: private BaseEvent {
private:
    bool cancelled = false;

public:
    bool IsCancelled() {
        return this->cancelled;
    }

    void SetCancelled(bool cancelled) {
        this->cancelled = cancelled;
    }

};

}

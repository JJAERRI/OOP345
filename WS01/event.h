#ifndef SENECA_EVENT_H
#define SENECA_EVENT_H

#include <string>
#include <chrono>
#include <iostream>

namespace seneca {
    class Event {
        std::string m_eventName;
        std::chrono::nanoseconds m_duration;

    public:
        Event() = default;
        Event(const char* name, const std::chrono::nanoseconds& duration);

        friend std::ostream& operator<<(std::ostream& os, const Event& event);
    };
}

#endif

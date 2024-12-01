#ifndef SENECA_TIMEMONITOR_H
#define SENECA_TIMEMONITOR_H

#include "event.h"
#include <chrono>

namespace seneca {
    class TimeMonitor {
        const char* m_eventName = nullptr;
        std::chrono::steady_clock::time_point m_startTime;

    public:
        void startEvent(const char* name);
        Event stopEvent();
    };
}

#endif

#ifndef SENECA_LOGGER_H
#define SENECA_LOGGER_H

#include "event.h"

namespace seneca {
    class Logger {
        Event* m_events = nullptr;
        size_t m_eventCount = 0;

    public:
        Logger() = default;
        ~Logger();
        Logger(Logger&&) noexcept;
        Logger& operator=(Logger&&) noexcept;
        void addEvent(const Event& event);
        friend std::ostream& operator<<(std::ostream& os, const Logger& logger);
    };
}

#endif

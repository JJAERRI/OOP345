#include "logger.h"
#include <iostream>
#include <iomanip>

namespace seneca {
    Logger::~Logger() {
        delete[] m_events;
    }

    Logger::Logger(Logger&& other) noexcept : m_events(other.m_events), m_eventCount(other.m_eventCount) {
        other.m_events = nullptr;
        other.m_eventCount = 0;
    }

    Logger& Logger::operator=(Logger&& other) noexcept {
        if (this != &other) {
            delete[] m_events;
            m_events = other.m_events;
            m_eventCount = other.m_eventCount;
            other.m_events = nullptr;
            other.m_eventCount = 0;
        }
        return *this;
    }

    void Logger::addEvent(const Event& event) {
        Event* temp = new Event[m_eventCount + 1];
        for (size_t i = 0; i < m_eventCount; ++i) {
            temp[i] = m_events[i];
        }
        temp[m_eventCount] = event;
        delete[] m_events;
        m_events = temp;
        ++m_eventCount;
    }

    std::ostream& operator<<(std::ostream& os, const Logger& logger) {
        for (size_t i = 0; i < logger.m_eventCount; ++i) {
            os << logger.m_events[i] << std::endl;
        }
        return os;
    }
}

#include "event.h" 
#include "settings.h"
#include <iomanip>

namespace seneca {
    Event::Event(const char* name, const std::chrono::nanoseconds& duration)
        : m_eventName(name), m_duration(duration) {}

    std::ostream& operator<<(std::ostream& os, const Event& event) {
        static int counter = 0;
        counter++;

        long long timeValue = event.m_duration.count();  

        if (g_settings.m_time_units == "microseconds") {
            timeValue /= 1000;
        }
        else if (g_settings.m_time_units == "milliseconds") {
            timeValue /= 1000000;
        }
        else if (g_settings.m_time_units == "seconds") {
            timeValue /= 1000000000; 

            if (timeValue < 10) {
                timeValue = 0;
            }
        }

        os << std::right << std::setw(2) << counter << ": ";

        os << std::right << std::setw(40) << event.m_eventName << " -> ";

        if (g_settings.m_time_units == "nanoseconds") {
            os << std::right << std::setw(11) << timeValue;
        }
        else if (g_settings.m_time_units == "microseconds") {
            os << std::right << std::setw(8) << timeValue;
        }
        else if (g_settings.m_time_units == "milliseconds") {
            os << std::right << std::setw(5) << timeValue;
        }
        else if (g_settings.m_time_units == "seconds") {
            os << std::right << std::setw(2) << timeValue;
        }

        os << " " << g_settings.m_time_units;

        return os;
    }
}

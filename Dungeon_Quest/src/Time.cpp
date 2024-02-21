#include "Time.h"

chrono_time_t Time::m_start_frame = chrono_high_t::now();
chrono_time_t Time::m_start_frame_cache = chrono_high_t::now();
chrono_time_t Time::m_end_frame = chrono_high_t::now();
float Time::m_fixed_delta_time = 0.02F;
const chrono_time_t Time::m_startup_time = chrono_high_t::now();
Time *Time::m_instance = nullptr;

Time::Time()
{
}

Time::~Time()
{
}

void Time::instantiate()
{
    if (!m_instance)
    {
        m_instance = new Time();
    }
}

void Time::destroy()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = nullptr;
    }
}

Time *Time::getInstance()
{
    return m_instance;
}

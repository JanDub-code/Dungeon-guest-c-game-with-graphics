#ifndef __E_TIME__
#define __E_TIME__

// INFO: I'm not sure how exactly timers work in Qt so I made this simple one

#include <chrono>

typedef std::chrono::high_resolution_clock::time_point chrono_time_t;
typedef std::chrono::high_resolution_clock chrono_high_t;

#define chronoDurationMil std::chrono::duration_cast<std::chrono::milliseconds>
#define chronoDurationMic std::chrono::duration_cast<std::chrono::microseconds>

// Singleton
class Time
{
private:
    static chrono_time_t m_start_frame;
    static chrono_time_t m_start_frame_cache;
    static chrono_time_t m_end_frame;
    static float m_fixed_delta_time;
    static const chrono_time_t m_startup_time;
    static Time *m_instance;

    // Constructor
    Time();

    // Destructor
    ~Time();
public:
    static void instantiate();
    static void destroy();
    static Time *getInstance();

    // Capture start frame timestamp to cache
    inline static void startFrame()
    { m_start_frame_cache = chrono_high_t::now(); }

    // Save start frame timestamp from cache to start frame and capture end frame timestamp
    inline static void endFrame()
    {
        m_start_frame = m_start_frame_cache;
        m_end_frame = chrono_high_t::now();
    }

    // Return Delta Time (time since last frame in seconds)
    inline static float deltaTime()
    { return static_cast<float>(chronoDurationMic(m_end_frame - m_start_frame).count()) / 1000000.0F; }

    // Return Fixed Delta Time (can be overwritten)
    inline static float &fixedDeltaTime()
    { return m_fixed_delta_time; }

    // Time since startup in seconds (be careful with double overflow)
    inline static double realTimeSinceStartup()
    { return static_cast<double>(chronoDurationMic(chrono_high_t::now() - m_startup_time).count()) / 1000000.0; }
};

#endif

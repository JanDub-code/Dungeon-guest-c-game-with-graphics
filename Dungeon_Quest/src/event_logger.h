#ifndef EVENTLOGGER_H
#define EVENTLOGGER_H

#include <fstream>

//#define logOpen EventLogger::openLog
#define logClose EventLogger::closeLog
#define logEvent EventLogger::eventLog

class EventLogger
{
private:
    static const char *m_name;
    static std::fstream m_log_file;
    static EventLogger *m_instance;
    static bool m_init_fail;

    EventLogger(const char *name);
    ~EventLogger();
public:
    static void instantiate(const char *name);
    static void destroy();
    static EventLogger *getInstance();
    //open log file
    //void openLog(/*const char *name*/);
    //close log file
    static void closeLog();

    enum class LogType
    {
        LOG_TYPE_DEFAULT = 0x0, // int 0
        LOG_TYPE_INFO = 0x1,
        LOG_TYPE_ERROR = 0x2,
        LOG_TYPE_WARNING = 0x3,
        LOG_TYPE_DEBUG = 0x4,
        LOG_EV_SRC = 0x5
    };

    //event logger
    static void eventLog(const char *event_source, const LogType log_type, const std::string message);
private:
    //open log file
    static void openLog(/*const char *name*/);
    static std::string timeLog();
    template <class T>
    static T localTime();
    static const std::string getStringLogType(const LogType log_type);
};

#endif // EVENTLOGGER_H

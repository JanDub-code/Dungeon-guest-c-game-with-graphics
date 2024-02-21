#include "event_logger.h"
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>

const char *EventLogger::m_name = "";
std::fstream EventLogger::m_log_file;
EventLogger *EventLogger::m_instance = nullptr;
bool EventLogger::m_init_fail = false;

EventLogger::EventLogger(const char *name)
{
    m_name = name;

    try
    {
#if defined(__linux__) || defined(__APPLE__)
        int check = ::mkdir("logs",7);
#elif _WIN32
        int check = ::mkdir("logs");
#endif
        if (!check)
        {
            std::cout << "Directory for Event Logger successfuly created!" << std::endl;
            openLog();
        }
        else if (check == -1)
        {
            std::cerr << "Directory for Event Logger already exists!" << std::endl;
            openLog();
        }
        else
        {
            throw(check);
        }
    }
    catch (int result)
    {
        std::cerr << "Unable to create directory for Event Logger!" << std::endl;
        std::cerr << "mkdir result: " << result << std::endl;
        m_init_fail = true;
        delete this;
    }
}

EventLogger::~EventLogger()
{
    closeLog(); // if deleted but forgot to close
}

void EventLogger::instantiate(const char *name)
{
    if (!m_instance)
    {
        m_instance = new EventLogger(name);

        if (m_init_fail)
        {
            m_init_fail = false;
            m_instance = nullptr;
        }
    }
}

void EventLogger::destroy()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = nullptr;
    }
}

EventLogger *EventLogger::getInstance()
{
    return m_instance;
}


void EventLogger::openLog(/*const char *name*/)
{
    if (!m_log_file.is_open())
    {
        std::string log_file_name = "";
        log_file_name = "logs/" + std::string(m_name) + "_" + std::to_string(1900 + localTime<tm*>()->tm_year)
                        + "" + std::to_string(1 + localTime<tm*>()->tm_mon)
                        + "" + std::to_string(localTime<tm*>()->tm_mday)
                        + "" + std::to_string(localTime<tm*>()->tm_hour)
                        + "" + std::to_string(localTime<tm*>()->tm_min)
                        + "" + std::to_string(localTime<tm*>()->tm_sec) + ".log";
        m_log_file.open(log_file_name, std::fstream::out);
    }
    else
    {
        eventLog("log", LogType::LOG_TYPE_WARNING, "Attempting to open already opened log file");
    }
}

void EventLogger::closeLog()
{
    if (m_log_file.is_open())
    {
        m_log_file.close();
    }
}

//event logger
void EventLogger::eventLog(const char *event_source, const LogType log_type, const std::string message)
{
    if (m_log_file.is_open()) // TODO: Remove?
    {
        std::string log_message = "";
        log_message = "[" + timeLog() + "]" + " "
                      + "[" + std::string(event_source) + "/" + getStringLogType(log_type) + "]"
                      + ": " + message + "\n";
        m_log_file << log_message;
    }
}

std::string EventLogger::timeLog()
{
    std::string log_time = "";
    log_time = std::to_string(localTime<tm*>()->tm_hour)
               + ":" + std::to_string(localTime<tm*>()->tm_min)
               + ":" + std::to_string(localTime<tm*>()->tm_sec);
    return log_time;
}

const std::string EventLogger::getStringLogType(const LogType log_type)
{
    switch (log_type) {
    case LogType::LOG_TYPE_DEFAULT:
        return std::string("default");
    case LogType::LOG_TYPE_INFO:
        return std::string("INFO");
    case LogType::LOG_TYPE_WARNING:
        return std::string("WARN");
    case LogType::LOG_TYPE_ERROR:
        return std::string("ERROR");
    case LogType::LOG_TYPE_DEBUG:
        return std::string("DEBUG");
    case LogType::LOG_EV_SRC:
        return std::string("log");
    default:
        return std::string("undefined");
        break;
    }
}

template<class T>
T EventLogger::localTime()
{
    time_t now = time(NULL);
    tm *ltm = localtime(&now);
    return ltm;
}

#ifndef __HAHA_LOG_LOGGERMANAGER__
#define __HAHA_LOG_LOGGERMANAGER__

#include <map>
#include <string>
#include <stdarg.h>
#include "base/Mutex.h"
#include "base/util.h"
#include "Logger.h"


#define HAHA_LOG_LEVEL(logger, level) \
    if(logger->getLevel() <= level) \
    haha::log::LogInfoWrapper(logger, haha::log::LogInfo::ptr(new haha::log::LogInfo(logger->getName(), level, \
                            __FILE__, __LINE__, 0, haha::GetThreadId(), \
                            time(0), haha::Thread::getCurrentThreadName()))).getSS()

#define HAHA_LOG_DEBUG(logger)  HAHA_LOG_LEVEL(logger, haha::log::LogLevel::Level::DEBUG)
#define HAHA_LOG_INFO(logger)  HAHA_LOG_LEVEL(logger, haha::log::LogLevel::Level::INFO)
#define HAHA_LOG_WARN(logger)  HAHA_LOG_LEVEL(logger, haha::log::LogLevel::Level::WARN)
#define HAHA_LOG_ERROR(logger)  HAHA_LOG_LEVEL(logger, haha::log::LogLevel::Level::ERROR)
#define HAHA_LOG_FATAL(logger)  HAHA_LOG_LEVEL(logger, haha::log::LogLevel::Level::FATAL)


#define HAHA_LOG_FMT_LEVEL(logger, level, fmt, ...) \
    if(logger->getLevel() <= level) \
    haha::log::LogInfoWrapper(logger, haha::log::LogInfo::ptr(new haha::log::LogInfo(logger->getName(), level, \
                            __FILE__, __LINE__, 0, haha::GetThreadId(), \
                            time(0), haha::Thread::getCurrentThreadName()))).getLogInfo()->format(fmt, __VA_ARGS__)

#define HAHA_LOG_FMT_DEBUG(logger, fmt, ...)  HAHA_LOG_FMT_LEVEL(logger, haha::log::LogLevel::Level::DEBUG, fmt, __VA_ARGS__)
#define HAHA_LOG_FMT_INFO(logger, fmt, ...)  HAHA_LOG_FMT_LEVEL(logger, haha::log::LogLevel::Level::INFO, fmt, __VA_ARGS__)
#define HAHA_LOG_FMT_WARN(logger, fmt, ...)  HAHA_LOG_FMT_LEVEL(logger, haha::log::LogLevel::Level::WARN, fmt, __VA_ARGS__)
#define HAHA_LOG_FMT_ERROR(logger, fmt, ...) HAHA_LOG_FMT_LEVEL(logger, haha::log::LogLevel::Level::ERROR, fmt, __VA_ARGS__)
#define HAHA_LOG_FMT_FATAL(logger, fmt, ...)  HAHA_LOG_FMT_LEVEL(logger, haha::log::LogLevel::Level::FATAL, fmt, __VA_ARGS__)


#define HAHA_LOG_SYNC_ROOT() haha::log::LoggerManager::getInstance().getSyncRoot()
#define HAHA_LOG_ASYNC_ROOT() haha::log::LoggerManager::getInstance().getAsyncRoot()



namespace haha{

namespace log{

static const std::string default_sync_log_file = "app_sync";
static const std::string default_async_log_file = "app_async";
static const int default_roll_size = 10 * 1000 * 1000;
static const int default_flush_interval = 3;


class LogInfoWrapper{
public:
    LogInfoWrapper(Logger::ptr logger, LogInfo::ptr info):logger_(logger),info_(info){}
    ~LogInfoWrapper(){
        logger_->log(info_);
    }
    LogInfo::OutStream& getSS() { return info_->getSS(); }

private:
    Logger::ptr logger_;
    LogInfo::ptr info_;
};


class LoggerManager{
public:
    typedef SpinLock MutexType;
    
    static LoggerManager& getInstance(){
        static LoggerManager manager;
        return manager;
    }

    Logger::ptr getLogger(const std::string &name);
    void init();
    Logger::ptr getSyncRoot() const {return sync_root_;}
    Logger::ptr getAsyncRoot() const {return async_root_;}

    std::string toYamlString();

private:
    LoggerManager();

private:
    MutexType mutex_;
    std::map<std::string, Logger::ptr> loggers_;
    Logger::ptr sync_root_;
    Logger::ptr async_root_;
    Logger::ptr sync_stdout_;
};

}

}

#endif